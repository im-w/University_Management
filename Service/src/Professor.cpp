#include "Professor.hpp"
#include <iostream>

Professor::Professor(const string &id, const string &name,
                     const string &major_id, const string &position)
    : User(id, name), major_id(major_id), position(position) {}

void Professor::printInfo() {
  cout << "Professor Information:" << endl;
  cout << "ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Major ID: " << major_id << endl;
  cout << "Position: " << position << endl;
}