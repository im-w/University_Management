#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "User.hpp"
#include <string>

using namespace std;

class Student : public User {
protected:
  string major_id;
  string semester;

public:
  Student(const string &id, const string &name, const string &major_id,
          const string &semester);
  void printInfo();
};

#endif // STUDENT_HPP
