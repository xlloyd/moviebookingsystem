#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>
#include <vector>

// Define the 'Movie' structure representing a movie
struct Movie {
    std::string title;                              // Movie title
    double price;                                   // Price of the movie
    std::string duration;                           // Duration of the movie
    std::vector<std::string> availableTimes;        // Available showtimes
    std::string cinema;                             // Cinema location
    bool exists;                                    // Flag indicating movie existence
    std::unordered_map<std::string, bool> seatAvailability;  // Seat availability map
};

// Define the 'User' structure representing a user
struct User {
    std::string name;                               // User's name
    std::string phoneNumber;                        // User's phone number
    std::string emailAddress;                       // User's email address
    std::string movieTitle;                          // Title of the selected movie
    std::string availableTime;                       // Preferred showtime
    std::string cinema;                              // Preferred cinema location
    std::string seat;                                // Chosen seat
};

// Declare global variables to store movies and users
extern std::unordered_map<std::string, Movie> movies;
extern std::vector<User> users;

// Utility functions
void clearScreen();                                               // Clear the screen
bool isValidTimeFormat(const std::string& time);                   // Check if the time format is valid
bool isValidDurationFormat(const std::string& duration);           // Check if the duration format is valid
bool isValidFullName(const std::string& name);                     // Check if the full name is valid
bool isDuplicateFullName(const std::string& name);                 // Check if the full name is a duplicate
bool isValidPhoneNumber(const std::string& phoneNumber);           // Check if the phone number is valid
bool isDuplicatePhoneNumber(const std::string& phoneNumber);       // Check if the phone number is a duplicate
bool isValidEmailAddress(const std::string& emailAddress);         // Check if the email address is valid
bool isDuplicateEmailAddress(const std::string& emailAddress);     // Check if the email address is a duplicate
bool isValidAvailableTime(const std::string& time);                // Check if the showtime is valid
bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time);  // Check if the showtime is available
bool isMovieTitleExists(const std::string& movieTitle, const std::unordered_map<std::string, Movie>& movies);  // Check if the movie title exists
bool isValidPrice(const std::string& price);                       // Check if the price format is valid
bool isValidSeat(const std::string& seat);                         // Check if the seat is valid
bool isDuplicateSeat(const std::string& seat, const std::vector<User>& users);  // Check if the seat is a duplicate
bool isSeatBooked(const std::string& seat, const std::vector<User>& users);      // Check if the seat is booked

#endif // UTILS_H
