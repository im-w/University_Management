#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "Program.hpp"
#include "handlers.hpp"

void mapServerPaths(Server &server, Program &program) {
  server.setNotFoundErrPage("static/404.html");

  server.get("/", new ShowPage("static/home.html"));
  server.get("/home.png", new ShowImage("static/home.png"));
  server.get("/home-background.png",
             new ShowImage("static/home-background.png"));

  server.get("/rand", new RandomNumberHandler());

  server.get("/login", new ShowPage("static/login.html"));
  server.post("/login", new LoginHandler(program));

  server.get("/student", new ShowPage("static/student.html"));
  server.get("/student-background.png",
             new ShowImage("static/student-background.png"));
  server.get("/student-change-profile-picture",
             new ShowPage("static/student-change-profile-picture.html"));
  server.get("/student-send-post",
             new ShowPage("static/student-send-post.html"));
  server.get("/student-show-offer-course",
             new ShowPage("static/student-show-offer-course.html"));
  server.get("/student-join-offer-course",
             new ShowPage("static/student-join-offer-course.html"));
  server.get("/student-leave-offer-course",
             new ShowPage("static/student-leave-offer-course.html"));
  server.get("/student-see-my-courses",
             new ShowPage("static/student-see-my-courses.html"));
  server.get("/logout", new ShowPage("static/student-show-offer-course.html"));

  server.get("/professor", new ShowPage("static/professor.html"));
  server.get("/professor-background.png",
             new ShowImage("static/professor-background.png"));
  server.get("/professor-change-profile-picture",
             new ShowPage("static/professor-change-profile-picture.html"));
  server.get("/professor-send-post",
             new ShowPage("static/professor-send-post.html"));
  server.get("/professor-show-offer-course",
             new ShowPage("static/professor-show-offer-course.html"));
  server.get("/logout", new ShowPage("static/student-show-offer-course.html"));

  server.get("/admin", new ShowPage("static/admin.html"));
  server.get("/admin-background.png",
             new ShowImage("static/admin-background.png"));
  server.get("/admin-change-profile-picture",
             new ShowPage("static/admin-change-profile-picture.html"));
  server.get("/admin-send-post", new ShowPage("static/admin-send-post.html"));
  server.get("/admin-show-offer-course",
             new ShowPage("static/admin-show-offer-course.html"));
  server.get("/admin-add-course", new ShowPage("static/admin-add-course.html"));
  server.get("/logout", new ShowPage("static/student-show-offer-course.html"));

  server.get("/up", new ShowPage("static/upload_form.html"));
  server.post("/up", new UploadHandler());
  server.get("/colors", new ColorHandler("template/colors.html"));
  server.get("/music", new ShowPage("static/music.html"));
  server.get("/music/moonlight.mp3",
             new ShowFile("static/moonlight.mp3", "audio/mpeg"));
}

int main(int argc, char **argv) {
  Program program(MAJORS_PATH, STUDENTS_PATH, COURSES_PATH, TEACHERS_PATH);
  program.setup();

  try {
    int port = argc > 1 ? std::stoi(argv[1]) : 5000;
    Server server(port);
    mapServerPaths(server, program);
    std::cout << "Server running on port: " << port << std::endl;
    server.run();
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
  } catch (const Server::Exception &e) {
    std::cerr << e.getMessage() << std::endl;
  }
  return 0;
}
