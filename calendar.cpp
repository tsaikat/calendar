#include "calendar.h"


bool Calendar::pushEvent(DateTime date, std::shared_ptr<Event>& event) {
    if (database.find(date) == database.end()) {
        database[date] = event;
        return true;
    } else {
        std::cout << "Oops! an event already exist on " << date << std::endl;
        if (promptBool("Do you want to replace the existing event? (y/n)") ) {
            database[date] = event;
            return true;
        }
    }
    return false;
}

bool Calendar::promptBool(const std::string question) const {
    std::string answer;
    while ( answer != "y" && answer != "n" ) {
        std::cout << question << std::endl;
        getline(std::cin, answer);
    }
    if (answer == "y") return true;
    return false;
}

bool Calendar::printEvents(DateTime& begin, DateTime& end) {
    auto itBegin = database.lower_bound(begin);
    auto itEnd = database.upper_bound(end);
    bool firstIter = true;
    for (; itBegin != itEnd; ++itBegin) {
        if (!firstIter) {
            std::cout << std::setfill ('.') << std::setw (22) << " |";
        } else {
            firstIter = false; 
        }
        std::cout << *(itBegin->second);
    } 
    return !firstIter;
}

void Calendar::printEvents(DateTime& dayBegin) {
    DateTime dayEnd = dayBegin;
    dayEnd.setTime(23);
    auto itBegin = database.lower_bound(dayBegin);
    auto itEnd = database.upper_bound(dayEnd);
    for (; itBegin != itEnd; ++itBegin) {
        std::cout << std::setfill (' ') << std::setw (17) << itBegin->first.getTime()<<":00"<< " |";
        std::cout << *(itBegin->second);
    } 
}