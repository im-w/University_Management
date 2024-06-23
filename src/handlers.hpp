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

class StudentHomeHandler : public RequestHandler {
public:
  StudentHomeHandler(Program &program) : program_(program) {}
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

class StudentChangeProfilePictureHandler : public RequestHandler {
public:
  StudentChangeProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentSeePersonalPageHandler : public RequestHandler {
public:
  StudentSeePersonalPageHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentSendPostHandler : public RequestHandler {
public:
  StudentSendPostHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentJoinOfferCourseHandler : public RequestHandler {
public:
  StudentJoinOfferCourseHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class StudentLeaveOfferCourseHandler : public RequestHandler {
public:
  StudentLeaveOfferCourseHandler(Program &program) : program_(program) {}
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

class PostStudentChangeProfilePictureHandler : public RequestHandler {
public:
  PostStudentChangeProfilePictureHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostStudentDeleteProfilePictureHandler : public RequestHandler {
public:
  PostStudentDeleteProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostStudentSendPostHandler : public RequestHandler {
public:
  PostStudentSendPostHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostStudentSeePersonalPageHandler : public RequestHandler {
public:
  PostStudentSeePersonalPageHandler(Program &program) : program_(program) {}
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

class ProfessorHomeHandler : public RequestHandler {
public:
  ProfessorHomeHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class ProfessorChangeProfilePictureHandler : public RequestHandler {
public:
  ProfessorChangeProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class ProfessorSeePersonalPageHandler : public RequestHandler {
public:
  ProfessorSeePersonalPageHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class ProfessorSendPostHandler : public RequestHandler {
public:
  ProfessorSendPostHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostProfessorChangeProfilePictureHandler : public RequestHandler {
public:
  PostProfessorChangeProfilePictureHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostProfessorDeleteProfilePictureHandler : public RequestHandler {
public:
  PostProfessorDeleteProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostProfessorSendPostHandler : public RequestHandler {
public:
  PostProfessorSendPostHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostProfessorSeePersonalPageHandler : public RequestHandler {
public:
  PostProfessorSeePersonalPageHandler(Program &program) : program_(program) {}
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

class AdminHomeHandler : public RequestHandler {
public:
  AdminHomeHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class AdminChangeProfilePictureHandler : public RequestHandler {
public:
  AdminChangeProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class AdminSeePersonalPageHandler : public RequestHandler {
public:
  AdminSeePersonalPageHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class AdminSendPostHandler : public RequestHandler {
public:
  AdminSendPostHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};


class AdminAddOfferCourseHandler : public RequestHandler {
public:
  AdminAddOfferCourseHandler(Program &program) : program_(program) {}
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

class PostAdminChangeProfilePictureHandler : public RequestHandler {
public:
  PostAdminChangeProfilePictureHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostAdminDeleteProfilePictureHandler : public RequestHandler {
public:
  PostAdminDeleteProfilePictureHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};

class PostAdminSendPostHandler : public RequestHandler {
public:
  PostAdminSendPostHandler(Program &program,Server &server) : program_(program) , server_(server) {}
  Response *callback(Request *) override;

private:
  Program &program_;
  Server &server_;
};

class PostAdminSeePersonalPageHandler : public RequestHandler {
public:
  PostAdminSeePersonalPageHandler(Program &program) : program_(program) {}
  Response *callback(Request *) override;

private:
  Program &program_;
};


class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *) override;
};

class PostAdminProfilePictureHandler : public RequestHandler {
public:
  Response *callback(Request *) override;
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(const std::string &filePath);
  std::map<std::string, std::string> handle(Request *req) override;
};

#endif // HANDLERS_HPP_INCLUDE
