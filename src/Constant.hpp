#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <vector>
#include <string>

using namespace std;


enum class Permission {
    Guest,
    Student,
    Professor,
    Admin
};

const vector<string> POST_COMMAND_LIST = {"login","logout","post","connect","course_offer","my_courses"};
const vector<string> PUT_COMMAND_LIST = {};
const vector<string> DELETE_COMMAND_LIST = {"post","my_courses"};
const vector<string> GET_COMMAND_LIST = {"notification","my_courses","personal_page","courses","post"};
const string ADMIN_ID = "0";
const string ADMIN_PASSWORD = "UT_account";
const string ADMIN_NAME = "ADMIN";
const string NONE_STRING = "NONE_STRING";
const string OK_OUTPUT = "OK";
const string EMPTY_OUTPUT = "Empty";
const string NOT_FOUND_OUTPUT = "Not Found";
const string BAD_REQUEST_OUTPUT = "Bad Request";
const string PERMISSIN_DENIED_OUTPUT = "Permission Denied";
const string INTERNAL_DATA_DIRECTORY_PATH = "./Internal_Databases/";
const string INTERNAL_DATA_POSTS_BASE_NAME = "-posts.csv";
const string INTERNAL_DATA_NOTIFICATIONS_BASE_NAME = "-notifications.csv";
const string INTERNAL_DATA_CONFIG_NAME = "configuration.csv";
const string INTERNAL_DATA_OFFER_COURSES_NAME = "offer-courses.csv";





#endif // CONSTANT_HPP
