#include "functions.hpp"

void autoMapImageServerPaths(Server &server) {
  CSVHandler images_CSV ("Users_Storage/images-path.csv");
  vector<string> images_path = images_CSV.findColumn("image_path");
  for (const string &path : images_path) {
    if (path != NONE_STRING) {
    size_t pos = path.find_last_of("/\\");
    string link = path.substr(pos);
      server.get(link,new ShowImage(path));
      cout << path << endl;
      cout << link << endl;
    }
  }
}

void addImagePathToAutoMapImageServer(string imagePath) {
    CSVHandler images_CSV ("Users_Storage/images-path.csv");
    vector<string> images_path = images_CSV.findColumn("image_path");
    for (const string &path : images_path) {
        if (path == imagePath) {
            return;
        }
    }
    vector<string> row = {imagePath};
    images_CSV.addRowToMatrix(row);
    images_CSV.writeMatrixToCSV();
}

void addAndLoadImage(string imagePath, Server &server) {
    CSVHandler images_CSV ("Users_Storage/images-path.csv");
    vector<string> images_path = images_CSV.findColumn("image_path");
    for (const string &path : images_path) {
        if (path == imagePath) {
            return;
        }
    }
    if (imagePath != NONE_STRING) {
       vector<string> row = {imagePath};
      images_CSV.addRowToMatrix(row);
      images_CSV.writeMatrixToCSV();
      size_t pos = imagePath.find_last_of("/\\");
      string link = imagePath.substr(pos);
      server.get(link,new ShowImage(imagePath));
      }
}
