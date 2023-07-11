#include "fileio.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <limits>


void saveDataToFile() {
    std::ofstream outFile("data1.dat");
    if (!outFile.is_open()) {
        std::cout << "Failed to open data file for writing!\n";
        return;
    }

    // Write movie data
    outFile << movies.size() << "\n";
    for (const auto& movie : movies) {
        outFile << movie.second.title << "\n";
        outFile << movie.second.price << "\n";
        outFile << movie.second.duration << "\n";
        outFile << movie.second.availableTimes.size() << "\n";
        for (const auto& time : movie.second.availableTimes) {
            outFile << time << "\n";
        }
        outFile << movie.second.cinema << "\n"; // Add cinema to the file
    }


    outFile << users.size() << "\n";
    for (const auto& user : users) {
        outFile << user.name << "\n";
        outFile << user.phoneNumber << "\n";
        outFile << user.emailAddress << "\n";
        outFile << user.movieTitle << "\n";
        outFile << user.availableTime << "\n";
        outFile << user.cinema << "\n"; // Add cinema to the file
    }

    outFile.close();
}

void loadDataFromFile() {
     std::ifstream inFile("data1.dat");
    if (!inFile.is_open()) {
        std::cout << "Failed to open data file for reading!\n";
        return;
    }

    movies.clear();
    users.clear();

    // Read movie data
    int movieCount;
    inFile >> movieCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < movieCount; ++i) {
        Movie movie;
        std::getline(inFile, movie.title);
        inFile >> movie.price;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(inFile, movie.duration);
        int timeCount;
        inFile >> timeCount;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int j = 0; j < timeCount; ++j) {
            std::string time;
            std::getline(inFile, time);
            movie.availableTimes.push_back(time);
        }
        std::getline(inFile, movie.cinema); // Read cinema from the file
        movies[movie.title] = movie;
    }


    int userCount;
    inFile >> userCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < userCount; ++i) {
        User user;
        std::getline(inFile, user.name);
        std::getline(inFile, user.phoneNumber);
        std::getline(inFile, user.emailAddress);
        std::getline(inFile, user.movieTitle);
        std::getline(inFile, user.availableTime);
        std::getline(inFile, user.cinema); // Read cinema from the file
        users.push_back(user);
    }

    inFile.close();
}

