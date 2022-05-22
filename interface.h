#ifndef __INTERFACE__
#define __INTERFACE__
#include <iostream>
#include <string>
#include <sstream>



class Interface {
    // NOT Implemented yet
    void moveEvent();
    void deleteEvent();
    void freeTime();
    void importEvent();

    // Printing Program UI
    void printStartPage() const;
    void printManu() const;
    void printViewManu() const;
    void printFindManu() const;
    void printExportManu() const;


    // Methods executing a command
    void viewCalendar();
    void findEvent();
    void addEvent();
    void exportEvent();
    
    //Auxiliary methods for printing UI
    void clearConsole() const;
    bool promptChoice(const int& low, const int& high, int& choice) const;
    void popUpMsg(const std::string& msg) const;
    /**
     *  @param length Limit on user input, Default set to 50;
     */
    std::string promptQuestion(const std::string& question, const size_t length = 50) const;
    int promptChoice(const std::string question, const int& low, const int& high) const;
    bool promptBool(const std::string question) const;
    /**
     *  @param getTime Set this to True when we need to prompt for time as well as date. False by default;
     */
    DateTime promptDateTime(bool getTime = false);
    bool checkFormat (const std::string& date);
    void perseDate (std::string& date, int& day, int& month, int& year);


public:
    void start();
};

#endif