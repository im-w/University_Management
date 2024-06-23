#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "functions.hpp"
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
  server.post("/logout", new LogoutHandler(program));

  server.get("/student", new StudentHomeHandler(program));
  server.get("/default-profile-picture.png", new ShowImage("static/default-profile-picture.png"));
  server.get("/student-background.png",
             new ShowImage("static/student-background.png"));
  server.get("/student-change-profile-picture",
             new StudentChangeProfilePictureHandler(program));
  server.post("/student-change-profile-picture",
             new PostStudentChangeProfilePictureHandler(program, server));
  server.post("/student-delete-profile-picture",
             new PostStudentDeleteProfilePictureHandler(program));
  server.get("/student-send-post",
             new StudentSendPostHandler(program));
  server.post("/student-send-post",
             new PostStudentSendPostHandler(program, server));
  server.get("/student-see-personal-page", new StudentSeePersonalPageHandler(program));
  server.post("/student-see-personal-page", new PostStudentSeePersonalPageHandler(program));
  server.get("/student-show-offer-course",
             new StudentShowOfferCourseHandler(program));
  server.get("/student-join-offer-course",
             new StudentJoinOfferCourseHandler(program));
  server.post("/student-join-offer-course",
             new PostStudentJoinOfferCourseHandler(program));
  server.get("/student-leave-offer-course",
             new StudentLeaveOfferCourseHandler(program));
  server.post("/student-leave-offer-course",
             new PostStudentLeaveOfferCourseHandler(program));
  server.get("/student-see-my-courses",
             new StudentShowMyOfferCourseHandler(program));

  server.get("/professor", new ProfessorHomeHandler(program));
  server.get("/default-profile-picture.png", new ShowImage("static/default-profile-picture.png"));
  server.get("/professor-background.png",
             new ShowImage("static/professor-background.png"));
  server.get("/professor-change-profile-picture",
             new ProfessorChangeProfilePictureHandler(program));
  server.post("/professor-change-profile-picture",
             new PostProfessorChangeProfilePictureHandler(program, server));
  server.post("/professor-delete-profile-picture",
             new PostProfessorDeleteProfilePictureHandler(program));
  server.get("/professor-send-post",
             new ProfessorSendPostHandler(program));
  server.post("/professor-send-post",
             new PostProfessorSendPostHandler(program, server));
  server.get("/professor-see-personal-page", new ProfessorSeePersonalPageHandler(program));
  server.post("/professor-see-personal-page", new PostProfessorSeePersonalPageHandler(program));
  server.get("/professor-show-offer-course",
             new ProfessorShowOfferCourseHandler(program));

  server.get("/admin", new AdminHomeHandler(program));
  server.get("/admin-background.png",
             new ShowImage("static/admin-background.png"));
  server.get("/admin-change-profile-picture",
             new AdminChangeProfilePictureHandler(program));
  server.post("/admin-change-profile-picture",
             new PostAdminChangeProfilePictureHandler(program, server));
  server.post("/admin-delete-profile-picture",
             new PostAdminDeleteProfilePictureHandler(program));
  server.get("/admin-send-post", new AdminSendPostHandler(program));
  server.post("/admin-send-post", new PostAdminSendPostHandler(program,server));
  server.get("/admin-see-personal-page", new AdminSeePersonalPageHandler(program));
  server.post("/admin-see-personal-page", new PostAdminSeePersonalPageHandler(program));
  server.get("/admin-show-offer-course",
             new AdminShowOfferCourseHandler(program));
  server.get("/admin-add-offer-course", new AdminAddOfferCourseHandler(program));
  server.post("/admin-add-offer-course", new PostAdminAddOfferCourseHandler(program));
}

int main(int argc, char **argv) {
  Program program(MAJORS_PATH, STUDENTS_PATH, COURSES_PATH, TEACHERS_PATH);
  program.setup();

  try {
    int port = argc > 1 ? stoi(argv[1]) : 5000;
    Server server(port);
    mapServerPaths(server, program);
    autoMapImageServerPaths(server);
    cout << "Server running on port: " << port << endl;
    server.run();
  } catch (const invalid_argument &e) {
    cerr << e.what() << endl;
  } catch (const Server::Exception &e) {
    cerr << e.getMessage() << endl;
  }
  return 0;
}
