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
  void setupCoursePostsFile(CSVHandler &File);
  void setupNotificationsFile(CSVHandler &File);
  vector<string> getInputVectorFromTerminal();
  void parseInput(const vector<string> &input);
  void checkLoginCommand(const vector<string> &input);
  bool isCommandInList(const string &command,
                       const vector<string> &command_list);
  void login(const string id, const string password);
  void logout();
  void post(const string title, const string message, const string attach);
  void postTaForm(const string offer_course_id, const string message);
  void channelPost(const string offer_course_id, const string title,
                   const string message, const string attach);
  void deletePost(const string id);
  void printUserHeader(const string id);
  void seePage(const string id);
  void seeChannelPage(const string id);
  void getPost(const string id, const string post_id);
  void getChannelPost(const string id, const string post_id);
  void seeAllOfferCourses();
  void seeOfferCourses(const string &id);
  void connect(const string id);
  void addProfilePhoto(const string photo);
  void sendNotification(const string sender_id, const string sender_name,
                        const string send_to_id, const string massage);
  void getNotification();
  void courseOffer(string course_id, string professor_id, string capacity,
                   string time, string exam_date, string class_number);
  void studentAddCourse(string id);
  void studentDeleteCourse(string id);
  vector<size_t> studentCoursesIndex();
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
  bool isExists(const string member, const vector<string> vector);
  bool isNormalNumber(const string &str);
  bool isUserIdValid(const string &id);
  bool isStudentIdValid(const string &id);
  bool isProfessorIdValid(const string &id);
  bool isCourseIdValid(const string &id);
  bool isOfferCourseIdValid(const string &id);
  bool isCourseOfferProfessorTimeOverlap(const string &time,
                                         const string &professor_id);
  bool isCourseOfferProfessorMajorOk(const string &professor_id,
                                     const string &course_id);
  bool isCourseOfferStudentTimeOverlap(const string &offer_course_id);
  bool isCourseOfferStudentMajorOk(const string &offer_course_id);
  bool isCourseOfferStudentCreditOk(const string &offer_course_id);
  void postPostCommand(const vector<string> &input);
  void postCoursePostCommand(const vector<string> &input);
  void postConnectCommand(const vector<string> &input);
  void postProfilePhotoCommand(const vector<string> &input);
  void deletePostCommand(const vector<string> &input);
  void getPersonalPageCommand(const vector<string> &input);
  void getCourseChannelCommand(const vector<string> &input);
  void getCoursePostCommand(const vector<string> &input);
  void getCoursesCommand(const vector<string> &input);
  void getPostCommand(const vector<string> &input);
  void studentPutMyCourseCommand(const vector<string> &input);
  void studentDeleteCourseCommand(const vector<string> &input);
  void professorPostTaFormCommand(const vector<string> &input);
  void AdminPostOfferCourseCommand(const vector<string> &input);

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