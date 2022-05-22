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
                << "6. Find Free Slot\n"
                << "7. Import Event\n"
                << "8. Export Event" << std::endl;
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
    std::cout << "1. In TEXT Format"  << std::endl;
    std::cout << "2. In HTML Format" << std::endl;
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
            std::cout << "Oops! command doesn't exist. Try again." << std::endl;
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
            // Daily view
        } else if ( choice == 2 ) {
            // Weekly view
        } else if ( choice == 3 ) {
            // Monthly view
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
            // Find EVENT by Name
        } else if ( choice == 2 ) {
            // Find EVENT by place of event
        }
    }
}

void Interface::exportEvent () {
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
            // Export in .txt format
        } else if ( choice == 2 ) {
            // Export in .html format
        }
    }
}
void Interface::addEvent() {
    clearConsole();
    std::cout << "Main Manu >> Add Event:\n" << std:: endl;
    
    std::string eventName;
    std::string eventPlace;
    int eventType;
    int eventRecur = 1;
    int interval = 0;
    int eventDuration;
    DateTime eventDateTime;

    eventName = promptQuestion("Type your event name:");
    eventPlace = promptQuestion("Type your event location:");
    eventType = promptChoice("What type of event is it?\n" 
                                "1. Important\n"
                                "2. Optional\n" 
                                "3. Moveable", 1, 3);
    if ( promptBool("Do you want to make it recurring? (y/n)") ) {
        eventRecur = promptChoice("How many times do you want it to occur? (limit: 365)", 1, 365);
        interval = promptChoice("What's the recurrance intervals in days? (limit: 365)", 0, 365 );
    }
    eventDateTime = promptDateTime(true);
    eventDuration = promptChoice("What's the duration of the event in hours? (1 - 24)", 1, 24);
    //add the event the calender;
    popUpMsg("Event was added to calendar successfully!\n\nPress <ENTER> to return to main manu.");
}

DateTime Interface::promptDateTime(bool getTime) {
    while (true) {
        std::string dateInput;
        int day, month, year;
        int time = 0;
        std::cout << "Insert date in format: DD.MM.YYYY ( e.g. \"12.06.2022\" )" << std::endl:
        getline(std::cin, dateInput);
        if (!checkFormat(dateInput) ) {
            std::cout << "Invalid date format. Try again!" << std::endl;
            continue;
        }
        perseDate(dateInput, day, month, year);
        if (getTime) {
            time = promptChoice("Insert the time of the event (0 - 23)", 0, 23);
        }
        DateTime date (year, month, day, time);
        if (date.isValid()) return date;

        std::cout << "Oops! The date you entered is not valid. Try again!" << std::endl;
        continue;
    }
}

void Interface::perseDate (std::string& date, int& day, int& month, int& year) {
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

bool Interface::promptBool(const std::string question) const {
    std::string answer;
    while ( answer != "y" && answer != "n" ) {
        std::cout << question << std::endl;
        getline(std::cin, answer);
    }
    if (answer == "y") return true;
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
            // moveEvent();
        } else if ( choice == 5) {
            // deleteEvent();
        } else if ( choice == 6) {
            //find free spot
            // freeTime();
        } else if ( choice == 7) {
            // importEvent();
        } else if ( choice == 8) {
            exportEvent();
        }
    }
}