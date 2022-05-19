#include "interface.h"

void Interface::printManu () {
    clearConsole();
    std:: cout << "---------------------" << std:: endl;
    std:: cout << "| Planning Calendar | " << std:: endl;
    std:: cout << "---------------------\n\n" << std:: endl;

    std::cout << "Choose an option to nevigate\n\n"
                << "0. Exit\n"
                << "1. View Calendar\n"
                << "2. Add Event\n"
                << "3. Find Event\n"
                << "4. Move Event\n"
                << "5. Delete Event\n"
                << "6. Find Free Slot\n"
                << "7. Import Events\n"
                << "8. Export Events\n\n";
}

void Interface::clearConsole() const { std::cout << "\033c"; }

void Interface::printStartPage() {
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
bool Interface::promptChoice(const int& lowNum, const int& highNum, int& choice) {
    std::string input;
    std::string low = std::to_string(lowNum);
    std::string high = std::to_string(highNum);
    
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    if (input.size() == 1 && input >= low && input <= high) {
        choice = stoi(input);
        return true;
    }
    return false;
}

void Interface::popUpMsg(const std::string& msg) const {
    clearConsole();
    std::cout <<"\n" << msg <<std::endl;
    std::string temp;
    getline(std::cin, temp);
}

void Interface::printViewCal () {
    clearConsole();
    std:: cout << "---------------------" << std:: endl;
    std:: cout << "| Planning Calendar | " << std:: endl;
    std:: cout << "---------------------\n\n" << std:: endl;

    std:: cout << "1. Daily View" << std:: endl;
    std:: cout << "1. Weekly View" << std:: endl;
    std:: cout << "3. Monthly View" << std:: endl;
}


void Interface::start() {
    printStartPage();
    printManu();
    
    int choice;
    while (true) {
        
        if (!promptChoice(0,8,choice) ) {
            popUpMsg("Oops! command doesnt exist! Click <ENTER> to try again.");
            printManu();
        }
            
        if ( choice == 0) {
            clearConsole();
            break;
        } else if ( choice == 1) {
            printViewCal();
            
        } else if ( choice == 2) {
            
        } else if ( choice == 3) {
            
        } else if ( choice == 4) {
            
        } else if ( choice == 5) {
            
        } else if ( choice == 6) {
            
        } else if ( choice == 7) {
            
        } else if ( choice == 8) {
            
        }
    }

}
