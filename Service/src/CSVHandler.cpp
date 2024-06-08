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
  matrix = CSVHandler::csvToMatrix();
}

vector<vector<string>> CSVHandler::csvToMatrix() {
  vector<vector<string>> result_matrix;
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
    result_matrix.push_back(line_vector);
  }
  file.close();

  return result_matrix;
}

void CSVHandler::printData() const {
  for (vector<vector<string>>::const_iterator it = matrix.begin();
       it != matrix.end(); ++it) {
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
  for (size_t i = 0; i < matrix.size(); ++i) {
    result += "Row " + to_string(i + 1) + " has " +
              to_string(matrix[i].size()) + " columns.\n";
  }
  return result;
}

vector<string> CSVHandler::findColumn(const string key) const {
  vector<string> result_vector;

  if (matrix.empty() || matrix[0].empty()) {
    return result_vector;
  }

  auto it = find(matrix[0].begin(), matrix[0].end(), key);

  if (it == matrix[0].end()) {
    throw runtime_error("Key not found in header. key: " + key);
    return result_vector;
  }

  size_t index = distance(matrix[0].begin(), it);

  for (size_t i = 1; i < matrix.size(); ++i) {
    if (index < matrix[i].size()) {
      result_vector.push_back(matrix[i][index]);
    } else {
      throw runtime_error("Index out of bounds. index: " + to_string(index) +
                          " key: " + key);
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
  return matrix[index];
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
  vector<string> header = matrix[0];
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

void CSVHandler::writeMatrixToCSV() {
  ofstream file(file_path);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << file_path << endl;
    return;
  }

  for (const auto &row : matrix) {
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

void CSVHandler::updateFieldInMatrix(const string column_key,
                                     const string column_value,
                                     const string field_header,
                                     const string new_field_value) {
  int index = findRowIndex(column_key, column_value);
  matrix[index][keyHeaderIndex(field_header)] = new_field_value;
}

void CSVHandler::appendFieldInMatrix(const string column_key,
                                     const string column_value,
                                     const string field_header,
                                     const string append_value) {
  int index = findRowIndex(column_key, column_value);
  matrix[index][keyHeaderIndex(field_header)] += append_value;
}

void CSVHandler::addRowToMatrix(vector<string> row) {
  if (!matrix.empty()) {
    if (matrix[0].size() != row.size()) {
      runtime_error("Size of row isn't matching with the header of the CSV.");
    }
  }
  matrix.push_back(row);
}

void CSVHandler::deleteRowOfMatrix(const string column_key,
                                   const string column_value) {
  int index = findRowIndex(column_key, column_value);
  matrix.erase(matrix.begin() + (index));
}

vector<vector<string>> CSVHandler::bodyMatrix() {
  vector<vector<string>> output;
  for (size_t i = 1; i < matrix.size(); i++) {
    output.push_back(matrix[i]);
  }
  return output;
}

void CSVHandler::cleanBodyOfMatrix() {
  if (matrix.size() > 1) {
    matrix.erase(matrix.begin() + 1, matrix.end());
  }
}

bool CSVHandler::isEmpty() { return (bodyMatrix().empty()); }
