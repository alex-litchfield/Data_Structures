// Program:  hw2_main.cpp
// Purpose:  Demonstrate use of the Course class.

#include <iostream>  //library for reading & writing from the console/keyboard
#include <fstream>   //library for reading and writing from other files
#include <vector>    //library for vector functions
#include <algorithm> //library for algorithim functions like sort()
#include <cmath>     //library needed for abs() function
#include "course.h"  //includes course header file

int main(int argc, char *argv[]) {
    //Error chec if there are not enough args present
    if (argc<4) {
        std::cerr << "Can't open, needs additional arguments" <<std::endl;
        exit(1);
    }
    std::ifstream infile(argv[1]);
    //Error check for if input file is valid.
    if (!infile.good()) {
        std::cerr << "Can't open " << argv[1] << " to read" << std::endl;
        exit(1);
    }
    int course_id;
    std::string dept, course_code, course_title, days, start_time, end_time, room;
    std::vector<Course> courses;
    //creates an object for every line in the input file, but if a line has multiple days,
    //it creates an different object for that class per day it occurs
    while (infile >> course_id >> dept >> course_code >> course_title >> days >> start_time >> end_time >> room) {
        for (int i=0; i<int(days.length())+1; i++) {
            if (days[0]=='M') {
                Course course1(course_id, dept, course_code, course_title, "Monday", start_time, end_time, room);
                courses.push_back(course1);
            }
            else if (days[0]=='T') {
                Course course1(course_id, dept, course_code, course_title, "Tuesday", start_time, end_time, room);
                courses.push_back(course1);
            }
            else if (days[0]=='W') {
                Course course1(course_id, dept, course_code, course_title, "Wednesday", start_time, end_time, room);
                courses.push_back(course1);
            }
            else if (days[0]=='R') {
                Course course1(course_id, dept, course_code, course_title, "Thursday", start_time, end_time, room);
                courses.push_back(course1);
            }
            else if (days[0]=='F') {
                Course course1(course_id, dept, course_code, course_title, "Friday", start_time, end_time, room);
                courses.push_back(course1);
            }
            days.erase(0, 1);
        }
    }
    infile.close();
    std::ofstream outfile(argv[2]);
    //Error check for if output file is valid.
    if (!outfile.good()) {
        std::cerr << "Can't open " << argv[2] << " to write" << std::endl;
        exit(1);
    }
    //room based output
    if (courses.size()==0) { // Error check for if no courses are present
        outfile << "No data available." << std::endl;
        exit(1);
    }
    int begin_limit=0;
    int end_limit=courses.size();
    if (argv[3]==std::string("room") || argv[3]==std::string("custom")) {
        bool room_validity=false;
        int i_counter=0;
        int start_counter=0;
        sort(courses.begin(), courses.end(), sort_by_room);
        for (int i=0; i<int(courses.size()); i++) {
            if (argc==5 && courses[i].get_room()==argv[4]) { //if 4th argument present
                room_validity=true;
                if (i==0 || (i>0 && courses[i].get_room()!=courses[i-1].get_room() ) ) {
                    begin_limit=i;
                }
                end_limit=i+1;
            }
            if (i<(int(courses.size())-1) && courses[i].get_room()==courses[i+1].get_room()) { //if rooms are identical and no 4th arg
                i_counter++;
                if (i==0 || courses[i-1].get_room()!=courses[i].get_room()) {
                    start_counter=i;
                }
            }
            else { //if rooms ARENT identical
                i_counter++;
                sort(courses.begin()+start_counter, courses.begin()+start_counter+i_counter, sort_by_day);
                int j_counter=0;
                int start_counter2=0;
                for (int j=start_counter; j<(start_counter+i_counter); j++) { //searching through courses with identical rooms and identical days
                    if (j<(int(courses.size())-1) && courses[j].get_days()==courses[j+1].get_days()) { //if days are identical
                        j_counter++;
                        if (j==0 || courses[j-1].get_days()!=courses[j].get_days()) {
                            start_counter2=j;
                        }
                    }
                    else { // if days ARENT identical
                        j_counter++;
                        sort(courses.begin()+start_counter2, courses.begin()+start_counter2+j_counter, sort_by_earliest_start_time);
                        int k_counter=0;
                        int start_counter3=0;
                        for (int k=start_counter2; k<(start_counter2+j_counter); k++) { //searching through courses with identical rooms, days, and start times
                            if (k<(int(courses.size())-1) && courses[k].get_start_time()==courses[k+1].get_start_time()) { //if start times are identical
                                k_counter++;
                                if (k==0 || courses[k-1].get_start_time()!=courses[k].get_start_time()) {
                                    start_counter3=k;
                                }  
                            }
                            else { //if start times ARENT identical
                                k_counter++;
                                sort(courses.begin()+start_counter3, courses.begin()+start_counter3+k_counter, sort_by_course_code);
                                int l_counter=0;
                                int start_counter4=0;
                                for (int l=start_counter3; l<(start_counter3+k_counter); l++) { //searching through courses with identical rooms, days, start times, and course codes
                                    if (l<(int(courses.size())-1) && courses[l].get_course_code()==courses[l+1].get_course_code()) { //if course codes are identical
                                        l_counter++;
                                        if (l==0 || courses[l-1].get_course_code()!=courses[l].get_course_code()) {
                                            start_counter4=l;
                                        }
                                    }
                                    else { //if course codes ARENT identical
                                        l_counter++;
                                        sort(courses.begin()+start_counter4, courses.begin()+start_counter4+l_counter, sort_by_dept);
                                        l_counter=0;
                                    }  
                                }
                                k_counter=0;
                            }
                        }
                        j_counter=0;
                    }
                }
                i_counter=0;
            }
        }
        if (argc==5 && room_validity==false) { //Error check for if room is valid.
            outfile << "No data available." << std::endl;
            exit(1);
        }
    }
    //dept based output
    else if (argv[3]==std::string("dept") ) {
        if (argv[3]==std::string("dept") && argc!=5) { //Error check for if 4th arg is present with "dept"
            std::cerr << "Needs additional argument " << argv[4] << std::endl;
            exit(1);
        }
        bool dept_validity=false;
        int i_counter=0;
        int start_counter=0;
        sort(courses.begin(), courses.end(), sort_by_dept);
        for (int i=0; i<int(courses.size()); i++) {
            if (argc==5 && courses[i].get_dept()==argv[4]) { //if 4th argument present
                dept_validity=true;
                if (i==0 || (i>0 && courses[i].get_dept()!=courses[i-1].get_dept() ) ) {
                    begin_limit=i;
                }
                end_limit=i+1;
            }
            if (i<(int(courses.size())-1) && courses[i].get_dept()==courses[i+1].get_dept()) { //if depts are identical and no 4th arg
                i_counter++;
                if (i==0 || courses[i-1].get_dept()!=courses[i].get_dept()) {
                    start_counter=i;
                }
            }
            else { //if depts ARENT identical
                i_counter++;
                sort(courses.begin()+start_counter, courses.begin()+start_counter+i_counter, sort_by_course_code);
                int j_counter=0;
                int start_counter2=0;
                for (int j=start_counter; j<(start_counter+i_counter); j++) { //searching through courses with identical depts and identical course codes
                    if (j<(int(courses.size())-1) && courses[j].get_course_code()==courses[j+1].get_course_code()) { //if course codes are identical
                        j_counter++;
                        if (j==0 || courses[j-1].get_course_code()!=courses[j].get_course_code()) {
                            start_counter2=j;
                        }
                    }
                    else { // if course codes ARENT identical
                        j_counter++;
                        sort(courses.begin()+start_counter2, courses.begin()+start_counter2+j_counter, sort_by_day);
                        int k_counter=0;
                        int start_counter3=0;
                        for (int k=start_counter2; k<(start_counter2+j_counter); k++) { //searching through courses with identical depts, course_codes, and days
                            if (k<(int(courses.size())-1) && courses[k].get_days()==courses[k+1].get_days()) { //if days are identical
                                k_counter++;
                                if (k==0 || courses[k-1].get_days()!=courses[k].get_days()) {
                                    start_counter3=k;
                                }  
                            }
                            else { //if days ARENT identical
                                k_counter++;
                                sort(courses.begin()+start_counter3, courses.begin()+start_counter3+k_counter, sort_by_latest_start_time);
                                int l_counter=0;
                                int start_counter4=0;
                                for (int l=start_counter3; l<(start_counter3+k_counter); l++) { //searching through courses with identical depts, course_codes, days, and latest start time
                                    if (l<(int(courses.size())-1) && courses[l].get_start_time()==courses[l+1].get_start_time()) { //if start times are identical
                                        l_counter++;
                                        if (l==0 || courses[l-1].get_start_time()!=courses[l].get_start_time()) {
                                            start_counter4=l;
                                        }
                                    }
                                    else { //if start times ARENT identical
                                        l_counter++;
                                        l_counter=0;
                                    }  
                                }
                                k_counter=0;
                            }
                        }
                        j_counter=0;
                    }
                }
                i_counter=0;
            }
        }
        if (argc==5 && dept_validity==false) { //Error check for if the 4th arg is valid when 3rd arg is "dept" .
            outfile << "No data available." << std::endl;
            exit(1);
        }
    }
    //printing operations begin
    int counter=0;
    int start_counter=0;
    if (argc==5) { //make both these ints
        int counter=end_limit;
        int start_counter=begin_limit;
    }
    int day_length=0;
    int title_length=0;
    for (int i=begin_limit; i<end_limit; i++) {
        if (argv[3]==std::string("room") || argv[3]==std::string("custom") ) { //room based AND custom printing
            if (i<(int(courses.size())-1) && courses[i].get_room()==courses[i+1].get_room() ) { //if rooms are identical and operation is room
                counter++;
                if (i==0 || courses[i-1].get_room()!=courses[i].get_room()) {
                    start_counter=i;
                }
                if (int(courses[i].get_course_title().length())>title_length) { //finds largest course title name in a set
                    title_length=courses[i].get_course_title().length();
                }
                if (int(courses[i].get_days().length())>day_length) { //finds largest day name in a set
                    day_length=courses[i].get_days().length();
                }
            }
            else { //if rooms are not identical
                if ( (i<(int(courses.size())-1) && courses[i].get_room()!=courses[i-1].get_room() ) || (i>0 && courses[i].get_room()==courses[i-1].get_room() ) ) { //if there is only one course within a room
                    if (i==0 || courses[i-1].get_room()!=courses[i].get_room()) {
                        start_counter=i;
                    }
                    if (int(courses[i].get_course_title().length())>title_length) { //finds largest course title name in a set
                        title_length=courses[i].get_course_title().length();
                    }
                    if (int(courses[i].get_days().length())>day_length) { //finds largest day name in a set
                        day_length=courses[i].get_days().length();
                    }
                }
                counter++;
                outfile << "Room " << courses[i].get_room() <<std::endl;
                if (argv[3]==std::string("room")) {
                    outfile << "Dept  Coursenum  Class Title";
                    if (title_length-11<0) {
                        title_length=11;
                    }
                    outfile << std::string(abs(title_length-11), ' ');
                    outfile << "  Day" << std::string(abs(day_length-3), ' ') << "  Start Time  End Time"<<std::endl;
                    outfile << "----  ---------  -----------" << std::string(abs(title_length-11), '-') << "  ---";
                    outfile << std::string(abs(day_length-3), '-') << "  ----------  --------"<<std::endl;
                }
                int monday_usage =0;
                int tuesday_usage =0;
                int wednesday_usage =0;
                int thursday_usage =0;
                int friday_usage =0;
                //for each course which shared a room, print its info OR find what day it occurs
                for (int j=start_counter; j<(start_counter+counter); j++) { 
                    if (argv[3]==std::string("custom") && courses[j].get_days()==std::string("Monday")) {
                        monday_usage++;
                    }
                    else if (argv[3]==std::string("custom") && courses[j].get_days()==std::string("Tuesday")) {
                        tuesday_usage++;
                    }
                    else if (argv[3]==std::string("custom") && courses[j].get_days()==std::string("Wednesday")) {
                        wednesday_usage++;
                    }
                    else if (argv[3]==std::string("custom") && courses[j].get_days()==std::string("Thursday")) {
                        thursday_usage++;
                    }
                    else if (argv[3]==std::string("custom") && courses[j].get_days()==std::string("Friday")) {
                        friday_usage++;
                    }
                    else if (argv[3]==std::string("room") ) {
                        outfile << courses[j].get_dept() << std::string(6-courses[j].get_dept().length(), ' ');
                        outfile << courses[j].get_course_code() << "    " << courses[j].get_course_title();
                        outfile << std::string(2+title_length-courses[j].get_course_title().length(), ' ');
                        outfile << courses[j].get_days() << std::string(2+day_length-courses[j].get_days().length(), ' ');
                        outfile << courses[j].get_start_time() << "     " << courses[j].get_end_time() << ' ' << std::endl;
                    }
                }
                //outputs info for our "custom" operation
                if (argv[3]==std::string("custom") ) {
                    std::vector<int> weekdays = {monday_usage, tuesday_usage, wednesday_usage, thursday_usage, friday_usage};
                    sort(weekdays.begin(), weekdays.end());
                    outfile << "This room is most used on";
                    bool monday_printed=false;
                    bool tuesday_printed=false;
                    bool wednesday_printed=false;
                    bool thursday_printed=false;
                    bool friday_printed=false;
                    for (int k=0; k<int(weekdays.size()); k++) {
                        if (weekdays[4-k]==weekdays[4] && monday_usage==weekdays[4-k] && monday_printed==false) {
                            if (tuesday_printed==true || wednesday_printed==true || thursday_printed==true || friday_printed==true) {
                                outfile << " and";
                            }
                            outfile << " Mondays";
                            monday_printed=true;
                        }
                        if (weekdays[4-k]==weekdays[4] && tuesday_usage==weekdays[4-k] && tuesday_printed==false) {
                            if (monday_printed==true || wednesday_printed==true || thursday_printed==true || friday_printed==true) {
                                outfile << " and";
                            }
                            outfile << " Tuesdays";
                            tuesday_printed=true;
                        }
                        if (weekdays[4-k]==weekdays[4] && wednesday_usage==weekdays[4-k] && wednesday_printed==false) {
                            if (monday_printed==true || tuesday_printed==true || thursday_printed==true || friday_printed==true) {
                                outfile << " and";
                            }
                            outfile << " Wednesdays";
                            wednesday_printed=true;
                        }
                        if (weekdays[4-k]==weekdays[4] && thursday_usage==weekdays[4-k] && thursday_printed==false) {
                            if (monday_printed==true || tuesday_printed==true || wednesday_printed==true || friday_printed==true) {
                                outfile << " and";
                            }
                            outfile << " Thursdays";
                            thursday_printed=true;
                        }
                        if (weekdays[4-k]==weekdays[4] && friday_usage==weekdays[4-k] && friday_printed==false) {
                            if (monday_printed==true || tuesday_printed==true || wednesday_printed==true || thursday_printed==true) {
                                outfile << " and";
                            }
                            outfile << " Fridays";
                            friday_printed=true;
                        }
                    }
                    outfile <<std::endl <<std::endl;
                }
                else if (argv[3]==std::string("room")) {
                    outfile << counter << " entries" << std::endl << std::endl;
                }
                counter=0;
                day_length=0;
                title_length=0;
            }
        }
        else if (argv[3]==std::string("dept") ) { //dept based printing
            if (i<(int(courses.size())-1) && courses[i].get_dept()==courses[i+1].get_dept() ) { //if depts are identical and operation is dept
                counter++;
                if (i==0 || courses[i-1].get_dept()!=courses[i].get_dept()) {
                    start_counter=i;
                }
                if (int(courses[i].get_course_title().length())>title_length) { //finds largest course title name in a set
                    title_length=courses[i].get_course_title().length();
                }
                if (int(courses[i].get_days().length())>day_length) { //finds largest day name in a set
                    day_length=courses[i].get_days().length();
                }
            }
            else { //if depts are not identical
                if ( (i<(int(courses.size())-1) && courses[i].get_dept()!=courses[i-1].get_dept() ) || (i>0 && courses[i].get_dept()==courses[i-1].get_dept() ) ) { //if there is only one course within a dept
                    if (i==0 || courses[i-1].get_dept()!=courses[i].get_dept()) {
                        start_counter=i;
                    }
                    if (int(courses[i].get_course_title().length())>title_length) { //finds largest course title name in a set
                        title_length=courses[i].get_course_title().length();
                    }
                    if (int(courses[i].get_days().length())>day_length) { //finds largest day name in a set
                        day_length=courses[i].get_days().length();
                    }
                }
                counter++;
                outfile << "Dept " << courses[i].get_dept() <<std::endl << "Coursenum  Class Title";
                if (title_length-11<0) {
                    title_length=11;
                }
                outfile << std::string(abs(title_length-11), ' ');
                outfile << "  Day" << std::string(abs(day_length-3), ' ') << "  Start Time  End Time"<<std::endl;
                outfile << "---------  -----------" << std::string(abs(title_length-11), '-');
                outfile << "  ---" << std::string(abs(day_length-3), '-') << "  ----------  --------"<<std::endl;
                for (int j=start_counter; j<(start_counter+counter); j++) {//for each course which shared a room, print its info
                    outfile << courses[j].get_course_code() << "    " << courses[j].get_course_title();
                    outfile << std::string(2+title_length-courses[j].get_course_title().length(), ' ');
                    outfile << courses[j].get_days() << std::string(2+day_length-courses[j].get_days().length(), ' ');
                    outfile << courses[j].get_start_time() << "     " << courses[j].get_end_time() << ' ' << std::endl;
                }
                outfile << counter << " entries" << std::endl << std::endl;
            }
        }
    }
}