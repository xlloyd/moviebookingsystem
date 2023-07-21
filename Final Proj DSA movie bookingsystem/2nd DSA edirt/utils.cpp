#include "utils.h"
#include <iostream>
#include <cstdlib>  //Include the cstdlib library for general purpose functions, such as memory allocation and conversion functions
#include <windows.h> //Include the windows.h header for Windows-specific functions and types
#include <conio.h>  //header for console input/output functions (specific to Windows)
#include <regex>   //Include the regex library for regular expression functionality

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
    std::cout << std::flush;
}

std::unordered_map<std::string, Movie> movies;
std::vector<User> users;

// Trim leading and trailing whitespaces from a string

// Check if the time string has a valid format (HH:MMAM/HH:MMPM)
bool isValidTimeFormat(const std::string& time) {
    const std::regex pattern(R"(^(0?[1-9]|1[0-2]):[0-5][0-9](AM|PM)$)");
    return std::regex_match(time, pattern);
}

// Check if the duration string has a valid format (HH:MM:SS)
bool isValidDurationFormat(const std::string& duration) {
    if (duration.length() != 8) {
        return false;
    }
    if (!isdigit(duration[0]) || !isdigit(duration[1]) ||
        duration[2] != ':' ||
        !isdigit(duration[3]) || !isdigit(duration[4]) ||
        duration[5] != ':' ||
        !isdigit(duration[6]) || !isdigit(duration[7])) {
        return false;
    }

    int hour = std::stoi(duration.substr(0, 2));
    int minute = std::stoi(duration.substr(3, 2));
    int second = std::stoi(duration.substr(6, 2));

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return false;
    }

    return true;
}

// Check if the name string is a valid full name (no digits)
bool isValidFullName(const std::string& name) {
    return !name.empty() && !std::any_of(name.begin(), name.end(), ::isdigit);
}

// Check if the name string already exists in the user list
bool isDuplicateFullName(const std::string& name) {
    for (const auto& user : users) {
        if (user.name == name) {
            return true;
        }
    }
    return false;
}

// Check if the phoneNumber string is a valid 11-digit phone number
bool isValidPhoneNumber(const std::string& phoneNumber) {
    return phoneNumber.length() == 11 && std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
}

// Check if the phoneNumber string already exists in the user list
bool isDuplicatePhoneNumber(const std::string& phoneNumber) {
    for (const auto& user : users) {
        if (user.phoneNumber == phoneNumber) {
            return true;
        }
    }
    return false;
}

// Check if the emailAddress string is a valid email address format
bool isValidEmailAddress(const std::string& emailAddress) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(emailAddress, pattern) && emailAddress.find("@") != 0 && emailAddress.find(".") != emailAddress.length() - 1;
}

// Check if the emailAddress string already exists in the user list
bool isDuplicateEmailAddress(const std::string& emailAddress) {
    for (const auto& user : users) {
        if (user.emailAddress == emailAddress) {
            return true;
        }
    }
    return false;
}

// Check if the movieTitle exists in the movies list
bool isMovieTitleExists(const std::string& movieTitle, const std::unordered_map<std::string, Movie>& movies) {
    auto it = movies.find(movieTitle);
    if (it != movies.end()) {
        return it->second.exists;
    }
    return false;
}

// Check if the price string is a valid format (e.g., 10.99)
bool isValidPrice(const std::string& price) {
    const std::regex pattern(R"([0-9]+(\.[0-9]{1,2})?)");
    return std::regex_match(price, pattern);
}

// Check if the time string has a valid format (HH:MMAM/HH:MMPM)
bool isValidAvailableTime(const std::string& time) {
    std::regex timeRegex(R"(\d{1,2}:\d{2}(AM|PM))");
    return std::regex_match(time, timeRegex);
}

// Check if the time string is available in the availableTimes vector
bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time) {
    for (const auto& availableTime : availableTimes) {
        if (availableTime == time) {
            return true;
        }
    }
    return false;
}

// Check if the seat string has a valid format (e.g., A1, B10)
bool isValidSeat(const std::string& seat) {
    std::string trimmedSeat = seat;
    // Remove hyphen ("-") from the seat string
    trimmedSeat.erase(std::remove(trimmedSeat.begin(), trimmedSeat.end(), '-'), trimmedSeat.end());

    // Trim leading and trailing whitespace characters
    trimmedSeat = std::regex_replace(trimmedSeat, std::regex("^\\s+"), "");
    trimmedSeat = std::regex_replace(trimmedSeat, std::regex("\\s+$"), "");

    const std::regex pattern(R"([A-F](?:[1-9]|1[0-9]|20))");
    return std::regex_match(trimmedSeat, pattern);
}

// Check if the seat string is a duplicate (already booked)
bool isDuplicateSeat(const std::string& seat, const std::vector<User>& users) {
    for (const auto& user : users) {
        if (user.seat == seat) {
            return true;
        }
    }
    return false;
}

// Check if the seat string is already booked
bool isSeatBooked(const std::string& seat, const std::vector<User>& users) {
    for (const User& user : users) {
        if (user.seat == seat) {
            return true;
        }
    }
    return false;
}
