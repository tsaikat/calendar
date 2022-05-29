#include "interface.h"

void Interface::printStartPage() const {
    clearConsole();
    std:: cout << "\n\n\n" << std:: endl;
    std:: cout << "\t---------------------" << std:: endl;
    std:: cout << "\t| Planning Calendar | " << std:: endl;
    std:: cout << "\t---------------------" << std:: endl;
    std:: cout << "\n\n\n" << std:: endl;
    std:: cout << "Please, press <ENTER> to view the manu" << std:: endl;
    std::string temp;
    getline(std::cin, temp);
}

void Interface::printManu () const {
    clearConsole();
    std::cout   << "Main Manu:\n\n"
                << "0. Exit\n"
                << "1. View Calendar\n"
                << "2. Add Event\n"
                << "3. Find Event\n"
                << "4. Move Event\n"
                << "5. Delete Event\n"
                << "6. Find Free Time\n"
                << "7. Import Events\n"
                << "8. Export Events" << std::endl;
}

void Interface::printViewManu () const {
    clearConsole();
    std:: cout << "Main Manu >> View Calender:\n" << std:: endl;
    std:: cout << "0. Return Back" << std:: endl;
    std:: cout << "1. Daily View" << std:: endl;
    std:: cout << "2. Weekly View" << std:: endl;
    std:: cout << "3. Monthly View" << std:: endl;
}
void Interface::printFindManu () const {
    clearConsole();
    std::cout << "Main Manu >> Find Event:\n" << std::endl;
    std::cout << "0. Return Back" << std::endl;
    std::cout << "1. By Name of Event" << std::endl;
    std::cout << "2. By Place of Event" << std::endl;
}

void Interface::printExportManu () const {
    clearConsole();
    std::cout << "Main Manu >> Export Event:\n" << std:: endl;
    std::cout << "0. Return Back"  << std::endl;
    std::cout << "1. In CSV Format"  << std::endl;
    std::cout << "2. In HTML Format" << std::endl;
}

void Interface::printImportManu () const {
    clearConsole();
    std::cout << "Main Manu >> Import Event:\n" << std:: endl;
    std::cout << "0. Return Back"  << std::endl;
    std::cout << "1. In CSV Format"  << std::endl;
}

void Interface::printHeader() const {
    clearConsole();
    std::cout <<"       Date And Time |"<<
                "       Name of Event |"<<
                "            Location |"<<
                "        Participants |"<<
                "       Type of Event |"<<
                "            Duration |"<< std::endl;
    std::cout << "------------------------------------------------------------------"
                "------------------------------------------------------------------" << std::endl;
}


void Interface::clearConsole() const { std::cout << "\033c"; }

bool Interface::promptChoice(const int& low, const int& high, int& choice) const {
    std::string buffer;
    int input;
    std::cin >> buffer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    for (auto & it: buffer) {
        if (it < '0' || it > '9') return false;
    }
    
    try {
        input = stoi(buffer);
    } catch(...) {
        return false;
    }

    if  (input >= low && input <= high) {
        choice = input;
        return true;
    }
    return false;
}
int Interface::promptChoice(const std::string question, const int& low, const int& high) const {
    int choice = -1;
    while (choice == -1) {
        std::cout << question << std::endl;
        if (!promptChoice(low, high, choice) ) {
            std::cout << "Oops! Invalid input. Try again." << std::endl;
        }
    }
    return choice;    
}
void Interface::popUpMsg (const std::string& msg) const {
    clearConsole();
    std::cout << msg <<std::endl;
    std::string temp;
    getline(std::cin, temp);
}

void Interface::goBack() const {
    std::cout << "\n\n\nPress <ENTER> to return" <<std::endl;
    std::string temp;
    getline(std::cin, temp);
}


void Interface::dailyView() {
    DateTime date;
    if (promptBool("Type 't' to view current week or 'c' for entering custom date.", "t", "c") ) {
        date = date.currDateTime();
        date.setTime(0);
    } else {
        date = promptDateTime();
    }
    printHeader();
    std::cout << std::setfill (' ') << std::setw (22) << date.formatDate() << std::endl
              << std::setfill('-') <<std::setw(22) <<"-" << std::endl;
    calendar.printEvents(date);
    goBack();
}
void Interface::weeklyView() {
    DateTime date;
    if (promptBool("Type 't' to view current week or 'c' for entering custom date.", "t", "c") ) {
        date = date.currDateTime();
        date.setTime(0); // Not necessary anymore because of resetWeek()
    } else {
        date = promptDateTime();
    }
    date.resetWeek();

    printHeader();
    for (size_t i = 0; i < 7; ++i, ++date) {
        DateTime dayBegin = date;
        DateTime dayEnd = date;
        dayEnd.setTime(23);

        //PRINTING HERE
        std::cout << std::setfill (' ') << std::setw (22) << dayBegin.formatDate();
        if (!calendar.printEvents(dayBegin, dayEnd) ) std::cout << std::endl;
    }
    goBack();
}

