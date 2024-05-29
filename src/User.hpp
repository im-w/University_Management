#ifndef USER_HPP
#define USER_HPP

#include <string>

using namespace std;

class User {
protected:
  string id;
  string name;

public:
  User(const string &id, const string &name);
  virtual ~User() {}
  virtual void printInfo() ;
  string getId() const;
  string getName() const;
};

#endif // USER_HPP
