#include "fileio.h"    // Include the fileio header file
#include "utils.h"     // Include the utils header file
#include <iostream>
#include <fstream>
#include <limits>

void saveDataToFile() {
    std::ofstream outFile("data1.dat");    // Create an output file stream and open "data1.dat" file
    if (!outFile.is_open()) {
        std::cout << "Failed to open data file for writing!\n";    // Check if the file failed to open for writing
        return;
    }

    // Write movie data
    outFile << movies.size() << "\n";    // Write the size of the movies map
    for (const auto& movie : movies) {
        outFile << movie.second.title << "\n";    // Write the title of the movie
        outFile << movie.second.price << "\n";    // Write the price of the movie
        outFile << movie.second.duration << "\n";    // Write the duration of the movie
        outFile << movie.second.availableTimes.size() << "\n";    // Write the size of the available times vector
        for (const auto& time : movie.second.availableTimes) {
            outFile << time << "\n";    // Write each available time for the movie
        }
        outFile << movie.second.cinema << "\n";    // Write the cinema of the movie
    }

    // Write user data
    outFile << users.size() << "\n";    // Write the size of the users vector
    for (const auto& user : users) {
        outFile << user.name << "\n";    // Write the name of the user
        outFile << user.phoneNumber << "\n";    // Write the phone number of the user
        outFile << user.emailAddress << "\n";    // Write the email address of the user
        outFile << user.movieTitle << "\n";    // Write the movie title booked by the user
        outFile << user.availableTime << "\n";    // Write the available time selected by the user
        outFile << user.seat << "\n";    // Write the seat booked by the user
    }

    outFile.close();    // Close the output file stream
}

void loadDataFromFile() {
    std::ifstream inFile("data1.dat");    // Create an input file stream and open "data1.dat" file
    if (!inFile.is_open()) {
        std::cout << "Failed to open data file for reading!\n";    // Check if the file failed to open for reading
        return;
    }

    movies.clear();    // Clear the movies map
    users.clear();    // Clear the users vector

    // Read movie data
    int movieCount;
    inFile >> movieCount;    // Read the number of movies
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Ignore the newline character
    for (int i = 0; i < movieCount; ++i) {
        Movie movie;
        std::getline(inFile, movie.title);    // Read the title of the movie
        inFile >> movie.price;    // Read the price of the movie
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Ignore the newline character
        std::getline(inFile, movie.duration);    // Read the duration of the movie
        int timeCount;
        inFile >> timeCount;    // Read the number of available times
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Ignore the newline character
        for (int j = 0; j < timeCount; ++j) {
            std::string time;
            std::getline(inFile, time);    // Read each available time for the movie
            movie.availableTimes.push_back(time);
        }
        std::getline(inFile, movie.cinema);    // Read the cinema of the movie
        movies[movie.title] = movie;    // Add the movie to the movies map
    }

    // Read user data
    int userCount;
    inFile >> userCount;    // Read the number of users
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Ignore the newline character
    for (int i = 0; i < userCount; ++i) {
        User user;
        std::getline(inFile, user.name);    // Read the name of the user
        std::getline(inFile, user.phoneNumber);    // Read the phone number of the user
        std::getline(inFile, user.emailAddress);    // Read the email address of the user
        std::getline(inFile, user.movieTitle);    // Read the movie title booked by the user
        std::getline(inFile, user.availableTime);    // Read the available time selected by the user
        std::getline(inFile, user.seat);    // Read the seat booked by the user
        users.push_back(user);    // Add the user to the users vector
    }

    inFile.close();    // Close the input file stream
}
