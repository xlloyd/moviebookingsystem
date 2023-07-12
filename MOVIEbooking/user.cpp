#include "user.h"
#include "utils.h"
#include "fileio.h"
#include <iostream>
#include <algorithm>
#include <sstream>


void showUserConsole() {
    std::cout << "User Console\n";
    std::cout << "------------\n\n";
    clearScreen();
    while (true) {
        std::cout << "HELLO PLEASE CHOOSE\n";
        std::cout << "1. Book a movie\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice (1-2): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                std::cout << "Book a movie\n";
                bookMovie();
                break;
            case 2:
                std::cout << "Exiting User Console...\n";
                return;
            default:
                std::cout << "Invalid choice!\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }
}

void bookMovie() {
    loadDataFromFile();
    clearScreen();

    std::cout << "Available Movies:\n";
    std::cout<< "'abort' to cancel\n";
    std::cout << "-----------------\n\n";
    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    for (const auto& title : movieTitles) {
        const Movie& movie = movies[title];
        std::cout << "Title: " << movie.title << "\n";
        std::cout << "Price: " << movie.price << "\n";
        std::cout << "Duration: " << movie.duration << "\n";
        std::cout << "Cinema: " << movie.cinema << "\n";
        std::cout << "Available Times: ";
        for (const auto& time : movie.availableTimes) {
            std::cout << time << " ";
        }
        std::cout << "\n";
        std::cout << "-------------------------\n";
    }
    std::cout << "\nEnter the movie title you want to book: ";
    std::string movieTitle;
    std::getline(std::cin, movieTitle);

    if (movieTitle == "abort") {
        std::cout << "Booking process canceled.\n";
        return;
    }

    std::transform(movieTitle.begin(), movieTitle.end(), movieTitle.begin(), ::tolower);

    const Movie* movie = nullptr;
    for (const auto& pair : movies) {
        std::string lowercaseTitle = pair.first;
        std::transform(lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), ::tolower);
        if (lowercaseTitle == movieTitle) {
            movie = &pair.second;
            break;
        }
    }

    if (movie == nullptr) {
        std::cout << "Movie title not found!\n";
        return;

    }
      clearScreen();

    std::cout << "\n[Booking Process]\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    User user;

    while (true) {
        std::cout << "Enter your full name: ";
        std::getline(std::cin, user.name);

        if (user.name == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidFullName(user.name)) {
            std::cout << "Invalid full name! Please enter a valid full name.\n";
        } else if (isDuplicateFullName(user.name)) {
            std::cout << "Name already exists! Please enter a different name.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your phone number (11 digits): ";
        std::getline(std::cin, user.phoneNumber);

        if (user.phoneNumber == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidPhoneNumber(user.phoneNumber)) {
            std::cout << "Invalid phone number! Please enter a valid 11-digit phone number.\n";
        } else if (isDuplicatePhoneNumber(user.phoneNumber)) {
            std::cout << "Phone number already exists! Please enter a different phone number.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your email address: ";
        std::getline(std::cin, user.emailAddress);

        if (user.emailAddress == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidEmailAddress(user.emailAddress)) {
            std::cout << "Invalid email address! Please enter a valid email address.\n";
        } else if (isDuplicateEmailAddress(user.emailAddress)) {
            std::cout << "Email address already exists! Please enter a different email address.\n";
        } else {
            break;
        }
    }

    clearScreen();

    
while (true) {
    std::cout << "Available times:\n";
    std::cout << "'abort' to cancel.\n";

    for (size_t i = 0; i < movie->availableTimes.size(); ++i) {
        std::cout << i + 1 << ". " << movie->availableTimes[i] << std::endl;
    }

    std::cout << "Select the index of the available time: ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "abort") {
        std::cout << "Booking process canceled.\n";
        return;
    }

    bool isNumeric = true;
    for (char c : input) {
        if (!std::isdigit(c)) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        unsigned int selectedIndex = std::stoi(input) - 1;

        if (selectedIndex >= 0 && selectedIndex < movie->availableTimes.size()) {
            std::string selectedTime = movie->availableTimes[selectedIndex];
            user.availableTime = selectedTime;
            break;
        } else {
            std::cout << "Invalid index! Please enter a valid index.\n";
        }
    } else {
        std::cout << "Invalid input! Please enter a valid index.\n";
    }
}

user.movieTitle = movie->title;
users.push_back(user);
saveDataToFile();
loadDataFromFile();

std::cout << "\nMovie booked successfully!\n";

clearScreen();


}

