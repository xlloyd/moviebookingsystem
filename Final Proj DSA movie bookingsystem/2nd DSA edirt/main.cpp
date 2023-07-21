#include <iostream>
#include <sstream>
#include "admin.h"    // Include the admin header file
#include "user.h"    // Include the user header file
#include "fileio.h"    // Include the fileio header file
#include "utils.h"    // Include the utils header file

const std::string RESET_COLOR = "\033[0m";    // Reset color code for console
const std::string RED_COLOR = "\033[31m";     // Red color code for console
const std::string GREEN_COLOR = "\033[32m";   // Green color code for console
const std::string YELLOW_COLOR = "\033[33m";  // Yellow color code for console
const std::string BLUE_COLOR = "\033[34m";    // Blue color code for console


int main() {


    while (true) {
        std::cout << YELLOW_COLOR << "======================================\n"<< RESET_COLOR ;
        std::cout << YELLOW_COLOR << "              Welcome!           \n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "       MOVIE BOOKING SYSTEM!     \n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "======================================\n"<< RESET_COLOR;
        std::cout << std::string(1, '\n');
        std::cout << "Please select an option:\n";    // Display the menu options
        std::cout << std::string(1, '\n');
        std::cout << GREEN_COLOR << "[1] " << RESET_COLOR << "Admin\n";
        std::cout << GREEN_COLOR << "[2] " << RESET_COLOR << "User\n";
        std::cout << GREEN_COLOR << "[3] " << RESET_COLOR << "Exit\n";
        std::cout << std::string(1, '\n');
        std::cout << YELLOW_COLOR << "======================================\n"<< RESET_COLOR ;
        std::cout << "Enter your choice (1-3): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;    // Convert the choice string to an integer

        switch (choice) {
            case 1:
                showAdminConsole();    // Call the function to display the admin console
                break;
            case 2:
                showUserConsole();    // Call the function to display the user console
                break;
            case 3:
                std::cout << "Exiting the Movie Booking System...\n";    // Display an exit message
                saveDataToFile();    // Save the data to the file
                return 0;    // Exit the program
            default:
                std::cout << "Invalid choice!\n";    // Display an error message for an invalid choice
        }

        std::cout << "Press Enter to continue...";    // Prompt the user to press Enter to continue
        std::cin.ignore();    // Ignore any remaining characters in the input buffer

        clearScreen();    // Clear the screen
    }

    return 0;
}
