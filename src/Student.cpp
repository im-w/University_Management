#include "Student.hpp"
#include <iostream>

Student::Student(const string &id, const string &name, const string &major_id,
                 const string &semester)
    : User(id, name), major_id(major_id), semester(semester) {}

void Student::printInfo() {
  cout << "Student Information:" << endl;
  cout << "ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Major ID: " << major_id << endl;
  cout << "Semester: " << semester << endl;
}

string Student::getSemester() { return semester; }