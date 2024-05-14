// File:    course.cpp
// Purpose: Implementation file for the Course class.

#include <iostream> // library for reading & writing from the console/keyboard
#include <vector> //library for vector functions
#include <algorithm> //library for algorithm functions
#include "course.h" //allows this file to have access to the header file

//Constructed from course ID, course department, course code, course title, days the course is scheduled, time the class starts each day, time the class ends each day, and the room it takes place in
Course::Course(int a_course_id, std::string a_dept, std::string a_course_code, std::string a_course_title, std::string a_days, std::string a_start_time, std::string a_end_time, std::string a_room) {
  course_id=a_course_id;
  dept=a_dept;
  course_code=a_course_code;
  course_title=a_course_title;
  days=a_days;
  start_time=a_start_time;
  end_time=a_end_time;
  room=a_room;
}

 // ACCESSORS
int Course::get_course_id() const {
  return course_id;
}

std::string Course::get_dept() const {
  return dept;
}

std::string Course::get_course_code() const {
  return course_code;
}

std::string Course::get_course_title() const {
  return course_title;
}

std::string Course::get_days() const {
  return days;
}

std::string Course::get_start_time() const {
  return start_time;
}

std::string Course::get_end_time() const {
  return end_time;
}

std::string Course::get_room() const {
  return room;
}

//MODIFIERS
void Course::set_course_id(int new_course_id) {
  course_id=new_course_id;
}

void Course::set_dept(std::string new_dept) {
  dept=new_dept;
}

void Course::set_course_code(std::string new_course_code) {
  course_code=new_course_code;
}

void Course::set_course_title(std::string new_course_title) {
  course_title=new_course_title;
}

void Course::set_days(std::string new_days) {
  days=new_days;
}

void Course::set_start_time(std::string new_start_time) {
  start_time=new_start_time;
}

void Course::set_end_time(std::string new_end_time) {
  end_time=new_end_time;
}

void Course::set_room(std::string new_room) {
  room=new_room;
}

//returns true if the first course's room comes before the second course's room in alphanumeric order
bool sort_by_room(const Course &course1, const Course &course2) {
  std::vector<std::string> rooms= {course1.get_room(), course2.get_room()};
  sort(rooms.begin(), rooms.end());
  return std::find(rooms.begin(), rooms.end(), course1.get_room() )<std::find(rooms.begin(), rooms.end(), course2.get_room() );
}

//returns true if the first course's code comes before the second course's code in alphanumeric order
bool sort_by_course_code(const Course &course1, const Course &course2) {
  std::vector<std::string> codes= {course1.get_course_code(), course2.get_course_code()};
  sort(codes.begin(), codes.end());
  return std::find(codes.begin(), codes.end(), course1.get_course_code() )<std::find(codes.begin(), codes.end(), course2.get_course_code() );
}

//returns true if the first course's dept comes before the second course's dept in alphabetical order
bool sort_by_dept(const Course &course1, const Course &course2) {
  std::vector<std::string> depts= {course1.get_dept(), course2.get_dept()};
  sort(depts.begin(), depts.end());
  return std::find(depts.begin(), depts.end(), course1.get_dept() )<std::find(depts.begin(), depts.end(), course2.get_dept() );
}

//returns true if the first course's day of the week comes before the second course's day of the week
bool sort_by_day(const Course &course1, const Course &course2) {
  std::vector<std::string> weekdays= {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
  return std::find(weekdays.begin(), weekdays.end(), course1.get_days() )<std::find(weekdays.begin(), weekdays.end(), course2.get_days() );
}

//returns true if the starting time of the first course comes BEFORE the starting time of the second course
bool sort_by_earliest_start_time(const Course &course1, const Course &course2) {
  int course1_hour = stoi(course1.get_start_time().substr(0, course1.get_start_time().find(":"))); 
  int course1_min = stoi(course1.get_start_time().substr(3, course1.get_start_time().find(":"))); 
  int course2_hour = stoi(course2.get_start_time().substr(0, course2.get_start_time().find(":"))); 
  int course2_min = stoi(course2.get_start_time().substr(3, course2.get_start_time().find(":")));
  if (course1.get_start_time()[5]=='P' && course1_hour!=12 ) {
    course1_hour=course1_hour+12;
  }
  if (course2.get_start_time()[5]=='P' && course2_hour!=12 ) {
    course2_hour=course2_hour+12;
  }
  if (course1_hour<course2_hour) {
    return true;
  }
  else if (course1_hour>course2_hour) {
    return false;
  }
  else {
    if (course1_min<course2_min) {
      return true;
    }
    else {
      return false;
    }
  }
}

//returns true if the starting time of the first course comes AFTER the starting time of the second course
bool sort_by_latest_start_time(const Course &course1, const Course &course2) {
  int course1_hour = stoi(course1.get_start_time().substr(0, course1.get_start_time().find(":"))); 
  int course1_min = stoi(course1.get_start_time().substr(3, course1.get_start_time().find(":"))); 
  int course2_hour = stoi(course2.get_start_time().substr(0, course2.get_start_time().find(":"))); 
  int course2_min = stoi(course2.get_start_time().substr(3, course2.get_start_time().find(":")));
  if (course1.get_start_time()[5]=='P' && course1_hour!=12) {
    course1_hour=course1_hour+12;
  }
  if (course2.get_start_time()[5]=='P' && course2_hour!=12 ) {
    course2_hour=course2_hour+12;
  }
  if (course1_hour>course2_hour) {
    return true;
  }
  else if (course1_hour<course2_hour) {
    return false;
  }
  else {
    if (course1_min>course2_min) {
      return true;
    }
    else {
      return false;
    }
  }
}