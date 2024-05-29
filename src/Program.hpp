#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "CSVHandler.hpp"
#include "Constant.hpp"
#include "User.hpp"
#include <cstddef>
#include <string>

using namespace std;

class Program {
public:
  Program(const string &_majorsFile_path, const string &_studentsFile_path,
          const string &_coursesFile_path, const string &_professorsFile_path);
  void run();
  void setup();
  void test();

private:
  bool createFileIfNotExists(const string &filename);
  void setupConfigFile(CSVHandler &File);
  void setupOfferCoursesFile(CSVHandler &File);
  void setupUser(const string &id, CSVHandler &config);
  void setupPostsFile(CSVHandler &File);
  void setupNotificationsFile(CSVHandler &File);
  vector<string> getInputVectorFromTerminal();
  void parseInput(const vector<string> &input);
  void checkLoginCommand(const vector<string> &input);
  bool isCommandInList(const string &command,
                       const vector<string> &command_list);
  void login(const string id, const string password);
  void logout();
  void post(const string title, const string message);
  void deletePost(const string id);
  void printUserHeader(const string id);
  void seePage(const string id);
  void connect(const string id);
  void sendNotification(const string sender_id, const string sender_name,
                        const string send_to_id, const string massage);
  void getNotification();
  void courseOffer(string course_id, string professor_id, string capacity,
                   string time, string examp_date,
                   string class_number); //! checkers
  void studentAddCourse(string id);
  void studentDeleteCourse(string id);
  vector<size_t> studentCousesIndex();
  void studentAllCourses();
  void checkUserCommand(const vector<string> &input);
  void checkStudentCommand(const vector<string> &input);
  void checkProfessorCommand(const vector<string> &input);
  void checkAdminCommand(const vector<string> &input);
  void checkStudentSpecificCommand(const vector<string> &input);
  void checkProfessorSpecificCommand(const vector<string> &input);
  void checkAdminSpecificCommand(const vector<string> &input);
  vector<string> splitString(const string &input, const char delimiter);
  string connectString(const vector<string> &input, const char delimiter);
  bool isNormalNumber(const string &str);
  bool isUserIdValid(const string &id);
  bool isStudentIdValid(const string &id);
  bool isProfessorIdValid(const string &id);
  bool isCourseIdValid(const string &id);
  bool isCourseOfferTimeOverlap(const string &professor_id, const string &time);
  bool isTimeOverlap(const string &time1, const string &time2);
  void splitTime(const string &timeStr, string &weekday, int &startHour,
                 int &endHour);
  bool isCourseOfferProfessorCanTeachCourse(const string &professor_id,
                                            const string &course_id);

  string majorsFile_path;
  string studentsFile_path;
  string coursesFile_path;
  string professorsFile_path;
  CSVHandler majorsCSV;
  CSVHandler studentsCSV;
  CSVHandler coursesCSV;
  CSVHandler professorsCSV;
  Permission permission;
  User *user_ptr = NULL;
  bool open;
};

#endif // PROGRAM_HPP