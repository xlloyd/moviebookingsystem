#include <iostream>
#include <sstream>
#include "admin.h"
#include "user.h"
#include "fileio.h"
#include "utils.h"

int main() {
    loadDataFromFile();

    std::cout << "Welcome to the Cinema Booking System!\n";

    while (true) {
        std::cout << "Please select an option:\n";
        std::cout << "1. Admin\n";
        std::cout << "2. User\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                showAdminConsole();
                break;
            case 2:
                showUserConsole();
                break;
            case 3:
                std::cout << "Exiting the Movie Booking System...\n";
                saveDataToFile();
                return 0;
            default:
                std::cout << "Invalid choice!\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }

    return 0;
}
