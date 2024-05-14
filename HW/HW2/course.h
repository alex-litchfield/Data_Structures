// File:     course.h
// Purpose:  Header file with declaration of the Course class, including member functions and private member variables.

#include <iostream> // library for reading & writing from the console/keyboard

class Course {
public:
  //Constructor
  Course(int a_course_id, std::string a_dept, std::string a_course_code, std::string a_course_title, std::string a_days, std::string a_start_time, std::string a_end_time, std::string a_room);

  // ACCESSORS
  int get_course_id() const;
  std::string get_dept() const;
  std::string get_course_code() const;
  std::string get_course_title() const;
  std::string get_days() const;
  std::string get_start_time() const;
  std::string get_end_time() const;
  std::string get_room() const;


  // MODIFIERS
  void set_course_id(int new_course_id);
  void set_dept(std::string new_dept);
  void set_course_code(std::string new_course_code);
  void set_course_title(std::string new_course_title);
  void set_days(std::string new_days);
  void set_start_time(std::string new_start_time);
  void set_end_time(std::string new_end_time);
  void set_room(std::string new_room);

  
  int course_id;
  std::string dept, course_code, course_title, days, start_time, end_time, room;
};

//returns true if the first course's room comes before the second course's room in alphanumeric order
bool sort_by_room(const Course &course1, const Course &course2);

//returns true if the first course's code comes before the second course's code in alphanumeric order
bool sort_by_course_code(const Course &course1, const Course &course2);

//returns true if the first course's dept comes before the second course's dept in alphabetical order
bool sort_by_dept(const Course &course1, const Course &course2);

//returns true if the first course's day of the week comes before the second course's day of the week
bool sort_by_day(const Course &course1, const Course &course2);

//returns true if the starting time of the first course comes BEFORE the starting time of the second course
bool sort_by_earliest_start_time(const Course &course1, const Course &course2);

//returns true if the starting time of the first course comes AFTER the starting time of the second course
bool sort_by_latest_start_time(const Course &course1, const Course &course2);