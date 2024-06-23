#ifndef FUNCTIONS_HPP_INCLUDE
#define FUNCTIONS_HPP_INCLUDE

#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "Program.hpp"
#include "CSVHandler.hpp"
#include "handlers.hpp"

void autoMapImageServerPaths(Server &server);
void addImagePathToAutoMapImageServer(const string imagePath);
void addAndLoadImage(string imagePath, Server &server);

#endif // FUNCTIONS_HPP_INCLUDE