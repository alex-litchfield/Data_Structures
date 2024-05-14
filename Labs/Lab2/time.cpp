// File:    time.cpp
// Purpose: Implementation file for the Time class.

#include <iostream>
#include "time.h"

Time::Time() {	//default constructor
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) { // construct from hour, minute, second
  hour = aHour;
  minute = aMinute;
  second = aSecond;
}

int Time::getHour() const {
  return hour;
}

int Time::getMinute() const {
  return minute;
}
	
int Time::getSecond() const {
  return second;
}

void Time::setHour(int h) {
  hour = h;
}

void Time::setMinute(int m) {
  minute = m;
}

void Time::setSecond(int s) {
  second = s; 
}

void Time::PrintAMPM() const {
    std::string meridian;
    if (hour>=12) {
        meridian="pm";
        std::cout << hour << ":";
    }
    else if (hour==0) {
        meridian="am";
        std::cout << 12 << ":";
    }
    else if (hour<12) {
        meridian="am";
        std::cout << hour << ":";
    }
    if (minute<10) {
        std::cout << 0 << minute << ":";
    }
    else if (minute>=10) {
        std::cout <<minute << ":";
    }
    if (second<10) {
        std::cout << 0 << second << " " << meridian << std::endl;
    }
    if (second>=10) {
        std::cout<< second << " " << meridian << std::endl;
    }
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
    if (t1.getHour()<t2.getHour() ) {
        return true;
    }
    else if (t1.getHour()>t2.getHour() ) {
        return false;
    }

    else {
        if (t1.getMinute()<t2.getMinute() ) {
            return true;
        }
        else if (t1.getMinute()>t2.getMinute() ) {
            return false;
        }

        else {
            if (t1.getSecond()<t2.getSecond() ) {
                return true;
            }

            else {
                return false;
            }
        }
    }
}