#include <iostream> // library for reading & writing from the console/keyboard
#include <fstream> //library for reading and writing from other files
#include <vector> //library for vector functions
#include <iomanip> //library for i/o manipulators
#include <algorithm>

int main() {
    std::string course1= "12:30PM";
    std::string course2= "02:00PM";
  int course1_hour = stoi(course1.substr(0, course1.find(":"))); 
  int course1_min = stoi(course1.substr(3, course1.find(":"))); 
  int course2_hour = stoi(course2.substr(0, course2.find(":"))); 
  int course2_min = stoi(course2.substr(3, course2.find(":")));
  //TESTING HERE
  //TESTING ABOVE
  if (course1[5]=='P' && (course1_hour!=12 || (course1_hour==12 && course1_min>0) ) ) {
    course1_hour=course1_hour+12;
  }
  if (course2[5]=='P' && (course2_hour!=12 || (course2_hour==12 && course2_min>0) ) ) {
    course2_hour=course2_hour+12;
  }
  if (course1_hour<course2_hour) {
    std::cout << true <<std::endl;
  }
  else if (course1_hour>course2_hour) {
    std::cout << false;
  }
  else {
    if (course1_min<course2_min) {
      std::cout << true;
    }
    else {
      std::cout << false;
    }
  }
}