#include "User.hpp"
#include <iostream>

User::User(const string &id, const string &name) : id(id), name(name) {}

void User::printInfo() {
  cout << "User Information:" << endl;
  cout << "ID: " << id << endl;
  cout << "Name: " << name << endl;
}

string User::getId() const { return id; }
string User::getName() const { return name; }
