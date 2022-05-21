#ifndef __INTERFACE__
#define __INTERFACE__
#include <iostream>
#include <string>
#include <sstream>



class Interface {
    // void addEvent();
    // void moveEvent();
    // void deleteEvent();
    // void freeTime();
    // void importEvent();
    // void viewEvents();
    // void exit();

    // Printing Program UI
    void printStartPage() const;
    void printManu () const;
    void printViewManu () const;
    void printFindManu () const;
    void printExportManu () const;


    // Methods executing a command
    void viewCalendar ();
    void findEvent();
    void exportEvent ();
    
    //Auxiliary methods for printing UI
    void clearConsole() const;
    bool promptChoice(const int& lowest, const int& highest, int& choice) const;
    void popUpMsg(const std::string& msg) const;

public:
    void start();
};

#endif