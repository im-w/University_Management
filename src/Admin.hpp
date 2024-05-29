#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include <string>

using namespace std;

class Admin : public User {
public:
  Admin(const string &id, const string &name);
};

#endif // ADMIN_HPP