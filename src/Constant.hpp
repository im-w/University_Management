#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <string>
#include <vector>

using namespace std;

enum class Permission { Guest, Student, Professor, Admin };

const bool REWRITE_INTERNAL_DATA_WHEN_PROGRAM_RUN = true;
const vector<string> POST_COMMAND_LIST = {
    "login", "logout", "post", "connect", "course_offer", "my_courses"};
const vector<string> PUT_COMMAND_LIST = {};
const vector<string> DELETE_COMMAND_LIST = {"post", "my_courses"};
const vector<string> GET_COMMAND_LIST = {"notification", "my_courses",
                                         "personal_page", "courses", "post"};
const string ADMIN_ID = "0";
const string ADMIN_PASSWORD = "UT_account";
const string ADMIN_NAME = "UT_account";
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
const string POST_COMMAND = "POST";
const string DELETE_COMMAND = "DELETE";
const string GET_COMMAND = "GET";
const string PUT_COMMAND = "PUT";
const string LOGIN_SUB_COMMAND = "login";
const string LOGOUT_SUB_COMMAND = "logout";
const string POST_SUB_COMMAND = "post";
const string CONNECT_SUB_COMMAND = "connect";
const string NOTIFICATION_SUB_COMMAND = "notification";
const string PERSONAL_PAGE_SUB_COMMAND = "personal_page";
const string COURSES_SUB_COMMAND = "courses";
const string MY_COURSES_SUB_COMMAND = "my_courses";
const string COURSE_OFFER_SUB_COMMAND = "course_offer";

#endif // CONSTANT_HPP
