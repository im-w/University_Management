#include "Program.hpp"
#include "Admin.hpp"
#include "Constant.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "TimeRange.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Program::Program(const string &_majorsFile_path,
                 const string &_studentsFile_path,
                 const string &_coursesFile_path,
                 const string &_professorsFile_path)
    : majorsFile_path(_majorsFile_path), studentsFile_path(_studentsFile_path),
      coursesFile_path(_coursesFile_path),
      professorsFile_path(_professorsFile_path), majorsCSV(majorsFile_path),
      studentsCSV(studentsFile_path), coursesCSV(coursesFile_path),
      professorsCSV(professorsFile_path), permission(Permission::Guest),
      open(true) {}

void Program::run() {
  setup();
  while (open) {
    test();
    vector<string> input = getInputVectorFromTerminal();
    parseInput(input);
  }
}

void Program::test() {} //? delete when code completed

void Program::setup() {
  if (!createFileIfNotExists(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME)) {
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    setupOfferCoursesFile(offer_courses);
  }
  if (!createFileIfNotExists(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_CONFIG_NAME)) {
    CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
    setupConfigFile(config);
  }
  CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
  setupUser(ADMIN_ID, config);

  vector<string> students_id = studentsCSV.findColumn("sid");
  for (const string &id : students_id) {
    setupUser(id, config);
  }
  vector<string> professors_id = professorsCSV.findColumn("pid");
  for (const string &id : professors_id) {
    setupUser(id, config);
  }
}

bool Program::createFileIfNotExists(const string &filename) {
  if (REWRITE_INTERNAL_DATA_WHEN_PROGRAM_RUN == true) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
      bool IsExsists = false;
      return IsExsists;
    } else {
      throw runtime_error("Failed to create file: " + filename);
    }
    return false;
  }
  bool IsExsists = false;
  ifstream infile(filename);
  if (!infile.is_open()) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
      IsExsists = false;
      return IsExsists;
    } else {
      throw runtime_error("Failed to create file: " + filename);
    }
  } else {
    IsExsists = true;
    return IsExsists;
  }
}

void Program::setupConfigFile(CSVHandler &File) {
  vector<string> row = {"uid", "last_post_id", "connections",
                        "profile_photo_path"};
  File.addRowToMatris(row);
  File.writeMatrisToCSV();
}
void Program::setupOfferCoursesFile(CSVHandler &File) {
  vector<string> row = {"offer_course_id", "course_id",   "professor_id",
                        "capacity",        "time",        "exam_date",
                        "class_number",    "students_id", "authors_id",
                        "last_post_id"};
  File.addRowToMatris(row);
  File.writeMatrisToCSV();
}

void Program::setupUser(const string &id, CSVHandler &config) {
  if (!createFileIfNotExists(INTERNAL_DATA_DIRECTORY_PATH + id +
                             INTERNAL_DATA_POSTS_BASE_NAME)) {
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH + id +
                     INTERNAL_DATA_POSTS_BASE_NAME);
    setupPostsFile(posts);
  }
  if (!createFileIfNotExists(INTERNAL_DATA_DIRECTORY_PATH + id +
                             INTERNAL_DATA_NOTIFICATIONS_BASE_NAME)) {
    CSVHandler notifications(INTERNAL_DATA_DIRECTORY_PATH + id +
                             INTERNAL_DATA_NOTIFICATIONS_BASE_NAME);
    setupNotificationsFile(notifications);
  }
  if (!config.isExists("uid", id)) {
    if (id != ADMIN_ID) {
      config.appendFieldInMatris("uid", ADMIN_ID, "connections", ";" + id);
    }
    vector<string> row = {id, "0", "0", NONE_STRING};
    config.addRowToMatris(row);
    config.writeMatrisToCSV();
  }
}

void Program::setupPostsFile(CSVHandler &File) {
  vector<string> row = {"post_id", "title", "massage", "attach_path", "type"};
  File.addRowToMatris(row);
  File.writeMatrisToCSV();
}

void Program::setupCoursePostsFile(CSVHandler &File) {
  vector<string> row = {"post_id",     "title", "massage",
                        "attach_path", "type",  "author_name"};
  File.addRowToMatris(row);
  File.writeMatrisToCSV();
}

void Program::setupNotificationsFile(CSVHandler &File) {
  vector<string> row = {"uid", "name", "massage"};
  File.addRowToMatris(row);
  File.writeMatrisToCSV();
}

vector<string> Program::getInputVectorFromTerminal() {
  string input;
  getline(cin, input);
  vector<string> result;
  string word;
  bool inQuotes = false;
  for (char c : input) {
    if (c == '\"') {
      inQuotes = !inQuotes;
      if (!inQuotes) {
        result.push_back(word);
        word.clear();
      }
    } else if (c == ' ' && !inQuotes) {
      if (!word.empty()) {
        result.push_back(word);
        word.clear();
      }
    } else {
      word += c;
    }
  }
  if (!word.empty()) {
    result.push_back(word);
  }
  return result;
}

