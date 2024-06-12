#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <string>
#include <vector>

using namespace std;

enum class Permission { Guest, Student, Professor, Admin };

const string ADMIN_ID = "0";
const string ADMIN_PASSWORD = "UT_account";
const string ADMIN_NAME = "UT_account";

const bool REWRITE_INTERNAL_DATA_WHEN_PROGRAM_RUN = false;
const string INTERNAL_DATA_DIRECTORY_PATH = "./Internal_Databases/";
const string INTERNAL_DATA_POSTS_BASE_NAME = "-posts.csv";
const string INTERNAL_DATA_NOTIFICATIONS_BASE_NAME = "-notifications.csv";
const string INTERNAL_DATA_CONFIG_NAME = "configuration.csv";
const string INTERNAL_DATA_OFFER_COURSES_NAME = "offer-courses.csv";
const string INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME = "course-";
const string INTERNAL_DATA_TA_FORM_FORM_ID_PRE_NAME = "-post-";
const string INTERNAL_DATA_TA_FORM_PROFESSOR_ID_PRE_NAME = "professor-";
const string INTERNAL_DATA_TA_FORM_BASE_NAME = "-ta-form.csv";
const string POSTS_DATA_POST_TYPE = "post";
const string POSTS_DATA_TA_FORM_TYPE = "ta_form";

const string OK_OUTPUT = "OK";
const string EMPTY_OUTPUT = "Empty";
const string NOT_FOUND_OUTPUT = "Not Found";
const string BAD_REQUEST_OUTPUT = "Bad Request";
const string PERMISSION_DENIED_OUTPUT = "Permission Denied";

const string NONE_STRING = "NONE_STRING";
const string ACCEPT_TA_REQUEST_STRING = "accept";
const string REJECT_TA_REQUEST_STRING = "reject";

const vector<string> POST_COMMAND_LIST = {
    "login",      "logout",        "post",        "connect", "course_offer",
    "my_courses", "profile_photo", "course_post", "ta_form", "ta_request"};
const vector<string> PUT_COMMAND_LIST = {};
const vector<string> DELETE_COMMAND_LIST = {"post", "my_courses"};
const vector<string> GET_COMMAND_LIST = {
    "notification", "my_courses",     "personal_page", "courses",
    "post",         "course_channel", "course_post"};

const string POST_COMMAND = "POST";
const string DELETE_COMMAND = "DELETE";
const string GET_COMMAND = "GET";
const string PUT_COMMAND = "PUT";

const string LOGIN_SUB_COMMAND = "login";
const string LOGOUT_SUB_COMMAND = "logout";
const string POST_SUB_COMMAND = "post";
const string CONNECT_SUB_COMMAND = "connect";
const string PROFILE_PHOTO_SUB_COMMAND = "profile_photo";
const string NOTIFICATION_SUB_COMMAND = "notification";
const string PERSONAL_PAGE_SUB_COMMAND = "personal_page";
const string COURSES_SUB_COMMAND = "courses";
const string MY_COURSES_SUB_COMMAND = "my_courses";
const string COURSE_OFFER_SUB_COMMAND = "course_offer";
const string COURSE_CHANNEL_SUB_COMMAND = "course_channel";
const string COURSE_POST_SUB_COMMAND = "course_post";
const string TA_FORM_SUB_COMMAND = "ta_form";
const string TA_REQUEST_SUB_COMMAND = "ta_request";
const string CLOSE_TA_FORM_SUB_COMMAND = "close_ta_form";

const string SEPARATOR_CHARACTER = "?";

const string TITLE_ARG_COMMAND = "title";
const string MESSAGE_ARG_COMMAND = "message";
const string IMAGE_ARG_COMMAND = "image";
const string ID_ARG_COMMAND = "id";
const string PASSWORD_ARG_COMMAND = "password";
const string PHOTO_ARG_COMMAND = "photo";
const string POST_ID_ARG_COMMAND = "post_id";
const string PROFESSOR_ID_ARG_COMMAND = "professor_id";
const string FORM_ID_ARG_COMMAND = "form_id";
const string COURSE_ID_ARG_COMMAND = "course_id";
const string CAPACITY_ARG_COMMAND = "capacity";
const string TIME_ARG_COMMAND = "time";
const string EXAM_DATE_ARG_COMMAND = "exam_date";
const string CLASS_NUMBER_ARG_COMMAND = "class_number";

const string MAJORS_PATH = "./External_Databases/majors.csv";
const string STUDENTS_PATH = "./External_Databases/students.csv";
const string COURSES_PATH = "./External_Databases/courses.csv";
const string TEACHERS_PATH = "./External_Databases/teachers.csv";

#endif // CONSTANT_HPP
