#include "handlers.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string randomNumber = std::to_string(std::rand() % 10 + 1);
  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "  <title>Random Number Page</title>";
  body += "</head>";

  body += "<body style=\"text-align: center;\">";
  body += "  <h1>AP HTTP</h1>";
  body += "  <p>A random number in [1, 10] is: " + randomNumber + "</p>";
  body += "  <p>SessionId: " + req->getSessionId() + "</p>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *LoginHandler::callback(Request *req) {
  std::string username = req->getBodyParam("username");
  std::string password = req->getBodyParam("password");
  if (username == "root") {
    throw Server::Exception("Remote root access has been disabled.");
  }
  std::cout << "username: " << username << ",\tpassword: " << password
            << std::endl;
  vector<string> input = {
      POST_COMMAND,   LOGIN_SUB_COMMAND, SEPARATOR_CHARACTER,
      ID_ARG_COMMAND, username,          PASSWORD_ARG_COMMAND,
      password};
  if (program_.checkLoginCommand(input)) {
    Response *res = nullptr;
    if (program_.isStudentIdValid(username)) {
      res = Response::redirect("/student");
    } else if (program_.isProfessorIdValid(username)) {
      res = Response::redirect("/professor");
    } else if (username == ADMIN_ID) {
      res = Response::redirect("/admin");
    } else {
      res = Response::redirect("/");
    }
    res->setSessionId("SID");
    return res;
  } else {
    Response *res = Response::redirect("/");
    return res;
  }
}

Response *UploadHandler::callback(Request *req) {
  std::string name = req->getBodyParam("file_name");
  std::string file = req->getBodyParam("file");
  utils::writeToFile(file, name);
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(const std::string &filePath)
    : TemplateHandler(filePath) {}

std::map<std::string, std::string> ColorHandler::handle(Request *req) {
  std::string newName = "I am " + req->getQueryParam("name");
  std::map<std::string, std::string> context;
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
