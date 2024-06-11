#ifndef CSVHANDLER_HPP
#define CSVHANDLER_HPP

#include <string>
#include <vector>

using namespace std;

class CSVHandler {
public:
  CSVHandler(string _file_path);
  void writeMatrixToCSV();
  vector<string> findColumn(const string key) const;
  vector<string> findRow(const string column_key,
                         const string column_value) const;
  int findRowIndex(const string column_key, const string column_value) const;
  string findField(const string column_key, const string column_value,
                   const string field_header) const;
  void updateFieldInMatrix(const string column_key, const string column_value,
                           const string field_header,
                           const string new_field_value);
  void appendFieldInMatrix(const string column_key, const string column_value,
                           const string field_header,
                           const string append_value);
  bool isEmpty();
  bool isExists(const string column_key, const string value) const;
  string size() const;
  size_t keyHeaderIndex(const string key) const;
  void addRowToMatrix(vector<string> row);
  void deleteRowOfMatrix(const string column_key, const string column_value);
  vector<vector<string>> bodyMatrix();
  void cleanBodyOfMatrix();
  void printColumn(const string key) const;
  void printRow(const string column_key, const string column_value) const;
  void printData() const;

private:
  vector<vector<string>> csvToMatrix();

  string file_path;
  vector<vector<string>> matrix;
};

#endif // CSVHANDLER_HPP
