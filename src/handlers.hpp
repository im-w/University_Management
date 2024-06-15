#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include "Program.hpp"
#include <map>
#include <string>

#include "../server/server.hpp"

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *) override;
};

class LoginHandler : public RequestHandler {
public:
  LoginHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class LogoutHandler : public RequestHandler {
public:
  LogoutHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentShowOfferCourseHandler : public RequestHandler {
public:
  StudentShowOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentShowMyOfferCourseHandler : public RequestHandler {
public:
  StudentShowMyOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostStudentJoinOfferCourseHandler : public RequestHandler {
public:
  PostStudentJoinOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostStudentLeaveOfferCourseHandler : public RequestHandler {
public:
  PostStudentLeaveOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class ProfessorShowOfferCourseHandler : public RequestHandler {
public:
  ProfessorShowOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class AdminShowOfferCourseHandler : public RequestHandler {
public:
  AdminShowOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostAdminAddOfferCourseHandler : public RequestHandler {
public:
  PostAdminAddOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *) override;
};

class PostStudentProfilePictureHandler : public RequestHandler {
public:
  Response *callback(Request *) override;
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(const std::string &filePath);
  std::map<std::string, std::string> handle(Request *req) override;
};

#endif // HANDLERS_HPP_INCLUDE
