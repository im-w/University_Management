#include "handlers.hpp"

#include "functions.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

Response *LoginHandler::callback(Request *req) {
  std::string username = req->getBodyParam("username");
  std::string password = req->getBodyParam("password");
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
    res->setSessionId(username);
    return res;
  } else {
    Response *res = Response::redirect("/");
    return res;
  }
}

Response *LogoutHandler::callback(Request *req) {
  std::string username = req->getBodyParam("username");
  std::string password = req->getBodyParam("password");
  if (username == "root") {
    throw Server::Exception("Remote root access has been disabled.");
  }
  std::cout << "logout : " << req->getSessionId() << std::endl;
  program_.logout();
  Response *res = Response::redirect("/");
  res->setSessionId("");
  return res;
}

Response *StudentHomeHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";

  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff;\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF;\n";
  body += "        }\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6;\n";
  body += "        }\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "        form button {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB;\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";

  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";

  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentShowOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";

  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff;\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF;\n";
  body += "        }\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6;\n";
  body += "        }\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "        form button {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB;\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";

  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "            <p>Show Offer Courses:</p>\n";
  body += "            <p> id | name | capacity | professor</p>\n";
  body += "            <p class=\"output\">" + program_.seeAllOfferCourses() +
          "</p>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";

  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentShowMyOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";

  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n";
  body += "\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";

  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "            <p>Show Offer Courses:</p>\n";
  body += "            <p> Id | Name | Capacity | Professor | Time | Exam date "
          "| Class number</p>\n";
  body += "            <p class=\"output\">" + program_.studentAllCourses() +
          "</p>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";

  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentChangeProfilePictureHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";

  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";

  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>\n";
  body += "                   " + program_.getUserId() + " | " +
          program_.getUserHeader() + "\n";
  body += "                </p>\n";
  body += "            </div>\n";
  body += "            <form action=\"/student-change-profile-picture\" "
          "method=\"post\" enctype=\"multipart/form-data\" style=\"margin-top: "
          "20px;\">\n";
  body += "                <input type=\"file\" name=\"file\" "
          "style=\"margin-bottom: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Upload\" "
          "style=\"padding: 8px 20px; background-color: #B0E0E6; color: white; "
          "border: none; border-radius: 20px; cursor: pointer; transition: "
          "background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "            <form action=\"/student-delete-profile-picture\" "
          "method=\"post\" style=\"margin-top: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Delete Profile "
          "Picture\" style=\"padding: 8px 20px; background-color: #FF6347; "
          "color: white; border: none; border-radius: 20px; cursor: pointer; "
          "transition: background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";

  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentSeePersonalPageHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";

  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff;\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF;\n";
  body += "        }\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6;\n";
  body += "        }\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #B0E0E6;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "        form button {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB;\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #B0E0E6;\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";

  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>UID | Name | Major | Semester/Position | "
          "Join/Offer Courses</p>\n";
  body += "                <p>\n";
  body += "                " + program_.AllUsersHeader();
  body += "                </p>\n";
  body += "                <form action=\"/student-see-personal-page\" "
          "method=\"POST\">\n";
  body += "                    <input type=\"text\" name=\"uid\" "
          "placeholder=\"Enter Person Id\" class=\"curved-input\" required>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">See page</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";

  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentSendPostHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";
  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n";
  body += "\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* High quality CSS for the logout button */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styling the file input */\n";
  body += "        input[type=\"file\"] {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "\n";
  body += "        input[type=\"file\"]::-webkit-file-upload-button {\n";
  body += "            visibility: hidden;\n";
  body += "        }\n";
  body += "\n";
  body += "        input[type=\"file\"]::before {\n";
  body += "            content: 'Choose a file';\n";
  body += "            display: inline-block;\n";
  body += "            background: #B0E0E6; /* Soft super light green */\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            border-radius: 20px;\n";
  body += "            padding: 10px 20px;\n";
  body += "            outline: none;\n";
  body += "            white-space: nowrap;\n";
  body += "            cursor: pointer;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        input[type=\"file\"]:hover::before {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "        }\n";
  body += "\n";
  body += "        input[type=\"file\"]:active::before {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";
  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Send Post:</p>\n";
  body += "                <form action=\"/student-send-post\" method=\"POST\" "
          "enctype=\"multipart/form-data\">\n";
  body += "                    <input type=\"text\" name=\"title\" "
          "placeholder=\"Enter Title\" class=\"curved-input\" required>\n";
  body += "                    <textarea name=\"message\" placeholder=\"Enter "
          "Message\" class=\"curved-input\" rows=\"5\" required></textarea>\n";
  body += "                    <input type=\"file\" name=\"file\" "
          "value=\"NONE_STRING\" >\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Upload Post</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentJoinOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";
  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n";
  body += "\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* High quality CSS for the logout button */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";
  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Join Offer Course:</p>\n";
  body += "                <form action=\"/student-join-offer-course\" "
          "method=\"POST\">\n";
  body += "                    <input type=\"text\" name=\"course-id\" "
          "placeholder=\"Enter Course Id\" class=\"curved-input\" required>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Join Course</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *StudentLeaveOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";
  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n";
  body += "\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #B0E0E6; /* Soft super light green */\n";
  body += "        }\n";
  body += "\n";
  body += "        .submit-button {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body +=
      "            border: 2px solid #B0E0E6; /* Soft super light green */\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #1e1e1e;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            text-align: center;\n";
  body += "            cursor: pointer;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* High quality CSS for the logout button */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";
  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Leave Offer Course:</p>\n";
  body += "                <form action=\"/student-leave-offer-course\" "
          "method=\"POST\">\n";
  body += "                    <input type=\"text\" name=\"course-id\" "
          "placeholder=\"Enter Course Id\" class=\"curved-input\" required>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Leave Course</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *PostStudentJoinOfferCourseHandler::callback(Request *req) {
  std::string course_id = req->getBodyParam("course-id");
  std::cout << "course_id: " << course_id << std::endl;
  vector<string> input = {PUT_COMMAND, MY_COURSES_SUB_COMMAND,
                          SEPARATOR_CHARACTER, ID_ARG_COMMAND, course_id};
  program_.parseInput(input);
  Response *res = Response::redirect("/student-see-my-courses");
  return res;
}

Response *PostStudentLeaveOfferCourseHandler::callback(Request *req) {
  std::string course_id = req->getBodyParam("course-id");
  std::cout << "course_id: " << course_id << std::endl;
  vector<string> input = {DELETE_COMMAND, MY_COURSES_SUB_COMMAND,
                          SEPARATOR_CHARACTER, ID_ARG_COMMAND, course_id};
  program_.parseInput(input);
  Response *res = Response::redirect("/student-see-my-courses");
  return res;
}

Response *PostStudentChangeProfilePictureHandler::callback(Request *req) {
  std::string name = "Users_Storage/Profile_Pictures/";
  name += program_.getUserId();
  name += "-pp.png";
  std::string file = req->getBodyParam("file");
  utils::writeToFile(file, name);
  addAndLoadImage(name, server_);
  Response *res = Response::redirect("/student-change-profile-picture");
  vector<string> input = {POST_COMMAND, PROFILE_PHOTO_SUB_COMMAND,
                          SEPARATOR_CHARACTER, PHOTO_ARG_COMMAND, name};
  program_.parseInput(input);
  return res;
}

Response *PostStudentDeleteProfilePictureHandler::callback(Request *req) {
  std::string name = NONE_STRING;
  Response *res = Response::redirect("/student-change-profile-picture");
  program_.addProfilePhoto(name);
  return res;
}

Response *PostStudentSendPostHandler::callback(Request *req) {
  std::string name = "Users_Storage/Posts/";
  std::string file = req->getBodyParam("file");
  if (file != "") {
    name += program_.getUserId();
    name += "-post-id-";
    name += program_.currentPostId();
    name += ".png";
    utils::writeToFile(file, name);
    addAndLoadImage(name, server_);
  } else {
    name = NONE_STRING;
  }
  std::string title = req->getBodyParam("title");
  std::string message = req->getBodyParam("message");

  cout << name << endl;
  cout << file << endl;
  cout << title << endl;
  cout << message << endl;
  Response *res = Response::redirect("/student-send-post");
  vector<string> input = {POST_COMMAND,
                          POST_SUB_COMMAND,
                          SEPARATOR_CHARACTER,
                          TITLE_ARG_COMMAND,
                          title,
                          MESSAGE_ARG_COMMAND,
                          message,
                          IMAGE_ARG_COMMAND,
                          name};
  program_.parseInput(input);
  return res;
}

Response *PostStudentSeePersonalPageHandler::callback(Request *req) {
  std::string uid = req->getBodyParam("uid");
  ;
  cout << "uid: " << uid << endl;
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");
  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";
  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Student Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff; /* White */\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        nav a:hover {\n";
  body += "            color: #F0F8FF; /* Lighter white for hover */\n";
  body += "        }\n";
  body += "\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('student-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "            position: relative; /* Ensure relative positioning for "
          "absolute buttons */\n";
  body += "        }\n";
  body += "\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "\n";
  body += "        .user-profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Add styles for the Instagram-like posts */\n";
  body += "        .post-container {\n";
  body += "            max-width: 100%;\n";
  body += "            margin-top: 20px;\n";
  body += "            display: flex;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            position: relative; /* Ensure relative positioning for "
          "absolute buttons */\n";
  body += "        }\n";
  body += "\n";
  body += "        .post {\n";
  body += "            width: 100%;\n";
  body += "            display: none;\n";
  body += "        }\n";
  body += "\n";
  body += "        .post img {\n";
  body += "            max-width: 100%;\n";
  body += "            height: auto;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styling for navigation buttons */\n";
  body += "        .nav-button {\n";
  body += "            position: absolute;\n";
  body += "            top: 50%;\n";
  body += "            transform: translateY(-50%);\n";
  body += "            padding: 10px;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "            z-index: 1;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-left {\n";
  body += "            left: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-right {\n";
  body += "            right: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styles for the logout button (unchanged) */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "    <script>\n";
  body += "        let currentPost = 0;\n";
  body += "\n";
  body += "        function showPost(index) {\n";
  body +=
      "            const posts = document.getElementsByClassName('post');\n";
  body += "            if (index < 0) {\n";
  body += "                index = posts.length - 1;\n";
  body += "            } else if (index >= posts.length) {\n";
  body += "                index = 0;\n";
  body += "            }\n";
  body += "\n";
  body += "            for (let i = 0; i < posts.length; i++) {\n";
  body += "                posts[i].style.display = 'none';\n";
  body += "            }\n";
  body += "            posts[index].style.display = 'block';\n";
  body += "            currentPost = index;\n";
  body += "        }\n";
  body += "\n";
  body += "        function nextPost() {\n";
  body += "            showPost(currentPost + 1);\n";
  body += "        }\n";
  body += "\n";
  body += "        function prevPost() {\n";
  body += "            showPost(currentPost - 1);\n";
  body += "        }\n";
  body += "\n";
  body +=
      "        document.addEventListener('DOMContentLoaded', function() {\n";
  body += "            showPost(currentPost);\n";
  body += "        });\n";
  body += "    </script>\n";
  body += "</head>\n";
  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/student-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/student-send-post\">Send Post</a>\n";
  body += "                <a href=\"/student-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/student-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/student-see-my-courses\">See My "
          "Courses</a>\n";
  body += "                <a href=\"/student-join-offer-course\">Join Offer "
          "Course</a>\n";
  body += "                <a href=\"/student-leave-offer-course\">Leave Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "            <img src=\"" + program_.getUserProfilePicture(uid) +
          "\" alt=\"Profile Picture\" class=\"user-profile-picture\">\n";
  body += "                <!-- Instagram-like Posts Section -->\n";
  body += "                   " + program_.seePage(uid);
  body += "                <!-- Navigation Buttons -->\n";
  body += "                <button class=\"nav-button nav-button-left\" "
          "onclick=\"prevPost()\">Previous</button>\n";
  body += "                <button class=\"nav-button nav-button-right\" "
          "onclick=\"nextPost()\">Next</button>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *ProfessorShowOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #FFDAB9;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #FFDAB9;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #FFDAB9;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            color: #333;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #FFB6C1; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "            <p>Show Offer Courses:</p>\n";
  body += "            <p> id | name | capacity | professor</p>\n";
  body += "            <p class=\"output\">" + program_.seeAllOfferCourses() +
          "</p>\n";
  body += "            </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ProfessorHomeHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #FFDAB9;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #FFDAB9;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #FFDAB9;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            color: #333;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #FFB6C1; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ProfessorChangeProfilePictureHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #FFDAB9;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #FFDAB9;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #FFDAB9;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            color: #333;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #FFB6C1; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>\n";
  body += "                   " + program_.getUserId() + " | " +
          program_.getUserHeader() + "\n";
  body += "                </p>\n";
  body += "            </div>\n";
  body += "            <form action=\"/professor-change-profile-picture\" "
          "method=\"post\" enctype=\"multipart/form-data\" style=\"margin-top: "
          "20px;\">\n";
  body += "                <input type=\"file\" name=\"file\" "
          "style=\"margin-bottom: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Upload\" "
          "style=\"padding: 8px 20px; background-color: #FFDAB9; color: white; "
          "border: none; border-radius: 20px; cursor: pointer; transition: "
          "background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "            <form action=\"/professor-delete-profile-picture\" "
          "method=\"post\" style=\"margin-top: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Delete Profile "
          "Picture\" style=\"padding: 8px 20px; background-color: #FF6347; "
          "color: white; border: none; border-radius: 20px; cursor: pointer; "
          "transition: background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "        </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ProfessorSeePersonalPageHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #FFDAB9;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #FFDAB9;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #FFDAB9;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            color: #333;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #FFB6C1; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>UID | Name | Major | Semester/Position | "
          "Join/Offer Courses</p>\n";
  body += "                <p>\n";
  body += "                " + program_.AllUsersHeader();
  body += "                </p>\n";
  body += "                <form action=\"/professor-see-personal-page\" "
          "method=\"POST\">\n";
  body += "                    <input type=\"text\" name=\"uid\" "
          "placeholder=\"Enter Person Id\" class=\"curved-input\" required>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">See page</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *ProfessorSendPostHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #FFDAB9;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #FFDAB9;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #FFDAB9;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            color: #333;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #FFB6C1; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #FFDAB9; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Send Post:</p>\n";
  body += "                <form action=\"/professor-send-post\" "
          "method=\"POST\" enctype=\"multipart/form-data\">\n";
  body += "                    <input type=\"text\" name=\"title\" "
          "placeholder=\"Enter Title\" class=\"curved-input\" required>\n";
  body += "                    <textarea name=\"message\" placeholder=\"Enter "
          "Message\" class=\"curved-input\" rows=\"5\" required></textarea>\n";
  body += "                    <input type=\"file\" name=\"file\" "
          "value=\"NONE_STRING\" >\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Upload Post</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *PostProfessorChangeProfilePictureHandler::callback(Request *req) {
  std::string name = "Users_Storage/Profile_Pictures/";
  name += program_.getUserId();
  name += "-pp.png";
  std::string file = req->getBodyParam("file");
  utils::writeToFile(file, name);
  addAndLoadImage(name, server_);
  Response *res = Response::redirect("/professor-change-profile-picture");
  vector<string> input = {POST_COMMAND, PROFILE_PHOTO_SUB_COMMAND,
                          SEPARATOR_CHARACTER, PHOTO_ARG_COMMAND, name};
  program_.parseInput(input);
  return res;
}

Response *PostProfessorDeleteProfilePictureHandler::callback(Request *req) {
  std::string name = NONE_STRING;
  Response *res = Response::redirect("/professor-change-profile-picture");
  program_.addProfilePhoto(name);
  return res;
}

Response *PostProfessorSendPostHandler::callback(Request *req) {
  std::string name = "Users_Storage/Posts/";
  std::string file = req->getBodyParam("file");
  if (file != "") {
    name += program_.getUserId();
    name += "-post-id-";
    name += program_.currentPostId();
    name += ".png";
    utils::writeToFile(file, name);
    addAndLoadImage(name, server_);
  } else {
    name = NONE_STRING;
  }
  std::string title = req->getBodyParam("title");
  std::string message = req->getBodyParam("message");

  cout << name << endl;
  cout << file << endl;
  cout << title << endl;
  cout << message << endl;
  Response *res = Response::redirect("/professor-send-post");
  vector<string> input = {POST_COMMAND,
                          POST_SUB_COMMAND,
                          SEPARATOR_CHARACTER,
                          TITLE_ARG_COMMAND,
                          title,
                          MESSAGE_ARG_COMMAND,
                          message,
                          IMAGE_ARG_COMMAND,
                          name};
  program_.parseInput(input);
  return res;
}

Response *PostProfessorSeePersonalPageHandler::callback(Request *req) {
  std::string uid = req->getBodyParam("uid");
  ;
  cout << "uid: " << uid << endl;
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Professor Page</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #FFE4B5;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('professor-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .user-profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Add styles for the Instagram-like posts */\n";
  body += "        .post-container {\n";
  body += "            max-width: 100%;\n";
  body += "            margin-top: 20px;\n";
  body += "            display: flex;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            position: relative; /* Ensure relative positioning for "
          "absolute buttons */\n";
  body += "        }\n";
  body += "\n";
  body += "        .post {\n";
  body += "            width: 100%;\n";
  body += "            display: none;\n";
  body += "        }\n";
  body += "\n";
  body += "        .post img {\n";
  body += "            max-width: 100%;\n";
  body += "            height: auto;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styling for navigation buttons */\n";
  body += "        .nav-button {\n";
  body += "            position: absolute;\n";
  body += "            top: 50%;\n";
  body += "            transform: translateY(-50%);\n";
  body += "            padding: 10px;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "            z-index: 1;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-left {\n";
  body += "            left: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-right {\n";
  body += "            right: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styles for the logout button (unchanged) */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "    <script>\n";
  body += "        let currentPost = 0;\n";
  body += "\n";
  body += "        function showPost(index) {\n";
  body +=
      "            const posts = document.getElementsByClassName('post');\n";
  body += "            if (index < 0) {\n";
  body += "                index = posts.length - 1;\n";
  body += "            } else if (index >= posts.length) {\n";
  body += "                index = 0;\n";
  body += "            }\n";
  body += "\n";
  body += "            for (let i = 0; i < posts.length; i++) {\n";
  body += "                posts[i].style.display = 'none';\n";
  body += "            }\n";
  body += "            posts[index].style.display = 'block';\n";
  body += "            currentPost = index;\n";
  body += "        }\n";
  body += "\n";
  body += "        function nextPost() {\n";
  body += "            showPost(currentPost + 1);\n";
  body += "        }\n";
  body += "\n";
  body += "        function prevPost() {\n";
  body += "            showPost(currentPost - 1);\n";
  body += "        }\n";
  body += "\n";
  body +=
      "        document.addEventListener('DOMContentLoaded', function() {\n";
  body += "            showPost(currentPost);\n";
  body += "        });\n";
  body += "    </script>\n";
  body += "</head>";

  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body +=
      "                <a href=\"/professor-change-profile-picture\">Change "
      "Profile Picture</a>";
  body += "                <a href=\"/professor-send-post\">Send Post</a>";
  body += "                <a href=\"/professor-see-personal-page\">See "
          "Personal Page</a>";
  body += "                <a href=\"/professor-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "            <img src=\"" + program_.getUserProfilePicture(uid) +
          "\" alt=\"Profile Picture\" class=\"user-profile-picture\">\n";
  body += "                <!-- Instagram-like Posts Section -->\n";
  body += "                   " + program_.seePage(uid);
  body += "                <!-- Navigation Buttons -->\n";
  body += "                <button class=\"nav-button nav-button-left\" "
          "onclick=\"prevPost()\">Previous</button>\n";
  body += "                <button class=\"nav-button nav-button-right\" "
          "onclick=\"nextPost()\">Next</button>\n";
  body += "            </div>\n";
  body += "            </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *PostAdminAddOfferCourseHandler::callback(Request *req) {
  std::string course_id = req->getBodyParam("course-id");
  std::string professor_id = req->getBodyParam("professor-id");
  std::string capacity = req->getBodyParam("capacity");
  std::string time = req->getBodyParam("time");
  std::string exam_date = req->getBodyParam("exam-date");
  std::string class_number = req->getBodyParam("class-number");
  std::cout << "course_id: " << course_id << std::endl;
  std::cout << "professor_id: " << professor_id << std::endl;
  std::cout << "capacity: " << capacity << std::endl;
  std::cout << "time: " << time << std::endl;
  std::cout << "exam_date: " << exam_date << std::endl;
  std::cout << "class_number: " << class_number << std::endl;
  vector<string> input = {POST_COMMAND,
                          COURSE_OFFER_SUB_COMMAND,
                          SEPARATOR_CHARACTER,
                          COURSE_ID_ARG_COMMAND,
                          course_id,
                          PROFESSOR_ID_ARG_COMMAND,
                          professor_id,
                          CAPACITY_ARG_COMMAND,
                          capacity,
                          TIME_ARG_COMMAND,
                          time,
                          EXAM_DATE_ARG_COMMAND,
                          exam_date,
                          CLASS_NUMBER_ARG_COMMAND,
                          class_number};
  program_.parseInput(input);
  Response *res = Response::redirect("/admin-show-offer-course");
  return res;
}

Response *AdminShowOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #9370DB;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #9370DB;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #9370DB;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";
  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "            <p>Show Offer Courses:</p>\n";
  body += "            <p> id | name | capacity | professor</p>\n";
  body += "            <p class=\"output\">" + program_.seeAllOfferCourses() +
          "</p>\n";
  body += "            </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *AdminHomeHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #9370DB;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #9370DB;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #9370DB;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";
  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *AdminChangeProfilePictureHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #9370DB;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #9370DB;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #9370DB;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";
  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>\n";
  body += "                   " + program_.getUserId() + " | " +
          program_.getUserHeader() + "\n";
  body += "                </p>\n";
  body += "            </div>\n";
  body += "            <form action=\"/admin-change-profile-picture\" "
          "method=\"post\" enctype=\"multipart/form-data\" style=\"margin-top: "
          "20px;\">\n";
  body += "                <input type=\"file\" name=\"file\" "
          "style=\"margin-bottom: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Upload\" "
          "style=\"padding: 8px 20px; background-color: #B0E0E6; color: white; "
          "border: none; border-radius: 20px; cursor: pointer; transition: "
          "background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "            <form action=\"/admin-delete-profile-picture\" "
          "method=\"post\" style=\"margin-top: 10px;\">\n";
  body += "                <input type=\"submit\" value=\"Delete Profile "
          "Picture\" style=\"padding: 8px 20px; background-color: #FF6347; "
          "color: white; border: none; border-radius: 20px; cursor: pointer; "
          "transition: background-color 0.3s, transform 0.3s;\">\n";
  body += "            </form>\n";
  body += "        </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *AdminSeePersonalPageHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #9370DB;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #9370DB;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #9370DB;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";
  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>UID | Name | Major | Semester/Position | "
          "Join/Offer Courses</p>\n";
  body += "                <p>\n";
  body += "                " + program_.AllUsersHeader();
  body += "                </p>\n";
  body += "                <form action=\"/admin-see-personal-page\" "
          "method=\"POST\">\n";
  body += "                    <input type=\"text\" name=\"uid\" "
          "placeholder=\"Enter Person Id\" class=\"curved-input\" required>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">See page</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *AdminSendPostHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "";
  body += "        .curved-input {";
  body += "            width: 80%;";
  body += "            padding: 10px;";
  body += "            margin-top: 20px;";
  body += "            border-radius: 20px;";
  body += "            border: 2px solid #9370DB;";
  body += "            outline: none;";
  body += "            font-size: 1em;";
  body += "            font-weight: bold;";
  body += "            color: #9370DB;";
  body += "            background-color: #1e1e1e;";
  body += "            text-align: center;";
  body += "        }";
  body += "";
  body += "        .curved-input::placeholder {";
  body += "            color: #9370DB;";
  body += "        }";
  body += "        form button {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE; /* LightPink */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB; /* PeachPuff */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>";
  body += "<body>";
  body += "    <div class=\"container\">";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Send Post:</p>\n";
  body += "                <form action=\"/admin-send-post\" method=\"POST\" "
          "enctype=\"multipart/form-data\">\n";
  body += "                    <input type=\"text\" name=\"title\" "
          "placeholder=\"Enter Title\" class=\"curved-input\" required>\n";
  body += "                    <textarea name=\"message\" placeholder=\"Enter "
          "Message\" class=\"curved-input\" rows=\"5\" required></textarea>\n";
  body += "                    <input type=\"file\" name=\"file\" "
          "value=\"NONE_STRING\" >\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Upload Post</button>\n";
  body += "                </form>\n";
  body += "        </div>\n";
  body += "        </div>";
  body += "    </div>";
  body += "</body>";

  body += "</html>";
  res->setBody(body);
  return res;
}

Response *PostAdminChangeProfilePictureHandler::callback(Request *req) {
  std::string name = "Users_Storage/Profile_Pictures/";
  name += program_.getUserId();
  name += "-pp.png";
  std::string file = req->getBodyParam("file");
  utils::writeToFile(file, name);
  addAndLoadImage(name, server_);
  Response *res = Response::redirect("/admin-change-profile-picture");
  vector<string> input = {POST_COMMAND, PROFILE_PHOTO_SUB_COMMAND,
                          SEPARATOR_CHARACTER, PHOTO_ARG_COMMAND, name};
  program_.parseInput(input);
  return res;
}

Response *PostAdminDeleteProfilePictureHandler::callback(Request *req) {
  std::string name = NONE_STRING;
  Response *res = Response::redirect("/admin-change-profile-picture");
  program_.addProfilePhoto(name);
  return res;
}

Response *PostAdminSendPostHandler::callback(Request *req) {
  std::string name = "Users_Storage/Posts/";
  std::string file = req->getBodyParam("file");
  if (file != "") {
    name += program_.getUserId();
    name += "-post-id-";
    name += program_.currentPostId();
    name += ".png";
    utils::writeToFile(file, name);
    addAndLoadImage(name, server_);
  } else {
    name = NONE_STRING;
  }
  std::string title = req->getBodyParam("title");
  std::string message = req->getBodyParam("message");

  cout << name << endl;
  cout << file << endl;
  cout << title << endl;
  cout << message << endl;
  Response *res = Response::redirect("/admin-send-post");
  vector<string> input = {POST_COMMAND,
                          POST_SUB_COMMAND,
                          SEPARATOR_CHARACTER,
                          TITLE_ARG_COMMAND,
                          title,
                          MESSAGE_ARG_COMMAND,
                          message,
                          IMAGE_ARG_COMMAND,
                          name};
  program_.parseInput(input);
  return res;
}

Response *PostAdminSeePersonalPageHandler::callback(Request *req) {
  std::string uid = req->getBodyParam("uid");
  ;
  cout << "uid: " << uid << endl;
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");
  std::string body;

  body += "<!DOCTYPE html>";
  body += "<html lang=\"en\">";

  body += "<head>";
  body += "    <meta charset=\"UTF-8\">";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">";
  body += "    <title>Admin Page<</title>";
  body += "    <style>";
  body += "        body {";
  body += "            margin: 0;";
  body += "            font-family: Arial, sans-serif;";
  body += "            background-color: #121212;";
  body += "            color: #ffffff;";
  body += "        }";
  body += "";
  body += "        .container {";
  body += "            display: flex;";
  body += "            height: 100vh;";
  body += "        }";
  body += "";
  body += "        .left-panel {";
  body += "            width: 30%;";
  body += "            background-color: #1e1e1e;";
  body += "            padding: 20px;";
  body += "            box-sizing: border-box;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            align-items: center;";
  body += "        }";
  body += "";
  body += "        .profile-picture {";
  body += "            width: 100px;";
  body += "            height: 100px;";
  body += "            border-radius: 50%;";
  body += "            margin-bottom: 20px;";
  body += "            margin-top: 20%;";
  body += "        }";
  body += "";
  body += "        nav {";
  body += "            width: 100%;";
  body += "            text-align: center;";
  body += "            margin-top: 20px;";
  body += "        }";
  body += "";
  body += "        nav a {";
  body += "            display: block;";
  body += "            margin: 20px 0;";
  body += "            color: #ffffff;";
  body += "            text-decoration: none;";
  body += "            font-weight: bold;";
  body += "            transition: color 0.3s;";
  body += "        }";
  body += "";
  body += "        nav a:hover {";
  body += "            color: #BA55D3;";
  body += "        }";
  body += "";
  body += "        .right-panel {";
  body += "            width: 70%;";
  body += "            position: relative;";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;";
  body += "            background-size: cover;";
  body += "            display: flex;";
  body += "            flex-direction: column;";
  body += "            justify-content: center;";
  body += "            align-items: center;";
  body += "            color: white;";
  body += "        }";
  body += "";
  body += "        .background-container {";
  body += "            width: 80%;";
  body += "            text-align: center;";
  body += "            background: rgba(0, 0, 0, 0.7);";
  body += "            padding: 20px;";
  body += "            border-radius: 10px;";
  body += "        }";
  body += "";
  body += "        p {";
  body += "            font-weight: bold;";
  body += "            font-size: 1.2em;";
  body += "        }";
  body += "\n";
  body += "        .user-profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Add styles for the Instagram-like posts */\n";
  body += "        .post-container {\n";
  body += "            max-width: 100%;\n";
  body += "            margin-top: 20px;\n";
  body += "            display: flex;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            position: relative; /* Ensure relative positioning for "
          "absolute buttons */\n";
  body += "        }\n";
  body += "\n";
  body += "        .post {\n";
  body += "            width: 100%;\n";
  body += "            display: none;\n";
  body += "        }\n";
  body += "\n";
  body += "        .post img {\n";
  body += "            max-width: 100%;\n";
  body += "            height: auto;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styling for navigation buttons */\n";
  body += "        .nav-button {\n";
  body += "            position: absolute;\n";
  body += "            top: 50%;\n";
  body += "            transform: translateY(-50%);\n";
  body += "            padding: 10px;\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "            z-index: 1;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-left {\n";
  body += "            left: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button-right {\n";
  body += "            right: 10px;\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        .nav-button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "\n";
  body += "        /* Styles for the logout button (unchanged) */\n";
  body += "        form button {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:hover {\n";
  body += "            background-color: #87CEEB; /* LightSkyBlue */\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "\n";
  body += "        form button:active {\n";
  body +=
      "            background-color: #B0E0E6; /* Soft super light green */\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "    <script>\n";
  body += "        let currentPost = 0;\n";
  body += "\n";
  body += "        function showPost(index) {\n";
  body +=
      "            const posts = document.getElementsByClassName('post');\n";
  body += "            if (index < 0) {\n";
  body += "                index = posts.length - 1;\n";
  body += "            } else if (index >= posts.length) {\n";
  body += "                index = 0;\n";
  body += "            }\n";
  body += "\n";
  body += "            for (let i = 0; i < posts.length; i++) {\n";
  body += "                posts[i].style.display = 'none';\n";
  body += "            }\n";
  body += "            posts[index].style.display = 'block';\n";
  body += "            currentPost = index;\n";
  body += "        }\n";
  body += "\n";
  body += "        function nextPost() {\n";
  body += "            showPost(currentPost + 1);\n";
  body += "        }\n";
  body += "\n";
  body += "        function prevPost() {\n";
  body += "            showPost(currentPost - 1);\n";
  body += "        }\n";
  body += "\n";
  body +=
      "        document.addEventListener('DOMContentLoaded', function() {\n";
  body += "            showPost(currentPost);\n";
  body += "        });\n";
  body += "    </script>\n";
  body += "</head>\n";
  body += "<body>";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">";
  body += "            <nav>";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>";
  body += "                <a href=\"/admin-send-post\">Send Post</a>";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>";
  body += "                <a href=\"admin-show-offer-course\">Show Offer "
          "Courses</a>";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">";
  body += "                    <button type=\"submit\">Logout</button>";
  body += "                </form>";
  body += "            </nav>";
  body += "        </div>";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "            <img src=\"" + program_.getUserProfilePicture(uid) +
          "\" alt=\"Profile Picture\" class=\"user-profile-picture\">\n";
  body += "                <!-- Instagram-like Posts Section -->\n";
  body += "                   " + program_.seePage(uid);
  body += "                <!-- Navigation Buttons -->\n";
  body += "                <button class=\"nav-button nav-button-left\" "
          "onclick=\"prevPost()\">Previous</button>\n";
  body += "                <button class=\"nav-button nav-button-right\" "
          "onclick=\"nextPost()\">Next</button>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";

  res->setBody(body);
  return res;
}

Response *AdminAddOfferCourseHandler::callback(Request *req) {
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");

  std::string body;

  body += "<!DOCTYPE html>\n";
  body += "<html lang=\"en\">\n";
  body += "<head>\n";
  body += "    <meta charset=\"UTF-8\">\n";
  body += "    <meta name=\"viewport\" content=\"width=device-width, "
          "initial-scale=1.0\">\n";
  body += "    <title>Admin Page</title>\n";
  body += "    <style>\n";
  body += "        body {\n";
  body += "            margin: 0;\n";
  body += "            font-family: Arial, sans-serif;\n";
  body += "            background-color: #121212;\n";
  body += "            color: #ffffff;\n";
  body += "        }\n";
  body += "        .container {\n";
  body += "            display: flex;\n";
  body += "            height: 100vh;\n";
  body += "        }\n";
  body += "        .left-panel {\n";
  body += "            width: 30%;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            padding: 20px;\n";
  body += "            box-sizing: border-box;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            align-items: center;\n";
  body += "        }\n";
  body += "        .profile-picture {\n";
  body += "            width: 100px;\n";
  body += "            height: 100px;\n";
  body += "            border-radius: 50%;\n";
  body += "            margin-bottom: 20px;\n";
  body += "            margin-top: 20%;\n";
  body += "        }\n";
  body += "        nav {\n";
  body += "            width: 100%;\n";
  body += "            text-align: center;\n";
  body += "            margin-top: 20px;\n";
  body += "        }\n";
  body += "        nav a {\n";
  body += "            display: block;\n";
  body += "            margin: 20px 0;\n";
  body += "            color: #ffffff;\n";
  body += "            text-decoration: none;\n";
  body += "            font-weight: bold;\n";
  body += "            transition: color 0.3s;\n";
  body += "        }\n";
  body += "        nav a:hover {\n";
  body += "            color: #BA55D3;\n";
  body += "        }\n";
  body += "        .right-panel {\n";
  body += "            width: 70%;\n";
  body += "            position: relative;\n";
  body += "            background: url('admin-background.png') no-repeat "
          "center center;\n";
  body += "            background-size: cover;\n";
  body += "            display: flex;\n";
  body += "            flex-direction: column;\n";
  body += "            justify-content: center;\n";
  body += "            align-items: center;\n";
  body += "            color: white;\n";
  body += "        }\n";
  body += "        .background-container {\n";
  body += "            width: 80%;\n";
  body += "            text-align: center;\n";
  body += "            background: rgba(0, 0, 0, 0.7);\n";
  body += "            padding: 20px;\n";
  body += "            border-radius: 10px;\n";
  body += "        }\n";
  body += "        p {\n";
  body += "            font-weight: bold;\n";
  body += "            font-size: 1.2em;\n";
  body += "        }\n";
  body += "        .curved-input {\n";
  body += "            width: 80%;\n";
  body += "            padding: 10px;\n";
  body += "            margin-top: 20px;\n";
  body += "            border-radius: 20px;\n";
  body += "            border: 2px solid #9370DB;\n";
  body += "            outline: none;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            color: #9370DB;\n";
  body += "            background-color: #1e1e1e;\n";
  body += "            text-align: center;\n";
  body += "        }\n";
  body += "        .curved-input::placeholder {\n";
  body += "            color: #9370DB;\n";
  body += "        }\n";
  body += "        form button {\n";
  body += "            background-color: #9370DB;\n";
  body += "            color: white;\n";
  body += "            border: none;\n";
  body += "            padding: 10px 20px;\n";
  body += "            font-size: 1em;\n";
  body += "            font-weight: bold;\n";
  body += "            border-radius: 20px;\n";
  body += "            cursor: pointer;\n";
  body += "            transition: background-color 0.3s, transform 0.3s;\n";
  body += "        }\n";
  body += "        form button:hover {\n";
  body += "            background-color: #7B68EE;\n";
  body += "            transform: scale(1.05);\n";
  body += "        }\n";
  body += "        form button:active {\n";
  body += "            background-color: #9370DB;\n";
  body += "            transform: scale(1);\n";
  body += "        }\n";
  body += "    </style>\n";
  body += "</head>\n";
  body += "<body>\n";
  body += "    <div class=\"container\">\n";
  body += "        <div class=\"left-panel\">\n";
  body += "            <img src=\"" + program_.getProfilePicture() +
          "\" alt=\"Profile Picture\" class=\"profile-picture\">\n";
  body += "            <nav>\n";
  body += "                <a href=\"/admin-change-profile-picture\">Change "
          "Profile Picture</a>\n";
  body += "                <a href=\"/admin-send-post\">Send Post</a>\n";
  body += "                <a href=\"/admin-see-personal-page\">See Personal "
          "Page</a>\n";
  body += "                <a href=\"/admin-show-offer-course\">Show Offer "
          "Courses</a>\n";
  body += "                <a href=\"/admin-add-offer-course\">Add Offer "
          "Course</a>\n";
  body += "                <form action=\"/logout\" method=\"POST\" "
          "style=\"display: inline;\">\n";
  body += "                    <button type=\"submit\">Logout</button>\n";
  body += "                </form>\n";
  body += "            </nav>\n";
  body += "        </div>\n";
  body += "        <div class=\"right-panel\">\n";
  body += "            <div class=\"background-container\">\n";
  body += "                <p>Add Course:</p>\n";
  body += "                <form action=\"/admin-add-offer-course\" "
          "method=\"POST\">\n";
  body += "                    <label for=\"course-id\"></label>\n";
  body += "                    <input type=\"text\" id=\"course-id\" "
          "name=\"course-id\" class=\"curved-input\" placeholder=\"Enter "
          "Course ID\" required>\n";
  body += "                    <label for=\"professor-id\"></label>\n";
  body += "                    <input type=\"text\" id=\"professor-id\" "
          "name=\"professor-id\" class=\"curved-input\" placeholder=\"Enter "
          "Professor ID\" required>\n";
  body += "                    <label for=\"capacity\"></label>\n";
  body += "                    <input type=\"text\" id=\"capacity\" "
          "name=\"capacity\" class=\"curved-input\" placeholder=\"Enter "
          "Capacity\" required>\n";
  body += "                    <label for=\"time\"></label>\n";
  body += "                    <input type=\"text\" id=\"time\" name=\"time\" "
          "class=\"curved-input\" placeholder=\"Enter Time (Example: "
          "Sunday:13-15)\" required>\n";
  body += "                    <label for=\"exam-date\"></label>\n";
  body += "                    <input type=\"text\" id=\"exam-date\" "
          "name=\"exam-date\" class=\"curved-input\" placeholder=\"Enter Exam "
          "Date (Example: 1403/4/4)\" required>\n";
  body += "                    <label for=\"class-number\"></label>\n";
  body += "                    <input type=\"text\" id=\"class-number\" "
          "name=\"class-number\" class=\"curved-input\" placeholder=\"Enter "
          "Class Number\" required>\n";
  body += "                    <br>\n";
  body += "                    <br>\n";
  body += "                    <button type=\"submit\" "
          "class=\"submit-button\">Add Course</button>\n";
  body += "                </form>\n";
  body += "            </div>\n";
  body += "        </div>\n";
  body += "    </div>\n";
  body += "</body>\n";
  body += "</html>\n";
  res->setBody(body);
  return res;
}