void Interface::monthlyView() {
    DateTime date;
    if (promptBool("Type 't' to view current month or 'c' for entering custom date.", "t", "c") ) {
        date = date.currDateTime();
        date.setTime(0); 
    } else {
        date = promptDateTime();
    }
    printHeader();
    for (size_t i = 1; i <= date.daysInMonth(); ++i) {
        date.setDay(i); //sets the date to first day of the month
        DateTime dayBegin = date;
        DateTime dayEnd = date;
        dayEnd.setTime(23);
        // print all dates in the month here3
        std::cout << std::setfill (' ') << std::setw (22) << dayBegin.formatDate();
        if (!calendar.printEvents(dayBegin, dayEnd) ) std::cout << std::endl;
    }

    goBack();
}


void Interface::viewCalendar () {
    int choice;
    while (true) {
        printViewManu();
        if (!promptChoice(0,3, choice) ) {
            popUpMsg("Oops! command doesn't exist! Press <ENTER> to try again.");
            continue;
        }
        
        if ( choice == 0) {
            return;
        } else if ( choice == 1 ) {
            dailyView();
        } else if ( choice == 2 ) {
            weeklyView();
        } else if ( choice == 3 ) {
            monthlyView();
        }
    }

}

void Interface::findEvent () {
    int choice;
    while (true) {
        printFindManu();
        if (!promptChoice(0,2, choice) ) {
            popUpMsg("Oops! command doesn't exist! Press <ENTER> to try again.");
            continue;
        }
        
        if ( choice == 0) {
            return;
        } else if ( choice == 1 ) {
            std::string name = promptQuestion("Type the name of the event you're looking for:");
            clearConsole();
            printHeader();
            if (!calendar.findByName(name))  {
                popUpMsg("No match found! Press <ENTER> to try again.");
                continue;
            }
            goBack();
        } else if ( choice == 2 ) {
           std::string name = promptQuestion("Type the location of the event you're looking for:");
            clearConsole();
            printHeader();
            if (!calendar.findByPlace(name))  {
                popUpMsg("No match found! Press <ENTER> to try again.");
                continue;
            }
            goBack();
        }
    }
}

void Interface::exportEvents () {
    int choice;
    while (true) {
        printExportManu();
        if (!promptChoice(0,2, choice) ) {
            popUpMsg("Oops! command doesn't exist! Press <ENTER> to try again.");
            continue;
        }
        
        if ( choice == 0) {
            return;
        } else if ( choice == 1 ) {
            std::string fileName = "Events exported to "; 
            fileName += calendar.exportCSV();
            fileName += "\nPress <ENTER> to return.";
            popUpMsg(fileName);
        } else if ( choice == 2 ) {
            // Export in .html format
        }
    }
}

void Interface::importEvents() {
    int choice;
    while (true) {
        printImportManu();
        if (!promptChoice(0,1, choice) ) {
            popUpMsg("Oops! command doesn't exist! Press <ENTER> to try again.");
            continue;
        }
        if ( choice == 0) {
            return;
        } else if ( choice == 1) {
            // std::string fileName = promptQuestion("Please enter file path/name" ); 
            calendar.importCSV();
        }
    }
}


void Interface::deleteEvent() {
        clearConsole();
        std::cout << "Main Manu >> Delete Event:\n" << std:: endl;
        DateTime date;
        date = promptDateTime(true); //true because we need date too
        if (calendar.deleteEvent(date)) {
            popUpMsg("Event was deleted successfully! Press <ENTER> to return to manu");
        } else {
            popUpMsg("Event was not found! Press <ENTER> to return to manu");
        }
}

void Interface::findFreeTime() {
    clearConsole();
    std::cout << "Main Manu >> Find Free Time:\n" << std:: endl;
    DateTime date;
    if (promptBool("Type 't' to search for free time today or 'c' for a differnt date", "t", "c")) {
        date = date.currDateTime();
    } else {
        date = promptDateTime(true);
    }
    int duration = promptChoice("Enter the duration of the event", 1, 23);
    clearConsole();
    calendar.printFreeTime(date, duration);
    goBack();
}


void Interface::moveEvent() {
    clearConsole();
    std::cout << "Main Manu >> Move Event:\n" << std:: endl;
    std::cout << "What event do you want to move?" <<std::endl;
    DateTime moveFrom = promptDateTime(true);
    std::cout << "When do you want to move to?" <<std::endl;
    DateTime moveTo = promptDateTime(true);
    calendar.moveEvent(moveFrom, moveTo);
}


