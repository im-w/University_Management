#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "handlers.hpp"

void mapServerPaths(Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/home-background.png", new ShowImage("static/home-background.png"));
    server.get("/rand", new RandomNumberHandler());
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());

    server.get("/student", new ShowPage("static/student.html"));
    server.get("/student-background.png", new ShowImage("static/student-background.png"));
    server.get("/professor", new ShowPage("static/professor.html"));
    server.get("/professor-background.png", new ShowImage("static/professor-background.png"));
    server.get("/admin", new ShowPage("static/admin.html"));
    server.get("/admin-background.png", new ShowImage("static/admin-background.png"));
    
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    server.get("/colors", new ColorHandler("template/colors.html"));
    server.get("/music", new ShowPage("static/music.html"));
    server.get("/music/moonlight.mp3", new ShowFile("static/moonlight.mp3", "audio/mpeg"));
}

int main(int argc, char** argv) {
    try {
        int port = argc > 1 ? std::stoi(argv[1]) : 5000;
        Server server(port);
        mapServerPaths(server);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
