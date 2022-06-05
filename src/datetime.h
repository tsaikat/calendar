#ifndef __DATE_AND_TIME__
#define __DATE_AND_TIME__

#include <iostream>
#include <tuple>
#include <iomanip>
#include <ctime>

/**
 * @class DateTime
 * A class to represent date and time and methods to work with date and time.
 */
class DateTime {
public:
    /**
     * Constructs an entity of DateTime
     * @param year 
     * @param month
     * @param day
     * @param time default set to 0
     */
    DateTime(const unsigned& year, const unsigned& month, const unsigned& day, const unsigned& time = 0);
    /**
     * Copy constructor
     * @param other existing DateTime object to be copied from.
     */
    DateTime(const DateTime &other);
    /// Empty constructor
    DateTime();
    /**
     * Converts a well formated date from string to DateTime and stores in the current instance, time is alaways set to 0
     * This may throw exception
     * @param dateStr a date in the form of string
     */
    void strToDate(const std::string& dateStr);

    /**
     * Checks whether the date this entity holds is valid or not
     * @return true if valid, false if invalid
     */
    bool isValid () const;
    /**
     * Checks if a year is a leap year
     * @param year pass the year that needs to be checked
     * @return true if it's a leap year, false otherwise
     */
    bool isLeapYear (unsigned year) const;
    /**
     * (friend function)
     * overloading < operator to compare two instances of DateTime
     * @param lhs DateTime instance on the left side of < operator
     * @param rhs Datetime instance on the right side of < operator
     * @return true if lhs is smaller than rhs, false otherwise
     */
    friend bool operator < ( const DateTime& lhs, const DateTime& rhs);
    /**
     * (friend function)
     * overloads << operator for DateTime entity
     * @return formatted date and time
     */
    friend std::ostream& operator << (std::ostream &oss, const DateTime& date);
    
    /// Increases date by one day forward (pre-increment)
    DateTime operator ++ ();
    /// compares two instances of DateTime for quality
    bool operator == ( const DateTime& rhs) const;
    /// compares two instance of DateTime for inequality
    bool operator != ( const DateTime& rhs) const;
    /// adds days to the current date
    DateTime operator + (unsigned days);
    /// @return how many days in current month
    unsigned daysInMonth() const;
    /// @return current local date and time as an instance of DateTime
    DateTime currDateTime() const;
    /// Sets the date back to starts of the week (Monday)
    void resetWeek ();
    /**
     * Convert the date into days
     * @return number of days
     */ 
    unsigned dateToDays();
    /**
     * Convert the days into a date
     * @return date as a DateTime instance
     */
    DateTime daysToDate(unsigned days);

    /**
     * Finds out what day of the week it is
     * @return day of the week as a string 
     */
    std:: string dayOfWeek () const;
    /**
     * Format date with day of the week
     * @return formatted date and weekday as a string
     */
    std::string formatDate () ;
    
    /// @return Time
    unsigned getTime() const;
    /// change the time
    void setTime(const unsigned time);
    /// change the day
    void setDay(unsigned day);
    /// @return formatted (just)date as a string
    std::string getDate() const;

private:
    unsigned mYear;
    unsigned mMonth;
    unsigned mDay;
    unsigned mTime;
};

#endif