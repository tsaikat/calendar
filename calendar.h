#ifndef __CALENDAR__
#define __CALENDAR__

#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include <filesystem>
#include "event.h"
#include "datetime.h"


class Calendar {
public:
    bool pushEvent(DateTime date, std::shared_ptr<Event>& event);   
    bool promptBool(const std::string question) const;
    bool printEvents(DateTime& begin, DateTime& end);
    void printEvents(DateTime& dayBegin);
    bool findByName(std::string name);
    bool findByPlace(std::string name);
    bool deleteEvent(const DateTime& date);
    bool printFreeTime(const DateTime& inDate, const unsigned duration);
    bool isTimeFree (const DateTime& date, unsigned eventDuration);
    bool moveEvent (const DateTime& moveFrom, const DateTime& moveTo );
    void throwMsg (const std::string& msg) const;

    std::string exportCSV();
    void importCSV();
    std::string getFileName() const;

private:
    std::map <DateTime, std::shared_ptr<Event>> database;
};


#endif