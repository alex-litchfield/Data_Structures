// File:     time.h
// Purpose:  Header file with declaration of the Time class, including member functions and private member variables.

class Time {
    public:
        Time();
        Time(int aHour, int aMinute, int aSecond);

        // ACCESSORS
        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        // MODIFIERS
        void setHour(int aHour);
        void setMinute(int aMinute);
        void setSecond(int aSecond);

        //Other member functions
        void PrintAMPM() const;

    private:  // REPRESENTATION (member variables)
        int hour;
        int minute;
        int second;
};

//nonmember functions
bool IsEarlierThan(const Time& t1, const Time& t2);