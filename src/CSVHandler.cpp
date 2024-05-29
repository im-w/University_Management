#include "CSVHandler.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

CSVHandler::CSVHandler(string _file_path) : file_path(_file_path) {
  matris = CSVHandler::csvToMatris();
}

vector<vector<string>> CSVHandler::csvToMatris() {
  vector<vector<string>> result_matris;
  ifstream file(file_path);
  if (!file.is_open()) {
    throw runtime_error("CSV file not found. file_path: " + file_path);
  }
  string line;
  while (getline(file, line)) {
    vector<string> line_vector;
    stringstream ss(line);
    string word;
    while (getline(ss, word, ',')) {
      line_vector.push_back(word);
    }
    result_matris.push_back(line_vector);
  }
  file.close();

  return result_matris;
}

void CSVHandler::printData() const {
  for (vector<vector<string>>::const_iterator it = matris.begin();
       it != matris.end(); ++it) {
    const vector<string> &vec = *it;
    for (vector<string>::const_iterator jt = vec.begin(); jt != vec.end();
         ++jt) {
      const string &str = *jt;
      cout << str << " ";
    }
    cout << endl;
  }
}

string CSVHandler::size() const {
  string result;
  for (size_t i = 0; i < matris.size(); ++i) {
    result += "Row " + to_string(i + 1) + " has " +
              to_string(matris[i].size()) + " columns.\n";
  }
  return result;
}

vector<string> CSVHandler::findColumn(const string key) const {
  vector<string> result_vector;
  
  if (matris.empty() || matris[0].empty()) {
    return result_vector;
  }
  
  auto it = find(matris[0].begin(), matris[0].end(), key);
  
  if (it == matris[0].end()) {
    throw runtime_error("Key not found in header. key: " + key);
    return result_vector;
  }
  
  size_t index = distance(matris[0].begin(), it);
  
  for (size_t i = 1; i < matris.size(); ++i) {
    if (index < matris[i].size()) {
      result_vector.push_back(matris[i][index]);
    } else {
      throw runtime_error("Index out of bounds. index: "+to_string(index)+" key: "+key);
      return result_vector;
    }
  }
  
  return result_vector;
}

void CSVHandler::printColumn(const string key) const {
  vector<string> column = findColumn(key);
  for (const string &field : column)
    cout << "[" << field << "]" << endl;
}

bool CSVHandler::isExists(const string column_key, const string value) const {
  vector<string> column = findColumn(column_key);
  for (const string &field : column) {
    if (field == value)
      return true;
  }
  return false;
}

vector<string> CSVHandler::findRow(const string column_key,
                                   const string column_value) const {
  int index = findRowIndex(column_key, column_value);
  return matris[index];
}

int CSVHandler::findRowIndex(const string column_key,
                             const string column_value) const {
  int index = 0;
  if (isExists(column_key, column_value)) {
    vector<string> column = findColumn(column_key);
    for (const string &field : column) {
      if (field == column_value)
        break;
      index++;
    }
  } else {
    throw runtime_error("Column_value not find in column_key. column_value: " +
                        column_value + " column_key: " + column_key);
  }
  return (index + 1);
}
void CSVHandler::printRow(const string column_key,
                          const string column_value) const {
  vector<string> row = findRow(column_key, column_value);
  for (const string &field : row)
    cout << "[" << field << "]" << endl;
}

size_t CSVHandler::keyHeaderIndex(const string key) const {
  vector<string> header = matris[0];
  size_t index = 0;
  for (const string &field : header) {
    if (field == key)
      return index;
    index++;
  }
  throw runtime_error("Key not found in header. key: " + key);
}

string CSVHandler::findField(const string column_key, const string column_value,
                             const string field_header) const {
  return findRow(column_key, column_value)[keyHeaderIndex(field_header)];
}

void CSVHandler::writeMatrisToCSV() {
  ofstream file(file_path);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << file_path << endl;
    return;
  }

  for (const auto &row : matris) {
    for (size_t i = 0; i < row.size(); ++i) {
      file << row[i];
      if (i < row.size() - 1) {
        file << ",";
      }
    }
    file << "\n";
  }

  file.close();
  if (file.fail()) {
    runtime_error("Failed to write to file. file_path: " + file_path);
  }
}

void CSVHandler::updateFieldInMatris(const string column_key,
                                     const string column_value,
                                     const string field_header,
                                     const string new_field_value) {
  int index = findRowIndex(column_key, column_value);
  matris[index][keyHeaderIndex(field_header)] = new_field_value;
}

void CSVHandler::appendFieldInMatris(const string column_key,
                                     const string column_value,
                                     const string field_header,
                                     const string append_value) {
  int index = findRowIndex(column_key, column_value);
  matris[index][keyHeaderIndex(field_header)] += append_value;
}

void CSVHandler::addRowToMatris(vector<string> row) {
  if (!matris.empty()) {
    if (matris[0].size() != row.size()) {
      runtime_error("Size of row isn't matching with the header of the CSV.");
    }
  }
  matris.push_back(row);
}

void CSVHandler::deleteRowOfMatris(const string column_key,
                                   const string column_value) {
  int index = findRowIndex(column_key, column_value);
  matris.erase(matris.begin() + (index));
}

vector<vector<string>> CSVHandler::bodyMatris() {
  vector<vector<string>> output;
  for (size_t i = 1; i < matris.size(); i++) {
    output.push_back(matris[i]);
  }
  return output;
}

void CSVHandler::cleanBodyOfMatris() {
  if (matris.size() > 1) {
    matris.erase(matris.begin() + 1, matris.end());
  }
}

bool CSVHandler::isEmpty() { return (bodyMatris().empty()); }
