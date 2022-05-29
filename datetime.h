#ifndef __DATE_AND_TIME__
#define __DATE_AND_TIME__

#include <iostream>
#include <tuple>
#include <iomanip>
#include <ctime>


class DateTime {
public:
    DateTime(const unsigned& year, const unsigned& month, const unsigned& day, const unsigned& time = 0);
    DateTime(const DateTime &other);
    DateTime();

    //checks weather the date this entity holds is valid or not
    bool isValid () const;

    //Auxiliary methods
    bool isLeapYear (unsigned year) const;
    friend bool operator < ( const DateTime& lhs, const DateTime& rhs);
    friend std::ostream& operator << (std::ostream &oss, const DateTime& date);
    DateTime operator ++ ();
    bool operator == ( const DateTime& rhs) const;
    bool operator != ( const DateTime& rhs) const;
    // bool operator < ( const DateTime& rhs) const;
    DateTime operator + (unsigned days);

    unsigned daysInMonth() const;
    DateTime currDateTime();
    void resetWeek ();


    // Howard Hinnant's Algorithm [https://howardhinnant.github.io/date/date.html]
    unsigned dateToDays() noexcept;
    DateTime daysToDate(unsigned days) noexcept;

    // Adopted From Sakamoto's methods [https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week]
    std:: string dayOfWeek () const;
    // printing stuff
    std::string formatDate () ;
    

    // Getter & Setters
    unsigned getTime() const;
    void setTime(const unsigned time);
    void setDay(unsigned day);
    std::string getDate() const;

private:
    unsigned mYear;
    unsigned mMonth;
    unsigned mDay;
    unsigned mTime;
};

#endif