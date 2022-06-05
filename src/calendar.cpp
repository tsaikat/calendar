#include "calendar.h"


bool Calendar::pushEvent(DateTime date, std::shared_ptr<Event>& event) {
    if (isTimeFree(date,event->getDuration() )) {
        database[date] = event;
        return true;
    } else {
        std::cout << "Oops! an event already exist/overlapping on " << date << std::endl;
        throwMsg("Press <ENTER> to continue");
    }
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
    // Checks if the given event (data + duration) can be placed in the database by
    // comparing given event end time with next event start time
    // and previous event end time with given event start time
    if (database.begin() == database.end()) return true;
    auto it = database.lower_bound(date);
    if ( it == database.end() ) {
        --it;
        unsigned duration = it->second->getDuration();
        DateTime newDate = it->first;
        newDate.setTime(newDate.getTime()+ duration  - 1);
        return newDate < date;
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
    }
    return false;
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

void Calendar::throwMsg (const std::string& msg) const {
    std::cout << msg <<std::endl;
    std::string temp;
    getline(std::cin, temp);
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
         << "Extra,"
         << "Duration"
         << "\n";
    
    for (auto const& [date, event] : database) {
        file << date.getDate() << delim 
             << date.getTime() << delim 
             << event->getName() << delim
             << event->getPlace() << delim
             << event->getParticipants() << delim
             << event->getType() << delim
             << event->getExtra() << delim
             << event->getDuration() << "\n";
    }
    file.close();
    return fileName;
}

std::string Calendar::exportHTML() {
    std::ofstream file;
    std::string fileName = "exports/export0.html";
    size_t postfix = 0;
    while (std::filesystem::exists(fileName)) {
        fileName = "exports/export" + std::to_string(++postfix) +".html";
    }
    
    file.open(fileName, std::ios::out | std::ios::app);
    file << "<!DOCTYPE html>"
         << "<html lang=\"en\"><meta charset=\"UTF-8\">"
         << "<head><title>Planning Calendar</title></head>"
         << "<body><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" style=\"font-family:sans-serif;\">"
         << "<thead style=\"background: #5E5E5E; color: #FFFFFF;\"><tr>"
         << "<td style =\"padding-right:10px;\"> Date</td>"
		 << "<td style =\"padding-right:10px;\"> Time</td>"
		 << "<td style =\"padding-right:10px;\"> Name of Event</td>"
		 << "<td style =\"padding-right:10px;\"> Location</td>"
		 << "<td style =\"padding-right:10px;\"> Participants</td>"
		 << "<td style =\"padding-right:10px;\"> Type of Event</td>"
		 << "<td style =\"padding-right:10px;\"> Duration</td></tr></thead><tbody>";

    
    for (auto const& [date, event] : database) {
        file << "<tr>"
             << "<td style =\"padding-right:10px;\"> " << date.getDate() << "</td>"
             << "<td style =\"padding-right:10px;\"> " << date.getTime() <<":00" << "</td>"
             << "<td style =\"padding-right:10px;\"> " << event->getName() << "</td>"
             << "<td style =\"padding-right:10px;\"> " << event->getPlace() << "</td>"
             << "<td style =\"padding-right:10px;\"> " << event->getParticipants() << "</td>"
             << "<td style =\"padding-right:10px;\"> " << event->getType() << "</td>"
             << "<td style =\"padding-right:10px;\"> " << event->getDuration() << "</td>"
             << "</tr>";
    }
    file << "</tbody></table></body></html>";
    file.close();
    return fileName;
}

void Calendar::importCSV() {
    std::ifstream file;
    file.open(getFileName(), std::ios::in);
    std::string line = "";
    getline(file, line);
    // Read a line
    while (getline(file, line)) {
        std::istringstream row;
        row.str(line);
        // Veribles to make DateTime & Event
        DateTime date;
        int time = 0;
        std::string name = "";
        std::string place ="";
        int participants = 0;
        int type = 0;
        int duration = 0;
        std::string extra = "";
        int i = 0;
        try {
            // Extract each attributes from the line
            for (std::string buffer; std::getline(row, buffer, ','); ++i) {
                if (i == 0) {
                    date.strToDate(buffer);
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
                    else continue;
                } else if ( i == 6) {
                    extra = buffer;
                } else if (i == 7) {
                    duration = std::stoi(buffer);
                }
            }
        } catch (...) {
            std::cout <<"Input data that was not formatted well are being skipped..." << std::endl;
            continue;
        }

        date.setTime(time);
        if (!date.isValid()) continue;
        std::shared_ptr<Event> event; 
        if (type == 1) {
            event = std::make_shared<Important>(name, place, duration, participants, extra);
        } else if (type == 2) {
            bool lessVis = stoi(extra);
            event = std::make_shared<Optional>(name, place, duration, participants, lessVis);
        } else if (type == 3) {
            DateTime moveUntil;
            try {
                moveUntil.strToDate(extra);
            } catch (...) {
                std::cout << "Date provided for moveable unitll is not valid. skipping.." << std::endl;
                continue;
            }
            event = std::make_shared<Moveable>(name, place, duration, participants, moveUntil);
        }
        pushEvent(date, event);
    }
    throwMsg("Import completed. Press <ENTER> to return");
}

std::string Calendar::getFileName() const {
    std::string fileName;
    while ( fileName.empty() ) {
        std::cout << "Please enter a valid file path/name(exclude '.csv' e.g. examples/file) " <<std::endl;
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