#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>
#include <vector>

struct Movie {
    std::string title;
    double price;
    std::string duration;
    std::vector<std::string> availableTimes;
    std::string cinema;
    bool exists;
};

struct User {
    std::string name;
    std::string phoneNumber;
    std::string emailAddress;
    std::string movieTitle;
    std::string availableTime;
    std::string cinema;
};

extern std::unordered_map<std::string, Movie> movies;
extern std::vector<User> users;

void clearScreen();
bool isValidTimeFormat(const std::string& time);
bool isValidDurationFormat(const std::string& duration);
bool isValidFullName(const std::string& name);
bool isDuplicateFullName(const std::string& name);
bool isValidPhoneNumber(const std::string& phoneNumber);
bool isDuplicatePhoneNumber(const std::string& phoneNumber);
bool isValidEmailAddress(const std::string& emailAddress);
bool isDuplicateEmailAddress(const std::string& emailAddress);
bool isMovieTitleExists(const std::string& movieTitle, const std::unordered_map<std::string, Movie>& movies);
bool isValidPrice(const std::string& price);
bool isValidAvailableTime(const std::string& time);
bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time);

#endif // UTILS_H

