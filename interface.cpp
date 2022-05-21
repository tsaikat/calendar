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

bool Interface::promptChoice(const int& lowest, const int& highest, int& choice) const {
    std::string input;
    std::string low = std::to_string(lowest);
    std::string high = std::to_string(highest);
    
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    if (input.size() == 1 && input >= low && input <= high) {
        choice = stoi(input);
        return true;
    }
    return false;
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
            popUpMsg("Oops! command doesnt exist! Click <ENTER> to try again.");
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
            popUpMsg("Oops! command doesnt exist! Click <ENTER> to try again.");
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
            popUpMsg("Oops! command doesnt exist! Click <ENTER> to try again.");
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

void Interface::start() {
    printStartPage();
    int choice;

    while (true) {
        printManu();    
        if (!promptChoice(0,8, choice) ) {
            popUpMsg("Oops! command doesnt exist! Click <ENTER> to try again.");
            continue;
        }
            
        if ( choice == 0) {
            clearConsole();
            break;
        } else if ( choice == 1) {
            viewCalendar();
        } else if ( choice == 2) {
            // add event 
        } else if ( choice == 3) {
            findEvent();
        } else if ( choice == 4) {
            //move event
        } else if ( choice == 5) {
            //delete event
        } else if ( choice == 6) {
            //find free spot
        } else if ( choice == 7) {
            // import event
        } else if ( choice == 8) {
            exportEvent();
        }
    }
}