void Interface::addEvent() {
    clearConsole();
    std::cout << "Main Manu >> Add Event:\n" << std:: endl;
    
    std::string eventName;
    std::string eventPlace;
    int eventParticipants;
    int eventType;
    int eventRecur = 1;
    int interval = 1;
    int eventDuration;

    eventName = promptQuestion("Type your event name:");
    eventPlace = promptQuestion("Type your event location:");
    eventParticipants = promptChoice("How many people will participate in the event? (Limit: 2000)", 2, 2000);
    eventType = promptChoice("What type of event is it?\n" 
                                "1. Important\n"
                                "2. Optional\n" 
                                "3. Moveable", 1, 3);
    if ( promptBool("Do you want to make it recurring? (y/n)", "y", "n") ) {
        eventRecur = promptChoice("How many times do you want it to occur? (limit: 500)", 2, 500);
        interval += promptChoice("What's the intervals between each ocurrance in days? (e.g. 0 = Daily | limit: 500)", 0, 500 );
    }
    DateTime eventDateTime = promptDateTime(true);
    eventDuration = promptChoice("What's the duration of the event in hours? (1 - 24)", 1, 24);
    // create an event out of the date received
    std::shared_ptr<Event> newEvent; 
    if (eventType == 1) {
        newEvent = std::make_shared<Important>(eventName, eventPlace, eventDuration, eventParticipants);
    } else if (eventType == 2) {
        newEvent = std::make_shared<Optional>(eventName, eventPlace, eventDuration, eventParticipants);
    } else if (eventType == 3) {
        newEvent = std::make_shared<Moveable>(eventName, eventPlace, eventDuration, eventParticipants);
    }
    unsigned days = eventDateTime.dateToDays();
    unsigned success = 0;
    for ( int i = 0; i < eventRecur; ++i, days += interval) {
        DateTime date = date.daysToDate(days);
        date.setTime(eventDateTime.getTime() );
        if (calendar.pushEvent(date, newEvent)) success ++;
    }
    if (success) {
        std::string msg = std::to_string(success) + " " +
                            "event(s) added to calendar successfully!\n" +
                            "Press <ENTER> to return to main manu.";
        popUpMsg(msg);
    } else {
        popUpMsg ("No event was added!\nPress <ENTER> to return to main manu.");
    }
}


DateTime Interface::promptDateTime(bool getTime) {
    while (true) {
        std::string dateInput;
        int day, month, year;
        int time = 0;
        std::cout << "Insert date in format: DD.MM.YYYY ( e.g. 12.06.2022 )" << std::endl;
        getline(std::cin, dateInput);
        if (!checkFormat(dateInput) ) {
            std::cout << "Invalid date format. Try again!" << std::endl;
            continue;
        }
        parseDate(dateInput, day, month, year);
        if (getTime) {
            time = promptChoice("Insert the time of the event (0 - 23)", 0, 23);
        }
        DateTime date (year, month, day, time);
        if (date.isValid()) return date;

        std::cout << "Oops! The date you entered is not valid. Try again!" << std::endl;
        continue;
    }
}

void Interface::parseDate (std::string& date, int& day, int& month, int& year) {
        std::stringstream stream(date);
        char dot;
        stream >> day >> dot >> month >> dot >> year;
}

bool Interface::checkFormat (const std::string& date) const {
    if (date.length() != 10 ) return false;
    if (date[2] != '.' || date[5] != '.') return false;
    for (int i = 0; i < 10; i ++) {
        if (i == 2 || i == 5) continue;
        else if ( date[i] < '0' || date[i] > '9' ) return false;
    }
    return true;
}

bool Interface::promptBool(const std::string question, const std::string iTrue, const std::string iFlase) const {
    std::string answer;
    while ( answer != iTrue && answer != iFlase ) {
        std::cout << question << std::endl;
        getline(std::cin, answer);
    }
    if (answer == iTrue) return true;
    return false;
}
std::string Interface::promptQuestion(const std::string& question, const size_t length) const {
    std::string answer;
    while ( answer.empty()) {
        std::cout << question <<std::endl;
        getline(std::cin, answer);
        if (answer.empty() ) std::cout << "Cannot be left blank. Please, try again!" <<std::endl;
        if (answer.length() > length ) {
            std::cout << "Oops! Too long. Keep it below " << length << " characters."<< std::endl;
            answer.clear();
        }
    }
    return answer;
}

void Interface::start() {
    printStartPage();
    int choice;

    while (true) {
        printManu();    
        if (!promptChoice(0,8, choice) ) {
            popUpMsg("Oops! command doesn't exist! Press <ENTER> to try again.");
            continue;
        }
            
        if ( choice == 0) {
            clearConsole();
            break;
        } else if ( choice == 1) {
            viewCalendar();
        } else if ( choice == 2) {            
            addEvent();
        } else if ( choice == 3) {
            findEvent();
        } else if ( choice == 4) {
            moveEvent();
        } else if ( choice == 5) {
            deleteEvent();
        } else if ( choice == 6) {
            findFreeTime();
        } else if ( choice == 7) {
            importEvents();
        } else if ( choice == 8) {
            exportEvents();
        }
    }
}