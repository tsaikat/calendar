#ifndef __INTERFACE__
#define __INTERFACE__
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>

#include "datetime.h"
#include "event.h"
#include "calendar.h"


/**
 * @class Interface
 * Creates the interface for the entire program.
 * Stores an instance of calendar and contains method to interact with it
 */
class Interface {
    /// Prints Start Page
    void printStartPage() const;
    /// Prints Main Manu
    void printManu() const;
    /// Prints View Calendar Manu
    void printViewManu() const;
    /// Prints Find Event Manu
    void printFindManu() const;
    /// Prints Export Events Manu
    void printExportManu() const;
    /// Prints Import Events Manu
    void printImportManu() const;
    /// Prints the header for viewing the calendar in daily, weekly and monthly mode
    void printHeader() const;

    /// Clears the console for giving the illusion of nevigating to a new page by clearing the display
    void clearConsole() const;
    /// Pauses the execution by prompting for input. Upon pressing enter it executes the code below.
    void goBack() const;
    /**
     * Clears the console and popup a message
     * @param msg string that you want to pass in to popup on screen
     */
    void popUpMsg(const std::string& msg) const;
    /**
     * Prompts user for an input from a range of integers
     * @param low (inclusive) is the minimum one can choose
     * @param high (inclusive) is the maximum one can choose
     * @param choice stores the users choice if it's valid
     * @return boolean: confirms if it was successfull or not
     */
    bool promptChoice(const int& low, const int& high, int& choice) const;
    /**
     * Ask users a question and prompt for an input from a range of integers
     * @param question pass the question in the form on a string
     * @param low (inclusive) is the minimum one can choose
     * @param high (inclusive) is the maximum one can choose
     * @return a valid integer input from user
     */
    int promptChoice(const std::string question, const int& low, const int& high) const;
    /**
     * Asking for user input in string form
     * @param question question prompted to users
     * @param length limit to control user input, Default set to 50 characters
     * @return a valid string from user
     */
    std::string promptStr(const std::string& question, const size_t length = 50) const;
    /**
     * Asks user to choose from two option (e.g. yes/no)
     * @param question a string with the question asked
     * @param iTrue a string that will represent true
     * @param iFalse a string that will represent false
     * @retval true - if users input was iTrue
     * @retval false - if users input was iFalse
     */
    bool promptBool(const std::string question, const std::string iTrue, const std::string iFalse) const;
    /**
     * Asks user to input a date and checks the validity of the date
     * @param getTime when set to true, the method asks user for time as well. Set to false by default;
     * @return an instance of valid date in the form of DateTime class
     */
    DateTime promptDateTime(bool getTime = false);
    /**
     * Checks whether the format of date is valid or not
     * @param date a date in the format of string
     * @return boolean: true if the format is valid, false if it's not.
     */
    bool checkFormat (const std::string& date) const;
    /**
     * Parse a string containing a date into separate int year, month, day
     * @param date string to parse
     * @param day stores the day
     * @param month stores the month
     * @param year stores the year
     */
    void parseDate (std::string& date, int& day, int& month, int& year);

    /// Creates interface for different ways of viewing the calendar 
    void viewCalendar();
    /// Creates interface for creating and adding an event to the calendar
    void addEvent();
    /// Creates interface for finding an event from the calendar
    void findEvent();
    /// Creates interface for moving events
    void moveEvent();
    /// Creates interface for deleting an event
    void deleteEvent();
    /// Creates interface for finding available time in the calendar
    void findFreeTime();
    /// Creates interface for importing events
    void importEvents();
    /// Creates interface for exporting events
    void exportEvents();

    /// Prints daily view of the calendar
    void dailyView();
    /// Prints weekly view of the calendar
    void weeklyView();
    /// Prints monthly view of the calendar
    void monthlyView();

public:
    /// Creates the main interface of the program
    void start();

private:
    /// Keeps an instance of calendar object which contains the events and methods to intract with it
    Calendar calendar;
};

#endif