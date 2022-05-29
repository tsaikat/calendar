#include "calendar.h"


bool Calendar::pushEvent(DateTime date, std::shared_ptr<Event>& event) {
    if (isTimeFree(date,event->getDuration() )) {
    // if (database.find(date) == database.end()) {
        database[date] = event;
        return true;
    } else {
        std::cout << "Oops! an event already exist/overlapping on " << date << std::endl;
        if (promptBool("Do you want to replace the conflicting event? (y/n)") ) {
            auto it = database.lower_bound(date);
            database.erase(it);
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

bool Calendar::findByName(std::string name) {
    bool flag = false;
    for (auto const& [date, event] : database) {
        if (event->getName() == name) {
            std::cout << std::setfill(' ') << std::setw(5) <<" " << date <<" |" << *(event);
            flag = true;
        }
    }
    return flag;
}

bool Calendar::findByPlace(std::string name) {
    bool flag = false;
    for (auto const& [date, event] : database) {
        if (event->getPlace() == name) {
            std::cout << std::setfill(' ') << std::setw(5) <<" " << date <<" |" << *(event);
            flag = true;
        }
    }
    return flag;
}


bool Calendar::deleteEvent(const DateTime& date) {
    auto it = database.find(date);
    if (it != database.end()) {
        database.erase(it);
        return true;
    }
    return false;
}

bool Calendar::printFreeTime(const DateTime& inDate, const unsigned duration) {
    DateTime date = inDate;
    while ( true ) {
        if (isTimeFree(date, duration)) {
            std::cout << "Next available time is: " <<date << std::endl;
            return true;
        } else {
            date.setTime(date.getTime()+1);
        }
    }
    
}

bool Calendar::isTimeFree (const DateTime& date, unsigned eventDuration) {
    if (database.begin() == database.end()) return true;
    auto it = database.lower_bound(date);
    if ( it == database.end() ) {
        --it;
        unsigned duration = it->second->getDuration();
        DateTime newDate = it->first;
        newDate.setTime(newDate.getTime()+ duration  - 1);
        return newDate < date;
        // --it and add duration and get a newDate.. check if this newDate is smaller than date. if smaller, date is free
    }

    if ( it->first != date ) {
        auto upperBound = it;
        if (it == database.begin()) {
            DateTime endDate = date;
            endDate.setTime(endDate.getTime() + eventDuration - 1);
            return ( endDate < upperBound->first );
        } 
        --it;
        unsigned duration = it->second->getDuration();
        DateTime newDate = it->first;
        newDate.setTime(newDate.getTime() + duration - 1);
        if (!(newDate < date)) return false;
        DateTime endDate = date;
        endDate.setTime(endDate.getTime() + eventDuration - 1);
        return ( endDate < upperBound->first );
        // --it and add duration and get a newDate.. check if this newDate is smaller than date.
        // if not smaller then return false
        // if smaller then 
        // add duration to date and get endDate and check if there's anything in between these date and endDate.. if nothing then free(true), else return false.
    }
    return false;
}

void Calendar::throwMsg (const std::string& msg) const {
    std::cout << msg <<std::endl;
    std::string temp;
    getline(std::cin, temp);
}


bool Calendar::moveEvent (const DateTime& moveFrom, const DateTime& moveTo ) {
    auto it = database.find(moveFrom); 
    if (it == database.end()) {
        throwMsg("Event was NOT found! Press <ENTER> to return");
    } else if ( !it->second->isMoveable()) {
        throwMsg("This event is not Moveable! Press <ENTER> to return");
    } else if (pushEvent(moveTo, it->second)) {
        database.erase(it);
        throwMsg("Event has been moved successfully! Press <ENTER> to return");
        return true;
    }
    return false;
}


std::string Calendar::exportCSV() {
    std::ofstream file;
    std::string fileName = "exports/export0.csv";
    size_t postfix = 0;
    char delim = ',';
    while (std::filesystem::exists(fileName)) {
        fileName = "exports/export" + std::to_string(++postfix) +".csv";
    }
    file.open(fileName, std::ios::out | std::ios::app);
    file << "Date,"
         << "Time,"
         << "Name of Event,"
         << "Location," 
         << "Participants," 
         << "Type of Event,"
         << "Duration"
         << "\n";
    
    for (auto const& [date, event] : database) {
        file << date.getDate() << delim 
             << date.getTime() << delim 
             << event->getName() << delim
             << event->getPlace() << delim
             << event->getParticipants() << delim
             << event->getType() << delim
             << event->getDuration() << "\n";
    }
    file.close();
    return fileName;
}

void Calendar::importCSV() {
    std::ifstream file;
    file.open(getFileName(), std::ios::in);
    std::string line = "";
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream row;
        row.str(line);
        //veribles to make DateTime & Event
        int year =0;
        int month = 0;
        int day = 0;
        int time = 0;
        std::string name = "";
        std::string place ="";
        int participants = 0;
        int type = 0;
        int duration = 0;
        int i = 0;
        for (std::string buffer; std::getline(row, buffer, ','); ++i) {
            if (i == 0) {
                std::istringstream dateStream;
                dateStream.str(buffer);
                std::string temp;
                std::getline(dateStream, temp, '.');
                day = std::stoi(temp);
                std::getline(dateStream, temp, '.');
                month = std::stoi(temp);
                std::getline(dateStream, temp, '.');
                year = std::stoi(temp);
            } else if (i == 1) {
                time = std::stoi(buffer);
            } else if ( i == 2) {
                name = buffer;
            } else if ( i == 3) {
                place = buffer;
            } else if ( i == 4) {
                participants = std::stoi(buffer);
            } else if ( i == 5) {
                if (buffer == "Important") type = 1;
                else if (buffer == "Optional") type = 2;
                else if (buffer == "Moveable") type = 3;
            } else if ( i == 6) {
                duration = std::stoi(buffer);
            }
        }
        DateTime date (year, month, day, time);
        std::shared_ptr<Event> event; 
        if (type == 1) {
            event = std::make_shared<Important>(name, place, duration, participants);
        } else if (type == 2) {
            event = std::make_shared<Optional>(name, place, duration, participants);
        } else if (type == 3) {
            event = std::make_shared<Moveable>(name, place, duration, participants);
        }
        pushEvent(date, event);
    }
    throwMsg("Import completed. Press <ENTER> to return");
}
std::string Calendar::getFileName() const {
    std::string fileName;
    while ( fileName.empty() ) {
        std::cout << "Please enter a valid file path/name(exclude '.csv' e.g. imports/import0) " <<std::endl;
        getline(std::cin, fileName);
        if (fileName.empty() ) {
            throwMsg("Cannot be left blank. Press <ENTER> to try again!");
            continue;
        }
        fileName+= ".csv";
        if ( !std::filesystem::exists(fileName) ) {
            throwMsg("File name/path doesn't exist. Press <ENTER> to try again!");
            fileName.clear();
        }
    }
    return fileName;
}