void Program::parseInput(const vector<string> &input) {
  if (permission == Permission::Guest) {
    checkLoginCommand(input);
  } else if (permission == Permission::Student) {
    checkStudentCommand(input);
  } else if (permission == Permission::Professor) {
    checkProfessorCommand(input);
  } else if (permission == Permission::Admin) {
    checkAdminCommand(input);
  } else {
    cerr << "Error: Invalid permission" << endl;
    abort();
  }
}

void Program::checkLoginCommand(const vector<string> &input) {
  if (input[0] == POST_COMMAND) {
    if (isCommandInList(input[1], POST_COMMAND_LIST)) {
      if (input[1] == LOGIN_SUB_COMMAND) {
        string id = NONE_STRING;
        string password = NONE_STRING;
        for (size_t i = 3; i < input.size(); i++) {
          if (input[i] == "id") {
            if (i + 1 < input.size()) {
              id = input[i + 1];
            }
          } else if (input[i] == "password") {
            if (i + 1 < input.size()) {
              password = input[i + 1];
            }
          }
        }
        if (id == NONE_STRING || password == NONE_STRING ||
            (!isNormalNumber(id))) {

          cout << BAD_REQUEST_OUTPUT << endl;
          return;
        }
        login(id, password);
      } else {
        cout << PERMISSIN_DENIED_OUTPUT << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == PUT_COMMAND) {
    if (isCommandInList(input[1], PUT_COMMAND_LIST)) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == GET_COMMAND) {
    if (isCommandInList(input[1], GET_COMMAND_LIST)) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == DELETE_COMMAND) {
    if (isCommandInList(input[1], DELETE_COMMAND_LIST)) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else {
    cout << BAD_REQUEST_OUTPUT << endl;
  }
}

bool Program::isCommandInList(const string &command,
                              const vector<string> &command_list) {
  for (const string &cmd : command_list) {
    if (cmd == command) {
      return true;
    }
  }
  return false;
}

void Program::login(const string id, const string password) {
  if (studentsCSV.isExists("sid", id)) {
    if (studentsCSV.findField("sid", id, "password") == password) {
      user_ptr = new Student(id, studentsCSV.findField("sid", id, "name"),
                             studentsCSV.findField("sid", id, "major_id"),
                             studentsCSV.findField("sid", id, "semester"));
      permission = Permission::Student;
      cout << OK_OUTPUT << endl;
    } else {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    }
  } else if (professorsCSV.isExists("pid", id)) {
    if (professorsCSV.findField("pid", id, "password") == password) {
      user_ptr = new Professor(id, professorsCSV.findField("pid", id, "name"),
                               professorsCSV.findField("pid", id, "major_id"),
                               professorsCSV.findField("pid", id, "position"));
      permission = Permission::Professor;
      cout << OK_OUTPUT << endl;
    } else {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    }
  } else if (id == ADMIN_ID) {
    if (password == ADMIN_PASSWORD) {
      user_ptr = new Admin(id, ADMIN_NAME);
      permission = Permission::Admin;
      cout << OK_OUTPUT << endl;
    } else {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

void Program::logout() {
  permission = Permission::Guest;
  delete user_ptr;
  cout << OK_OUTPUT << endl;
}

void Program::post(const string title, const string message,
                   const string attach = NONE_STRING) {
  CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
  string uid = user_ptr->getId();
  string last_post_id = config.findField("uid", uid, "last_post_id");
  last_post_id = to_string(stoi(last_post_id) + 1);
  CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH + uid +
                   INTERNAL_DATA_POSTS_BASE_NAME);
  vector<string> row = {};
  if (attach == NONE_STRING) {
    row = {last_post_id, title, message, NONE_STRING, POSTS_DATA_POST_TYPE};
  } else {
    row = {last_post_id, title, message, attach, POSTS_DATA_POST_TYPE};
  }
  if (row.empty()) {
    throw runtime_error("row you want add created by post function is empty");
  }
  posts.addRowToMatris(row);
  posts.writeMatrisToCSV();
  config.updateFieldInMatris("uid", uid, "last_post_id", last_post_id);
  config.writeMatrisToCSV();
  vector<string> connections =
      splitString(config.findField("uid", uid, "connections"), ';');
  for (const string &id : connections) {
    sendNotification(uid, user_ptr->getName(), id, "New Post");
  }
  cout << OK_OUTPUT << endl;
}

void Program::channelPost(const string offer_course_id, const string title,
                          const string message,
                          const string attach = NONE_STRING) {
  if (isOfferCourseIdValid(offer_course_id)) {
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    string uid = user_ptr->getId();
    bool has_permission = isExists(
        uid, splitString(offer_courses.findField("offer_course_id",
                                                 offer_course_id, "authors_id"),
                         ';'));
    if (!has_permission) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
      return;
    }
    string last_post_id = offer_courses.findField(
        "offer_course_id", offer_course_id, "last_post_id");
    last_post_id = to_string(stoi(last_post_id) + 1);
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH +
                     INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME +
                     offer_course_id + INTERNAL_DATA_POSTS_BASE_NAME);
    vector<string> row = {};
    if (attach == NONE_STRING) {
      row = {
          last_post_id,       title, message, NONE_STRING, POSTS_DATA_POST_TYPE,
          user_ptr->getName()};
    } else {
      row = {last_post_id,       title, message, attach, POSTS_DATA_POST_TYPE,
             user_ptr->getName()};
    }
    if (row.empty()) {
      throw runtime_error("row you want add created by post function is empty");
    }
    posts.addRowToMatris(row);
    posts.writeMatrisToCSV();
    offer_courses.updateFieldInMatris("offer_course_id", offer_course_id,
                                      "last_post_id", last_post_id);
    offer_courses.writeMatrisToCSV();
    vector<string> connections =
        splitString(offer_courses.findField("offer_course_id", offer_course_id,
                                            "students_id"),
                    ';');
    for (const string &id : connections) {
      if (id == uid) {
        continue;
      }
      sendNotification(offer_course_id,
                       coursesCSV.findField(
                           "cid",
                           offer_courses.findField(
                               "offer_course_id", offer_course_id, "course_id"),
                           "name"),
                       id, "New Course Post");
    }
    cout << OK_OUTPUT << endl;
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

void Program::deletePost(const string id) {
  string uid = user_ptr->getId();
  CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH + uid +
                   INTERNAL_DATA_POSTS_BASE_NAME);
  try {
    posts.deleteRowOfMatris("post_id", id);
  } catch (const exception &e) {
    cout << NOT_FOUND_OUTPUT << endl;
    return;
  }
  posts.writeMatrisToCSV();
  cout << OK_OUTPUT << endl;
}
void Program::printUserHeader(const string id) {
  if (id == ADMIN_ID) {
    cout << ADMIN_NAME << endl;
    return;
  }
  vector<string> user_row = {};
  vector<string> courses_name = {};
  try {
    user_row = studentsCSV.findRow("sid", id);
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    vector<string> students_ids = offer_courses.findColumn("students_id");
    vector<string> course_ids = offer_courses.findColumn("course_id");
    size_t index = 0;
    for (const string &students_id : students_ids) {
      vector<string> ids = splitString(students_id, ';');
      for (const string &sid : ids) {
        if (sid == id) {
          courses_name.push_back(
              coursesCSV.findField("cid", course_ids[index], "name"));
        }
      }
      index++;
    }
  } catch (const exception &e) {
    user_row = professorsCSV.findRow("pid", id);
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    vector<string> professor_ids = offer_courses.findColumn("professor_id");
    vector<string> course_ids = offer_courses.findColumn("course_id");
    size_t index = 0;
    for (const string &professor_id : professor_ids) {
      if (professor_id == id) {
        courses_name.push_back(
            coursesCSV.findField("cid", course_ids[index], "name"));
      }
      index++;
    }
  }
  if (courses_name.empty()) {
    cout << user_row[1] << " "
         << majorsCSV.findField("mid", user_row[2], "major") << " "
         << user_row[3] << " " << endl;
  } else {
    cout << user_row[1] << " "
         << majorsCSV.findField("mid", user_row[2], "major") << " "
         << user_row[3] << " " << connectString(courses_name, ',') << endl;
  }
}

void Program::seePage(const string id) {
  if (isUserIdValid(id)) {
    printUserHeader(id);
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH + id +
                     INTERNAL_DATA_POSTS_BASE_NAME);
    vector<vector<string>> all_posts_matris = posts.bodyMatris();
    reverse(all_posts_matris.begin(), all_posts_matris.end());
    for (const vector<string> &post : all_posts_matris) {
      if (post[4] == POSTS_DATA_POST_TYPE) {
        cout << post[0] << " \"" << post[1] << "\"" << endl;
      }
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

void Program::seeChannelPage(const string id) {
  if (isOfferCourseIdValid(id)) {
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    string uid = user_ptr->getId();
    bool has_permission =
        isExists(uid, splitString(offer_courses.findField("offer_course_id", id,
                                                          "authors_id"),
                                  ';'));
    if (!has_permission) {
      has_permission =
          isExists(uid, splitString(offer_courses.findField("offer_course_id",
                                                            id, "students_id"),
                                    ';'));
    }
    if (!has_permission) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
      return;
    }
    seeOfferCourses(id);
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH +
                     INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME + id +
                     INTERNAL_DATA_POSTS_BASE_NAME);
    vector<vector<string>> all_posts_matris = posts.bodyMatris();
    reverse(all_posts_matris.begin(), all_posts_matris.end());
    for (const vector<string> &post : all_posts_matris) {
      if (post[4] == POSTS_DATA_POST_TYPE) {
        cout << post[0] << " " << post[5] << " \"" << post[1] << "\"" << endl;
      }
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}
void Program::getPost(const string id, const string post_id) {
  if (isUserIdValid(id)) {
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH + id +
                     INTERNAL_DATA_POSTS_BASE_NAME);
    if (posts.isExists("post_id", post_id)) {
      printUserHeader(id);
      vector<string> post = posts.findRow("post_id", post_id);
      if (post[4] == POSTS_DATA_POST_TYPE) {
        cout << post[0] << " \"" << post[1] << "\"" << " \"" << post[2] << "\""
             << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
      return;
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
    return;
  }
}
void Program::getChannelPost(const string id, const string post_id) {
  if (isOfferCourseIdValid(id)) {
    CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_NAME);
    string uid = user_ptr->getId();
    bool has_permission =
        isExists(uid, splitString(offer_courses.findField("offer_course_id", id,
                                                          "authors_id"),
                                  ';'));
    if (!has_permission) {
      has_permission =
          isExists(uid, splitString(offer_courses.findField("offer_course_id",
                                                            id, "students_id"),
                                    ';'));
    }
    if (!has_permission) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
      return;
    }
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH +
                     INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME + id +
                     INTERNAL_DATA_POSTS_BASE_NAME);
    if (posts.isExists("post_id", post_id)) {
      seeOfferCourses(id);
      vector<string> post = posts.findRow("post_id", post_id);
      if (post[4] == POSTS_DATA_POST_TYPE) {
        cout << post[0] << " " << post[5] << " \"" << post[1] << "\"" << " \""
             << post[2] << "\"" << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
      return;
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
    return;
  }
}

void Program::seeAllOfferCourses() {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  vector<vector<string>> body_offer_courses = offer_courses.bodyMatris();
  for (const vector<string> &line : body_offer_courses) {
    cout << line[0] << " " << coursesCSV.findField("cid", line[1], "name")
         << " " << line[3] << " "
         << professorsCSV.findField("pid", line[2], "name") << endl;
  }
}
void Program::seeOfferCourses(const string &id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  if (isOfferCourseIdValid(id)) {
    vector<string> line = offer_courses.findRow("offer_course_id", id);
    cout << line[0] << " " << coursesCSV.findField("cid", line[1], "name")
         << " " << line[3] << " "
         << professorsCSV.findField("pid", line[2], "name") << " " << line[4]
         << " " << line[5] << " " << line[6] << endl;
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

void Program::connect(const string id) {
  string uid = user_ptr->getId();
  if (id == uid) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
  vector<string> connections =
      splitString(config.findField("uid", uid, "connections"), ';');
  for (const string &config_uid : connections) {
    if (config_uid == id) {
      cout << BAD_REQUEST_OUTPUT << endl;
      return;
    }
  }
  try {
    string connection = (";" + id);
    config.appendFieldInMatris("uid", uid, "connections", connection);
    connection = (";" + uid);
    config.appendFieldInMatris("uid", id, "connections", connection);
    config.writeMatrisToCSV();
  } catch (const exception &e) {
    cout << NOT_FOUND_OUTPUT << endl;
    return;
  }
  cout << OK_OUTPUT << endl;
}

void Program::addProfilePhoto(const string photo) {
  CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
  config.updateFieldInMatris("uid", user_ptr->getId(), "profile_photo_path",
                             photo);
  config.writeMatrisToCSV();
}

void Program::sendNotification(const string sender_id, const string sender_name,
                               const string send_to_id, const string massage) {
  vector<string> row = {sender_id, sender_name, massage};
  CSVHandler notifications(INTERNAL_DATA_DIRECTORY_PATH + send_to_id +
                           INTERNAL_DATA_NOTIFICATIONS_BASE_NAME);
  notifications.addRowToMatris(row);
  notifications.writeMatrisToCSV();
}

void Program::getNotification() {
  string uid = user_ptr->getId();
  CSVHandler notifications(INTERNAL_DATA_DIRECTORY_PATH + uid +
                           INTERNAL_DATA_NOTIFICATIONS_BASE_NAME);
  if (notifications.isEmpty()) {
    cout << EMPTY_OUTPUT << endl;
    return;
  }
  vector<vector<string>> notification_body = notifications.bodyMatris();
  reverse(notification_body.begin(), notification_body.end());
  for (const vector<string> &notification : notification_body) {
    cout << notification[0] << " " << notification[1] << ": " << notification[2]
         << endl;
  }
  notifications.cleanBodyOfMatris();
  notifications.writeMatrisToCSV();
}

void Program::courseOffer(string course_id, string professor_id,
                          string capacity, string time, string exam_date,
                          string class_number) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  vector<string> offer_course_ids = offer_courses.findColumn("offer_course_id");
  string last_offer_course_id = "0";
  if (offer_course_ids.size() != 0) {
    last_offer_course_id = offer_course_ids.back();
  }
  string offer_course_id = to_string((stoi(last_offer_course_id) + 1));
  vector<string> row = {offer_course_id,
                        course_id,
                        professor_id,
                        capacity,
                        time,
                        exam_date,
                        class_number,
                        "0",
                        ("0;" + professor_id),
                        "0"};
  offer_courses.addRowToMatris(row);
  offer_courses.writeMatrisToCSV();
  string professor_name = professorsCSV.findField("pid", professor_id, "name");
  CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
  vector<string> connections =
      splitString(config.findField("uid", ADMIN_ID, "connections"), ';');
  for (const string &id : connections) {
    sendNotification(professor_id, professor_name, id, "New Course Offering");
  }
  if (!createFileIfNotExists(INTERNAL_DATA_DIRECTORY_PATH +
                             INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME +
                             offer_course_id + INTERNAL_DATA_POSTS_BASE_NAME)) {
    CSVHandler posts(INTERNAL_DATA_DIRECTORY_PATH +
                     INTERNAL_DATA_OFFER_COURSES_POSTS_PRE_NAME +
                     offer_course_id + INTERNAL_DATA_POSTS_BASE_NAME);
    setupCoursePostsFile(posts);
  }
  cout << OK_OUTPUT << endl;
}

void Program::studentAddCourse(string id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  if (offer_courses.isExists("offer_course_id", id)) {
    vector<string> students_ids = splitString(
        offer_courses.findField("offer_course_id", id, "students_id"), ';');
    for (const string &sid : students_ids) {
      if (sid == user_ptr->getId()) {
        cout << PERMISSIN_DENIED_OUTPUT << endl;
        return;
      }
    }
    offer_courses.appendFieldInMatris("offer_course_id", id, "students_id",
                                      (";" + user_ptr->getId()));
    offer_courses.writeMatrisToCSV();
    CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH + INTERNAL_DATA_CONFIG_NAME);
    vector<string> connections =
        splitString(config.findField("uid", ADMIN_ID, "connections"), ';');
    for (const string &id : connections) {
      sendNotification(user_ptr->getId(), user_ptr->getName(), id,
                       "Get Course");
    }
    cout << OK_OUTPUT << endl;
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

void Program::studentDeleteCourse(string id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  if (offer_courses.isExists("offer_course_id", id)) {

    vector<string> students_id = splitString(
        offer_courses.findField("offer_course_id", id, "students_id"), ';');
    size_t size_students_id = students_id.size();
    students_id.erase(
        remove(students_id.begin(), students_id.end(), user_ptr->getId()),
        students_id.end());
    if (size_students_id == students_id.size()) {
      cout << NOT_FOUND_OUTPUT << endl;
    } else {

      offer_courses.updateFieldInMatris("offer_course_id", id, "students_id",
                                        connectString(students_id, ';'));
      offer_courses.writeMatrisToCSV();
      CSVHandler config(INTERNAL_DATA_DIRECTORY_PATH +
                        INTERNAL_DATA_CONFIG_NAME);
      vector<string> connections =
          splitString(config.findField("uid", ADMIN_ID, "connections"), ';');
      for (const string &id : connections) {
        sendNotification(user_ptr->getId(), user_ptr->getName(), id,
                         "Delete Course");
      }
      cout << OK_OUTPUT << endl;
    }
  } else {
    cout << NOT_FOUND_OUTPUT << endl;
  }
}

vector<size_t> Program::studentCousesIndex() {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  vector<size_t> userCoursesIndex = {};
  vector<string> students_ids = offer_courses.findColumn("students_id");
  size_t index = 0;
  for (const string &students_id : students_ids) {
    vector<string> ids = splitString(students_id, ';');
    for (const string &id : ids) {
      if (id == user_ptr->getId()) {
        userCoursesIndex.push_back(index);
      }
    }
    index++;
  }
  return userCoursesIndex;
}

void Program::studentAllCourses() {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  if (offer_courses.isEmpty()) {
    cout << EMPTY_OUTPUT << endl;
    return;
  }
  vector<vector<string>> body_offer_courses = offer_courses.bodyMatris();
  vector<size_t> userCoursesIndex = studentCousesIndex();
  if (userCoursesIndex.empty()) {
    cout << EMPTY_OUTPUT << endl;
    return;
  }
  for (const size_t &index : userCoursesIndex) {
    cout << body_offer_courses[index][0] << " "
         << coursesCSV.findField("cid", body_offer_courses[index][1], "name")
         << " " << body_offer_courses[index][3] << " "
         << professorsCSV.findField("pid", body_offer_courses[index][2], "name")
         << " " << body_offer_courses[index][4] << " "
         << body_offer_courses[index][5] << " " << body_offer_courses[index][6]
         << endl;
  }
}

void Program::checkUserCommand(const vector<string> &input) {
  if (input[0] == POST_COMMAND) {
    if (isCommandInList(input[1], POST_COMMAND_LIST)) {
      if (input[1] == LOGOUT_SUB_COMMAND) {
        logout();
      } else if (input[1] == POST_SUB_COMMAND) {
        postPostCommand(input);
      } else if (input[1] == CONNECT_SUB_COMMAND) {
        postConnectCommand(input);
      } else if (input[1] == PROFILE_PHOTO_SUB_COMMAND) {
        postProfilePhotoCommand(input);
      } else if (input[1] == COURSE_POST_SUB_COMMAND) {
        postcoursePostCommand(input);
      } else {
        cout << PERMISSIN_DENIED_OUTPUT << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == DELETE_COMMAND) {
    if (isCommandInList(input[1], DELETE_COMMAND_LIST)) {
      if (input[1] == POST_SUB_COMMAND) {
        deletePostCommand(input);
      } else {
        cout << PERMISSIN_DENIED_OUTPUT << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == GET_COMMAND) {
    if (isCommandInList(input[1], GET_COMMAND_LIST)) {
      if (input[1] == NOTIFICATION_SUB_COMMAND) {
        getNotification();
      } else if (input[1] == PERSONAL_PAGE_SUB_COMMAND) {
        getPersonalPageCommand(input);
      } else if (input[1] == COURSES_SUB_COMMAND) {
        getCoursesCommand(input);
      } else if (input[1] == POST_SUB_COMMAND) {
        getPostCommand(input);
      } else if (input[1] == COURSE_CHANNEL_SUB_COMMAND) {
        getCourseChannelCommand(input);
      } else if (input[1] == COURSE_POST_SUB_COMMAND) {
        getCoursePostCommand(input);
      } else {
        cout << PERMISSIN_DENIED_OUTPUT << endl;
      }
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else if (input[0] == PUT_COMMAND) {
    if (isCommandInList(input[1], PUT_COMMAND_LIST)) {
      cout << PERMISSIN_DENIED_OUTPUT << endl;
    } else {
      cout << NOT_FOUND_OUTPUT << endl;
    }
  } else {
    cout << BAD_REQUEST_OUTPUT << endl;
  }
}

void Program::checkStudentCommand(const vector<string> &input) {
  try {
    checkStudentSpecificCommand(input);
  } catch (const runtime_error &e) {
    if (std::string(e.what()) == "command not handle in this function") {
      checkUserCommand(input);
    } else {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}
void Program::checkProfessorCommand(const vector<string> &input) {
  try {
    checkProfessorSpecificCommand();
  } catch (const runtime_error &e) {
    if (std::string(e.what()) == "command not handle in this function") {
      checkUserCommand(input);
    } else {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}
void Program::checkAdminCommand(const vector<string> &input) {
  try {
    checkAdminSpecificCommand(input);
  } catch (const runtime_error &e) {
    if (std::string(e.what()) == "command not handle in this function") {
      checkUserCommand(input);
    } else {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}
void Program::checkStudentSpecificCommand(const vector<string> &input) {
  if (input[0] == PUT_COMMAND) {
    if (input[1] == MY_COURSES_SUB_COMMAND) {
      studentPutMycourseCommand(input);
    } else {
      throw runtime_error("command not handle in this function");
    }
  } else if (input[0] == GET_COMMAND) {
    if (input[1] == MY_COURSES_SUB_COMMAND) {
      studentAllCourses();
    } else {
      throw runtime_error("command not handle in this function");
    }
  } else if (input[0] == DELETE_COMMAND) {
    if (input[1] == MY_COURSES_SUB_COMMAND) {
      studentDeleteCourseCommand(input);
    } else {
      throw runtime_error("command not handle in this function");
    }
  } else {
    throw runtime_error("command not handle in this function");
  }
}
void Program::checkProfessorSpecificCommand() {

  throw runtime_error("command not handle in this function");
}
void Program::checkAdminSpecificCommand(const vector<string> &input) {
  if (input[0] == POST_COMMAND) {
    if (input[1] == COURSE_OFFER_SUB_COMMAND) {
      AdminPostOffercourseCommand(input);
    } else {
      throw runtime_error("command not handle in this function");
    }
  } else {
    throw runtime_error("command not handle in this function");
  }
}

vector<string> Program::splitString(const string &input, const char delimiter) {
  vector<string> result;
  istringstream iss(input);
  string token;

  while (getline(iss, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}

string Program::connectString(const vector<string> &input,
                              const char delimiter) {
  string result;
  int i = 0;
  for (const string &s : input) {
    if (i != 0) {
      result += delimiter;
    }
    result += s;
    i++;
  }

  return result;
}

bool Program::isExists(const string member, const vector<string> vector) {
  for (const string &str : vector) {
    if (str == member) {
      return true;
    }
  }
  return false;
}

bool Program::isNormalNumber(const string &str) {
  for (char c : str) {
    if (c < '0' || c > '9') {
      return false;
    }
  }
  return true;
}

bool Program::isUserIdValid(const string &id) {
  if (id == ADMIN_ID) {
    return true;
  } else if (studentsCSV.isExists("sid", id)) {
    return true;
  } else if (professorsCSV.isExists("pid", id)) {
    return true;
  }
  return false;
}

bool Program::isStudentIdValid(const string &id) {
  if (studentsCSV.isExists("sid", id)) {
    return true;
  }
  return false;
}
bool Program::isProfessorIdValid(const string &id) {
  if (professorsCSV.isExists("pid", id)) {
    return true;
  }
  return false;
}
bool Program::isCourseIdValid(const string &id) {
  if (coursesCSV.isExists("cid", id)) {
    return true;
  }
  return false;
}
bool Program::isOfferCourseIdValid(const string &id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  if (offer_courses.isExists("offer_course_id", id)) {
    return true;
  }
  return false;
}

bool Program::isCourseOfferProfessorTimeOverlap(const string &time,
                                                const string &professor_id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  vector<vector<string>> offer_courses_body = offer_courses.bodyMatris();
  for (vector<string> &line : offer_courses_body) {
    if (line[2] == professor_id) {
      if (isOverlap(parseTimeRange(time), parseTimeRange(line[4])) == true) {
        return true;
      }
    }
  }
  return false;
}

bool Program::isCourseOfferProfessorMajorOk(const string &professor_id,
                                            const string &course_id) {
  string professor_major_id =
      professorsCSV.findField("pid", professor_id, "major_id");
  vector<string> course_major_ids =
      splitString(coursesCSV.findField("cid", course_id, "majors_id"), ';');
  for (const string &course_major_id : course_major_ids) {
    if (course_major_id == professor_major_id) {
      return true;
    }
  }
  return false;
}

bool Program::isCourseOfferStudedntTimeOverlap(const string &offer_course_id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  vector<vector<string>> offer_courses_body = offer_courses.bodyMatris();
  for (vector<string> &line : offer_courses_body) {
    for (string &sid : splitString(line[7], ';')) {
      if (sid == user_ptr->getId()) {
        if (isOverlap(parseTimeRange(offer_courses.findField(
                          "offer_course_id", offer_course_id, "time")),
                      parseTimeRange(line[4])) == true) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Program::isCourseOfferStudentMajorOk(const string &offer_course_id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  string student_major_id =
      studentsCSV.findField("sid", user_ptr->getId(), "major_id");
  vector<string> course_major_ids = splitString(
      coursesCSV.findField("cid",
                           offer_courses.findField(
                               "offer_course_id", offer_course_id, "course_id"),
                           "majors_id"),
      ';');
  for (const string &course_major_id : course_major_ids) {
    if (course_major_id == student_major_id) {
      return true;
    }
  }
  return false;
}

bool Program::isCourseOfferStudentCreditOk(const string &offer_course_id) {
  CSVHandler offer_courses(INTERNAL_DATA_DIRECTORY_PATH +
                           INTERNAL_DATA_OFFER_COURSES_NAME);
  string student_semester =
      studentsCSV.findField("sid", user_ptr->getId(), "semester");

  string prerequisite = coursesCSV.findField(
      "cid",
      offer_courses.findField("offer_course_id", offer_course_id, "course_id"),
      "prerequisite");

  return (stoi(student_semester) >= stoi(prerequisite));
}

void Program::postPostCommand(const vector<string> &input) {
  string title = NONE_STRING;
  string message = NONE_STRING;
  string attach = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "title") {
      if (i + 1 < input.size()) {
        title = input[i + 1];
      }
    } else if (input[i] == "message") {
      if (i + 1 < input.size()) {
        message = input[i + 1];
      }
    } else if (input[i] == "image") {
      if (i + 1 < input.size()) {
        attach = input[i + 1];
      }
    }
  }
  if (title == NONE_STRING || message == NONE_STRING) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  post(title, message, attach);
}
void Program::postcoursePostCommand(const vector<string> &input) {
  string id = NONE_STRING;
  string title = NONE_STRING;
  string message = NONE_STRING;
  string attach = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    } else if (input[i] == "title") {
      if (i + 1 < input.size()) {
        title = input[i + 1];
      }
    } else if (input[i] == "message") {
      if (i + 1 < input.size()) {
        message = input[i + 1];
      }
    } else if (input[i] == "image") {
      if (i + 1 < input.size()) {
        attach = input[i + 1];
      }
    }
  }
  if (title == NONE_STRING || message == NONE_STRING || id == NONE_STRING ||
      id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  channelPost(id, title, message, attach);
}

void Program::postConnectCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  connect(id);
}

void Program::postProfilePhotoCommand(const vector<string> &input) {
  string photo = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "photo") {
      if (i + 1 < input.size()) {
        photo = input[i + 1];
      }
    }
  }
  if (photo == NONE_STRING) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  addProfilePhoto(photo);
}

void Program::deletePostCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  deletePost(id);
}

void Program::getPersonalPageCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  seePage(id);
}

void Program::getCourseChannelCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  seeChannelPage(id);
}

void Program::getCoursePostCommand(const vector<string> &input) {
  string id = NONE_STRING;
  string post_id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    } else if (input[i] == "post_id") {
      if (i + 1 < input.size()) {
        post_id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || post_id == NONE_STRING || (!isNormalNumber(id)) ||
      (!isNormalNumber(post_id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  getChannelPost(id, post_id);
}

void Program::getCoursesCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING) {
    seeAllOfferCourses();
    return;
  } else if ((!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  seeOfferCourses(id);
}

void Program::getPostCommand(const vector<string> &input) {
  string id = NONE_STRING;
  string post_id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    } else if (input[i] == "post_id") {
      if (i + 1 < input.size()) {
        post_id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || post_id == NONE_STRING || (!isNormalNumber(id)) ||
      (!isNormalNumber(post_id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  getPost(id, post_id);
}

void Program::studentPutMycourseCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  } else if (isCourseOfferStudedntTimeOverlap(id) ||
             (!isCourseOfferStudentMajorOk(id)) ||
             (!isCourseOfferStudentCreditOk(id))) {
    cout << PERMISSIN_DENIED_OUTPUT << endl;
    return;
  }

  studentAddCourse(id);
}

void Program::studentDeleteCourseCommand(const vector<string> &input) {
  string id = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "id") {
      if (i + 1 < input.size()) {
        id = input[i + 1];
      }
    }
  }
  if (id == NONE_STRING || (!isNormalNumber(id))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  }
  studentDeleteCourse(id);
}

void Program::AdminPostOffercourseCommand(const vector<string> &input) {
  string course_id = NONE_STRING;
  string professor_id = NONE_STRING;
  string capacity = NONE_STRING;
  string time = NONE_STRING;
  string exam_date = NONE_STRING;
  string class_number = NONE_STRING;
  for (size_t i = 3; i < input.size(); i++) {
    if (input[i] == "course_id") {
      if (i + 1 < input.size()) {
        course_id = input[i + 1];
      }
    } else if (input[i] == "professor_id") {
      if (i + 1 < input.size()) {
        professor_id = input[i + 1];
      }
    } else if (input[i] == "capacity") {
      if (i + 1 < input.size()) {
        capacity = input[i + 1];
      }
    } else if (input[i] == "time") {
      if (i + 1 < input.size()) {
        time = input[i + 1];
      }
    } else if (input[i] == "exam_date") {
      if (i + 1 < input.size()) {
        exam_date = input[i + 1];
      }
    } else if (input[i] == "class_number") {
      if (i + 1 < input.size()) {
        class_number = input[i + 1];
      }
    }
  }
  if (course_id == NONE_STRING || professor_id == NONE_STRING ||
      capacity == NONE_STRING || time == NONE_STRING ||
      exam_date == NONE_STRING || class_number == NONE_STRING ||
      (!isNormalNumber(course_id)) || (!isNormalNumber(professor_id)) ||
      (!isNormalNumber(capacity)) || (!isNormalNumber(class_number))) {
    cout << BAD_REQUEST_OUTPUT << endl;
    return;
  } else if (isStudentIdValid(professor_id) || (professor_id == ADMIN_ID) ||
             isCourseOfferProfessorTimeOverlap(time, professor_id) ||
             (!isCourseOfferProfessorMajorOk(professor_id, course_id))) {
    cout << PERMISSIN_DENIED_OUTPUT << endl;
    return;
  } else if (!isCourseIdValid(course_id) || !isProfessorIdValid(professor_id)) {
    cout << NOT_FOUND_OUTPUT << endl;
    return;
  }
  courseOffer(course_id, professor_id, capacity, time, exam_date, class_number);
}