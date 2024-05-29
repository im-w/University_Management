#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include "User.hpp"
#include <string>

using namespace std;

class Professor : public User {
protected:
  string major_id;
  string position;

public:
  Professor(const string &id, const string &name, const string &major_id,
            const string &position);
  void printInfo() ;
};

#endif // PROFESSOR_HPP