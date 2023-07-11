#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>-
#include <regex>



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


bool isValidTimeFormat(const std::string& time) {
    const std::regex pattern(R"(^(0?[1-9]|1[0-2]):[0-5][0-9](AM|PM)$)");
    return std::regex_match(time, pattern);
}

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

bool isValidFullName(const std::string& name) {
     return !name.empty() && !std::any_of(name.begin(), name.end(), ::isdigit);
}

bool isDuplicateFullName(const std::string& name) {
    for (const auto& user : users) {
        if (user.name == name) {
            return true;
        }
    }
    return false;
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
    return phoneNumber.length() == 11 && std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
}

bool isDuplicatePhoneNumber(const std::string& phoneNumber) {
    for (const auto& user : users) {
        if (user.phoneNumber == phoneNumber) {
            return true;
        }
    }
    return false;
}

bool isValidEmailAddress(const std::string& emailAddress) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(emailAddress, pattern) && emailAddress.find("@") != 0 && emailAddress.find(".") != emailAddress.length() - 1;
}

bool isDuplicateEmailAddress(const std::string& emailAddress) {
    for (const auto& user : users) {
        if (user.emailAddress == emailAddress) {
            return true;
        }
    }
    return false;
}

bool isMovieTitleExists(const std::string& movieTitle, const std::unordered_map<std::string, Movie>& movies) {
    auto it = movies.find(movieTitle);
    if (it != movies.end()) {
        return it->second.exists;
    }
    return false;
}

bool isValidPrice(const std::string& price) {
    const std::regex pattern(R"([0-9]+(\.[0-9]{1,2})?)");
    return std::regex_match(price, pattern);
}

bool isValidAvailableTime(const std::string& time) {
    std::regex timeRegex(R"(\d{1,2}:\d{2}(AM|PM))");
    return std::regex_match(time, timeRegex);
}

bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time) {
    for (const auto& availableTime : availableTimes) {
        if (availableTime == time) {
            return true;
        }
    }
    return false;
}

