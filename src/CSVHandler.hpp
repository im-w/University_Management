#ifndef CSVHANDLER_HPP
#define CSVHANDLER_HPP

#include <string>
#include <vector>

using namespace std;

class CSVHandler {
public:
  CSVHandler(string _file_path);
  void printData() const;
  string size() const;
  vector<string> findColumn(const string key) const;
  void printColumn(const string key) const;
  bool isExists(const string column_key, const string value) const;
  vector<string> findRow(const string column_key,
                         const string column_value) const;
  int findRowIndex(const string column_key,
                         const string column_value) const;  
  void printRow(const string column_key, const string column_value) const;
  size_t keyHeaderIndex(const string key) const;
  string findField(const string column_key, const string column_value,
                   const string field_header) const;
  void updateFieldInMatris(const string column_key, const string column_value,
                           const string field_header,
                           const string new_field_value);
  void appendFieldInMatris(const string column_key, const string column_value,
                           const string field_header,
                           const string append_value);
  void writeMatrisToCSV();
  void addRowToMatris(vector<string> row);
  void deleteRowOfMatris(const string column_key, const string column_value);
  vector<vector<string>> bodyMatris();
  void cleanBodyOfMatris();
  bool isEmpty();
private:
  vector<vector<string>> csvToMatris();

  string file_path;
  vector<vector<string>> matris;
};

#endif // CSVHANDLER_HPP
