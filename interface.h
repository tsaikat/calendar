#ifndef __INTERFACE__
#define __INTERFACE__
#include <iostream>
#include <string>
#include <sstream>



class Interface {
    void viewCalendar();
    void addEvent();
    void moveEvent();
    void deleteEvent();
    void freeTime();
    void importEvent();
    void exportEvent();
    void searchEvent();
    void viewEvents();
    void exit();

    // printing stuff
    bool promptChoice(const int& lowNum, const int& highNum, int& choice);
    void printStartPage();
    void clearConsole() const;
    void printManu ();
    void popUpMsg(const std::string& msg) const;
    
    //sub manus
    void printViewCal ();

public:
    void start();
};

#endif