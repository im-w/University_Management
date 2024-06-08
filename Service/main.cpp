#include "src/Program.hpp"
#include <iostream>

using namespace std;

bool validateArguments(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " </path/to/majors/file> </path/to/students/file> "
                 "</path/to/courses/file> </path/to/professors/file>"
              << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (!validateArguments(argc, argv)) {
    return -1;
  }
  Program program(argv[1], argv[2], argv[3], argv[4]);
  program.run();
  return 0;
}