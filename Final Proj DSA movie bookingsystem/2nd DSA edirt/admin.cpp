#include "admin.h" // Header file for the Admin class
#include "utils.h" // Header file for utility functions
#include "user.h" // Header file for the User class
#include "fileio.h" // Header file for file I/O operations
#include <iostream>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <regex>
#include <fstream>
#include <limits>

const std::string RESET_COLOR = "\033[0m";
const std::string RED_COLOR = "\033[31m";
const std::string GREEN_COLOR = "\033[32m";
const std::string YELLOW_COLOR = "\033[33m";
const std::string BLUE_COLOR = "\033[34m";


void showAdminConsole() {
    // The administrator password is set to "admin"
    std::string password = "admin";
    std::string inputPassword;

    // Clears the screen
    clearScreen();

    // Displays the title of the admin console
    std::cout << GREEN_COLOR << "Admin Console" << RESET_COLOR << "\n";
    std::cout << "-------------\n\n";

    // Initializes the number of password attempts and authentication status
    int attempts = 3;
    bool authenticated = false;

    // Authenticates the user by comparing the entered password with the stored password
    while (attempts > 0) {
        clearScreen();

        std::cout << GREEN_COLOR << "Admin Console" << RESET_COLOR << "\n";
        std::cout << "-------------\n\n";
        std::cout << "Enter password (Attempts left: " << attempts << "): ";

        char c;
        while ((c = _getch()) != '\r') {
            // Handles backspace character to delete the last entered character
            if (c == '\b') {
                if (!inputPassword.empty()) {
                    inputPassword.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                inputPassword += c;
                std::cout << '*';
            }
        }

        // Compares the entered password with the stored password
        if (inputPassword == password) {
            authenticated = true;
            break;
        } else {
            std::cout << "\nIncorrect password!\n";
            inputPassword = "";
            --attempts;
        }
    }

    // Checks if authentication was successful
    if (authenticated) {
        clearScreen();
        std::cout << GREEN_COLOR << "Admin Console" << RESET_COLOR << "\n";
        std::cout << "-------------\n\n";
        std::cout << "Authentication successful!\n";
        clearScreen();
    } else {
        clearScreen();
        std::cout << GREEN_COLOR << "Admin Console" << RESET_COLOR << "\n";
        std::cout << "-------------\n\n";
        std::cout << "Maximum attempts exceeded. Returning to the main menu.\n";
        return;
    }

    // Displays the admin console menu and executes the selected option
    while (true) {
        std::cout << GREEN_COLOR << "Admin Console" << RESET_COLOR << "\n";
        std::cout << "1. Upload a movie\n";
        std::cout << "2. View users' booked movies\n";
        std::cout << "3. Modify a user's booked movie\n";
        std::cout << "4. Delete a user's booked movie\n";
        std::cout << "5. Modify movie information\n";
        std::cout << "6. View movies info\n";
        std::cout << "7. Delete a movie\n";
        std::cout << "8. Exit\n";

        std::cout << "Enter your choice (1-8): ";

        // Reads the user's choice from input
        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        // Executes the selected option based on the user's choice
        switch (choice) {
            case 1:
                std::cout << "Upload a movie\n";
                uploadMovie();
                break;
            case 2:
                std::cout << "View users' booked movies\n";
                viewUsers();
                break;
            case 3:
                std::cout << "Modify a user's booked movie\n";
                modifyUser();
                break;
            case 4:
                std::cout << "Delete a user's booked movie\n";
                deleteUser();
                break;
            case 5:
                std::cout << "Modify movie information\n";
                modifyMovieInfo();
                break;
            case 6:
                std::cout << "View movie information\n";
                viewMovieInfo();
                break;
            case 7:
                std::cout << "Delete a movie\n";
                deleteMovie();
                break;
            case 8:
                return;
            default:
                std::cout << RED_COLOR << "Invalid choice!" << RESET_COLOR << "\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }
}


void uploadMovie() {
    Movie movie;
    std::string input;

    clearScreen();
    std::cout << GREEN_COLOR << "Upload a movie" << RESET_COLOR << "\n";
    std::cout << "('abort' to cancel)\n";

    // Prompt the user to enter the movie title
    while (true) {
        std::cout << "Movie title: ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        // Validate the movie title
        if (input.empty()) {
            std::cout << RED_COLOR << "Invalid movie title!" << RESET_COLOR << "\n";
        } else {
            // Check if the movie title already exists
            bool exists = false;
            for (const auto& mov : movies) {
                if (mov.first == input) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                movie.title = input;
            } else {
                std::cout << RED_COLOR << "Movie with title " << input << " already exists!" << RESET_COLOR << "\n";
                system("pause");
                continue;
            }
            break;
        }
    }

    // Prompt the user to enter the movie price
    while (true) {
        std::cout << "Price: ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::stringstream ss(input);
        // Convert the input to a float and validate it
        if (ss >> movie.price && movie.price > 0.0) {
            break;
        } else {
            std::cout << RED_COLOR << "Invalid price!" << RESET_COLOR << "\n";
        }
    }

    // Prompt the user to enter the movie duration
    while (true) {
        std::cout << "Duration (hh:mm:ss): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        // Validate the duration format using a regular expression
        if (isValidDurationFormat(input)) {
            movie.duration = input;
            break;
        } else {
            std::cout << RED_COLOR << "Invalid duration! Use the format 'hh:mm:ss'." << RESET_COLOR << "\n";
        }
    }

    // Prompt the user to choose a cinema for the movie
    while (true) {
        std::cout << "Choose a cinema:\n";
        std::cout << "1. Cinema 1\n";
        std::cout << "2. Cinema 2\n";
        std::cout << "3. Cinema 3\n";
        std::cout << "Choose (1-3): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Cinema selection canceled.\n";
            return;
        }

        // Assign the cinema based on the user's choice
        if (input == "1") {
            movie.cinema = "Cinema 1";
            break;
        } else if (input == "2") {
            movie.cinema = "Cinema 2";
            break;
        } else if (input == "3") {
            movie.cinema = "Cinema 3";
            break;
        } else {
            std::cout << RED_COLOR << "Invalid cinema choice! Please enter a number from the list." << RESET_COLOR << "\n";
        }
    }

    // Prompt the user to enter available times for the movie
    while (true) {
        if (movie.availableTimes.size() >= 3)
            break;
        std::cout << "Available time (hh:mmAM/PM): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::string hourStr, minuteStr, meridiem;
        std::regex timeRegex(R"((\d{1,2}):(\d{2})(AM|PM))", std::regex_constants::icase);
        std::smatch timeMatch;

        // Validate the available time format using a regular expression
        if (std::regex_match(input, timeMatch, timeRegex)) {
            hourStr = timeMatch[1].str();
            minuteStr = timeMatch[2].str();
            meridiem = timeMatch[3].str();

            int hour = std::stoi(hourStr);
            int minute = std::stoi(minuteStr);

            if ((hour >= 1 && hour <= 12) && (minute >= 0 && minute <= 59)) {
                std::ostringstream formattedTime;
                formattedTime << std::setw(2) << std::setfill('0') << hourStr << ":" << std::setw(2) << std::setfill('0') << minuteStr << meridiem;
                movie.availableTimes.push_back(formattedTime.str());

                // Prompt the user to add more available times or finish the movie upload
                while (true) {
                    if (movie.availableTimes.size() >= 3)
                        break;
                    std::cout << "Do you want to add more available times? (yes/no): ";
                    std::getline(std::cin, input);
                    if (input == "yes") {
                        std::cout << "Enter the available time (hh:mmAM/PM): ";
                        std::getline(std::cin, input);
                        if (std::regex_match(input, timeMatch, timeRegex)) {
                            hourStr = timeMatch[1].str();
                            minuteStr = timeMatch[2].str();
                            meridiem = timeMatch[3].str();
                            hour = std::stoi(hourStr);
                            minute = std::stoi(minuteStr);
                            if ((hour >= 1 && hour <= 12) && (minute >= 0 && minute <= 59)) {
                                formattedTime.str("");
                                formattedTime << std::setw(2) << std::setfill('0') << hourStr << ":" << std::setw(2) << std::setfill('0') << minuteStr << meridiem;
                                // Check if the time already exists in the available times
                                if (std::find(movie.availableTimes.begin(), movie.availableTimes.end(), formattedTime.str()) != movie.availableTimes.end()) {
                                    std::cout << RED_COLOR << "Time already exists!" << RESET_COLOR << "\n";
                                } else {
                                    movie.availableTimes.push_back(formattedTime.str());
                                }
                            } else {
                                std::cout << RED_COLOR << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format." << RESET_COLOR << "\n";
                            }
                        } else {
                            std::cout << RED_COLOR << "Invalid time format! Please use the 'hh:mmAM/PM' format." << RESET_COLOR << "\n";
                        }
                    } else if (input == "no") {
                        movies[movie.title] = movie;
                        saveDataToFile();
                        loadDataFromFile();
                        std::cout << GREEN_COLOR << "Movie uploaded successfully!" << RESET_COLOR << "\n";
                        viewMovieInfo();
                        return;
                    } else if (input == "abort") {
                        std::cout << "Movie upload canceled.\n";
                        return;
                    } else {
                        std::cout << RED_COLOR << "Invalid input! Enter 'yes', 'no', or 'abort'." << RESET_COLOR << "\n";
                    }
                }
            } else {
                std::cout << RED_COLOR << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format." << RESET_COLOR << "\n";
            }
        } else {
            std::cout << RED_COLOR << "Invalid time format! Please use the 'hh:mmAM/PM' format." << RESET_COLOR << "\n";
        }
    }

    movies[movie.title] = movie;
    saveDataToFile();

    std::cout << GREEN_COLOR << "Movie uploaded successfully!" << RESET_COLOR << "\n";
    viewMovieInfo();
}

void viewUsers() {
    // Load data from file
    loadDataFromFile();

    // Clear the screen and display a header
    clearScreen();
    std::cout << "Users who have booked a movie:\n\n";

    // Sort users by name
    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return a.name < b.name;
    });

    // Calculate the maximum lengths for other fields
    size_t maxNameLength = 0;
    size_t maxPhoneNumberLength = 0;
    size_t maxEmailAddressLength = 0;
    size_t maxMovieTitleLength = 0;
    size_t maxCinemaLength = 0;
    size_t maxAvailableTimeLength = 0;
    size_t maxSeatLength = 0;

    // Iterate over users to find the maximum lengths for different fields
    for (const auto& user : users) {
        if (!user.movieTitle.empty()) { // Display only if movie title is not empty
            maxNameLength = std::max(maxNameLength, user.name.length());
            maxPhoneNumberLength = std::max(maxPhoneNumberLength, user.phoneNumber.length());
            maxEmailAddressLength = std::max(maxEmailAddressLength, user.emailAddress.length());
            maxMovieTitleLength = std::max(maxMovieTitleLength, user.movieTitle.length());
            maxCinemaLength = std::max(maxCinemaLength, movies[user.movieTitle].cinema.length());
            maxAvailableTimeLength = std::max(maxAvailableTimeLength, user.availableTime.length());
            maxSeatLength = std::max(maxSeatLength, user.seat.length());
        }
    }

    // Iterate over users and display their information
    for (const auto& user : users) {
        if (!user.movieTitle.empty()) {
            std::cout << "Name: " << std::left << std::setw(maxNameLength) << user.name << "\n";
            std::cout << "Phone Number: " << std::left << std::setw(maxPhoneNumberLength) << user.phoneNumber << "\n";
            std::cout << "Email Address: " << std::left << std::setw(maxEmailAddressLength) << user.emailAddress << "\n";
            std::cout << "Movie Title: " << std::left << std::setw(maxMovieTitleLength) << user.movieTitle << "\n";
            std::cout << "Cinema: " << std::left << std::setw(maxCinemaLength) << movies[user.movieTitle].cinema << "\n";
            std::cout << "Chosen Time: " << std::left << std::setw(maxAvailableTimeLength) << user.availableTime << "\n";

            std::cout << "Seat: " << std::left << std::setw(maxSeatLength);
            if (user.seat.empty()) {
                std::cout << "\n";
            } else {
                std::cout << user.seat << "\n";
            }

            std::cout << std::string(maxNameLength + maxPhoneNumberLength + maxEmailAddressLength +
                                      maxMovieTitleLength + maxCinemaLength + maxAvailableTimeLength + maxSeatLength + 34, '-') << "\n";
        }
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



void modifyUser() {
    // Load data from file
    loadDataFromFile();

    // Clear the screen and display a header
    clearScreen();
    std::cout << GREEN_COLOR << "Modify a user's booked movie" << RESET_COLOR << "\n";
    std::cout << "(enter 'abort' to cancel)\n";

    // Sort users by name
    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return a.name < b.name;
    });

    // Display the list of users
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". " << users[i].name << "\n";
    }

    std::string indexStr;
    size_t index;
    std::cout << "Enter the index number of the user to modify: ";
    std::getline(std::cin, indexStr);

    // Check if the user wants to abort the modification process
    if (indexStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }
    clearScreen();
    std::stringstream(indexStr) >> index;

    // Validate the user's index
    if (index <= 0 || index > users.size()) {
        std::cout << RED_COLOR << "Invalid index number!" << RESET_COLOR << "\n";
        return;
    }

    User& user = users[index - 1];

    // Prompt the user to select the action to modify
    std::cout << "Select the action to modify:\n";
    std::cout << "(enter 'abort' to cancel)\n";
    std::cout << "1. Name\n";
    std::cout << "2. Phone number\n";
    std::cout << "3. Email address\n";
    std::cout << "4. Movie title\n";
    std::cout << "5. Available time\n";
    std::cout << "6. Seat\n";
    std::cout << "Enter the action number: ";

    std::string actionStr;
    std::getline(std::cin, actionStr);

    // Check if the user wants to abort the modification process
    if (actionStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }
    clearScreen();
    int action;
    std::stringstream(actionStr) >> action;

    switch (action) {
        case 1: {
            // Modify user's name
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";
            std::string newName;
            std::cout << "Name (" << user.name << "): ";
            std::getline(std::cin, newName);
            if (newName == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newName != "skip") {
                // Validate and update the name
                if (!isValidFullName(newName)) {
                    std::cout << RED_COLOR << "Invalid full name! Please enter a valid full name." << RESET_COLOR << "\n";
                    return;
                } else if (isDuplicateFullName(newName)) {
                    std::cout << RED_COLOR << "Name already exists! Please enter a different name." << RESET_COLOR << "\n";
                    return;
                }
                user.name = newName;
            }
            break;
        }
        case 2: {
            // Modify user's phone number
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";
            std::string newPhoneNumber;
            std::cout << "Phone number (" << user.phoneNumber << "): ";
            std::getline(std::cin, newPhoneNumber);
            if (newPhoneNumber == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newPhoneNumber != "skip") {
                // Validate and update the phone number
                if (!isValidPhoneNumber(newPhoneNumber)) {
                    std::cout << RED_COLOR << "Invalid phone number! Please enter a valid 11-digit phone number." << RESET_COLOR << "\n";
                    return;
                } else if (isDuplicatePhoneNumber(newPhoneNumber)) {
                    std::cout << RED_COLOR << "Phone number already exists! Please enter a different phone number." << RESET_COLOR << "\n";
                    return;
                }
                user.phoneNumber = newPhoneNumber;
            }
            break;
        }
        case 3: {
            // Modify user's email address
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";
            std::string newEmailAddress;
            std::cout << "Email address (" << user.emailAddress << "): ";
            std::getline(std::cin, newEmailAddress);
            if (newEmailAddress == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newEmailAddress != "skip") {
                // Validate and update the email address
                if (!isValidEmailAddress(newEmailAddress)) {
                    std::cout << RED_COLOR << "Invalid email address! Please enter a valid email address." << RESET_COLOR << "\n";
                    return;
                } else if (isDuplicateEmailAddress(newEmailAddress)) {
                    std::cout << RED_COLOR << "Email address already exists! Please enter a different email address." << RESET_COLOR << "\n";
                    return;
                }
                user.emailAddress = newEmailAddress;
            }
            break;
        }
        case 4: {
            // Modify user's movie title
            std::cout << "Change Movie\n";
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";

            int i = 0;
            std::vector<std::string> movieTitles;
            for (const auto& movie : movies) {
                movieTitles.push_back(movie.first);
                i++;
                std::cout << i << ". " << movie.first << std::endl;
            }

            std::string index;
            std::cout << "Enter the index of the movie (" << user.movieTitle << "): ";
            std::getline(std::cin, index);
            if (index == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (index == "skip") {
                break;
            } else if (index.length() == 1) {
                // Validate and update the movie title
                if (isdigit(index[0]) && index[0] > '0' && index[0] <= '9') {
                    std::string movieTitle = movieTitles[std::stoi(index) - 1];
                    user.movieTitle = movieTitle;
                } else {
                    std::cout << RED_COLOR << "Invalid input!" << RESET_COLOR << "\n";
                    return;
                }
            }
            break;
        }
        case 5: {
            // Modify user's available time
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";
            std::string newTime;

            int i = 0;
            for (std::string time : movies[user.movieTitle].availableTimes) {
                i++;
                std::cout << i << ": " << time << std::endl;
            }

            std::cout << "Select time: ";
            std::getline(std::cin, newTime);

            if (newTime == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newTime != "skip") {
                int index = 0;
                if (newTime.length() == 1)
                    index = std::stoi(newTime) - 1;

                if (index < 0 || index >= static_cast<int>(movies[user.movieTitle].availableTimes.size())) {
                    std::cout << RED_COLOR << "Invalid Input." << RESET_COLOR << "\n";
                    return;
                }

                const std::string& movieTitle = user.movieTitle;
                if (!isTimeAvailable(movies[movieTitle].availableTimes, movies[user.movieTitle].availableTimes[index])) {
                    std::cout << RED_COLOR << "The selected time is not available for the movie." << RESET_COLOR << "\n";
                    return;
                }

                user.availableTime = movies[user.movieTitle].availableTimes[index];

                // Update seat availability for the previous and new time
                Movie& movie = movies[user.movieTitle];
                movie.seatAvailability[user.availableTime] = true;
                movie.seatAvailability[newTime] = false;
            }
            break;
        }
        case 6: {
            // Modify user's seat
            std::cout << "Enter 'abort' to cancel or enter 'skip' to keep the information.\n";
            std::string newSeat;
            displaySeats(users);
            std::cout << "Seat (" << user.seat << "): ";
            std::getline(std::cin, newSeat);
            if (newSeat == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newSeat != "skip") {
                if (!isValidSeat(newSeat)) {
                    std::cout << RED_COLOR << "Invalid seat number! Please enter a valid seat number (e.g., A1)." << RESET_COLOR << "\n";
                    return;
                } else if (isDuplicateSeat(newSeat, users)) {
                    std::cout << RED_COLOR << "Seat already booked! Please select a different seat." << RESET_COLOR << "\n";
                    return;
                }
                user.seat = newSeat;
            }
            break;
        }
        default:
            std::cout << RED_COLOR << "Invalid action number!" << RESET_COLOR << "\n";
            return;
    }

    // Save the modified data to the file
    saveDataToFile();

    std::cout << GREEN_COLOR << "User's information modified successfully!" << RESET_COLOR << "\n";
    viewUsers();
}



void deleteUser() {
    // Load data from file
    loadDataFromFile();

    // Clear the screen and display a header
    clearScreen();
    std::cout << BLUE_COLOR << "Delete a user's booked movie" << RESET_COLOR << "\n\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    // Sort users by name
    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return a.name < b.name;
    });

    // Create a vector to store booked users
    std::vector<User> bookedUsers;
    for (const auto& user : users) {
        if (!user.movieTitle.empty()) {
            bookedUsers.push_back(user);
        }
    }

    // Check if there are any booked users
    if (bookedUsers.empty()) {
        std::cout << "No users found.\n";
        return;
    }

    // Display the list of booked users
    for (size_t i = 0; i < bookedUsers.size(); ++i) {
        std::cout << i + 1 << ". " << bookedUsers[i].name << "\n";
    }

    std::string indexStr;
    int index;
    std::cout << "\nEnter the index number of the user to delete: ";
    std::getline(std::cin, indexStr);

    // Check if the user wants to abort the deletion process
    if (indexStr == "abort") {
        std::cout << "User deletion aborted.\n";
        return;
    }

    try {
        index = std::stoi(indexStr);

        // Validate the user's index
        if (index <= 0 || index > static_cast<int>(bookedUsers.size())) {
            throw std::out_of_range("Invalid index number!");
        }

        // Confirm the deletion with the user
        std::cout << "Are you sure you want to delete the user's information? (" << YELLOW_COLOR << "yes" << RESET_COLOR << "/" << YELLOW_COLOR << "no" << RESET_COLOR << "): ";
        std::string confirm;
        std::getline(std::cin, confirm);

        if (confirm == "yes") {
            // Find the index of the user in the original users vector
            size_t userIndex = 0;
            for (size_t i = 0; i < users.size(); ++i) {
                if (users[i].name == bookedUsers[index - 1].name) {
                    userIndex = i;
                    break;
                }
            }

            // Erase the user from the users vector
            users.erase(users.begin() + userIndex);

            // Save the modified data to the file
            saveDataToFile();
            // Reload data from the file
            loadDataFromFile();
            std::cout << GREEN_COLOR << "User information deleted successfully!" << RESET_COLOR << "\n";
        } else {
            std::cout << "Deletion canceled.\n";
        }
    } catch (const std::invalid_argument&) {
        std::cout << RED_COLOR << "Invalid index number! Please enter a valid index." << RESET_COLOR << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << RED_COLOR << e.what() << RESET_COLOR << "\n";
    }
}


void modifyMovieInfo() {
    loadDataFromFile(); // Load data from a file into the collections
    clearScreen(); // Clear the console screen
    std::cout << YELLOW_COLOR << "Modify movie information\n\n" << RESET_COLOR; // Display a heading in yellow color
    std::cout << "Enter 'abort' at any time to cancel.\n\n"; // Provide an instruction for canceling the process

    std::vector<std::string> movieTitles; // Create a vector to store movie titles
    for (const auto& movie : movies) { // Iterate over the movies collection
        movieTitles.push_back(movie.first); // Extract and add the movie title to the vector
    }
    std::sort(movieTitles.begin(), movieTitles.end()); // Sort the movie titles in alphabetical order

    if (movieTitles.empty()) { // If there are no movies available
        std::cout << "No movies available to modify.\n"; // Display a message
        std::cout << "Press Enter to exit..."; // Instruct the user to press Enter
        std::cin.ignore(); // Wait for user input
        return; // Return from the function
    }

    std::cout << "Available movie titles:\n";
    std::cout << BLUE_COLOR << "----------------------\n" << RESET_COLOR;
    for (size_t i = 0; i < movieTitles.size(); ++i) {
        std::cout << YELLOW_COLOR << i + 1 << ". " << RESET_COLOR << movieTitles[i] << "\n";
    }
    std::cout << BLUE_COLOR << "----------------------\n" << RESET_COLOR;

    std::string input;
    int selectedIndex = -1;
    bool isValidIndex = false;
    while (!isValidIndex) { // Loop until a valid index is selected
        std::cout << "Select the index of the movie to modify (1-" << movieTitles.size() << "): ";
        std::getline(std::cin, input);
        std::cout << '\n'; // Add a space

        if (input == "abort") { // If the user wants to abort the process
            std::cout << "Movie modification canceled.\n";
            return; // Return from the function
        }

        std::stringstream ss(input);
        if (ss >> selectedIndex && selectedIndex >= 1 && selectedIndex <= static_cast<int>(movieTitles.size())) {
            isValidIndex = true; // Set the flag to true if the index is valid
        } else {
            std::cout << RED_COLOR << "Invalid index!" << RESET_COLOR << "\n";
        }
    }

    clearScreen();

    std::string movieTitle = movieTitles[selectedIndex - 1];
    Movie& movie = movies[movieTitle]; // Get the reference to the selected movie

    bool modifyAnother = true;
    while (modifyAnother) { // Loop until the user doesn't want to modify another aspect
        clearScreen();

        std::cout << YELLOW_COLOR << "Select the aspect to modify:\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "1. Movie title (" << RESET_COLOR << movie.title << YELLOW_COLOR << ")\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "2. Price (" << RESET_COLOR << movie.price << YELLOW_COLOR << ")\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "3. Duration (" << RESET_COLOR << movie.duration << YELLOW_COLOR << ")\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "4. Cinema number (" << RESET_COLOR << movie.cinema << YELLOW_COLOR << ")\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "5. Available times\n" << RESET_COLOR;
        std::cout << YELLOW_COLOR << "6. Reset Seats\n" << RESET_COLOR;
        std::cout << "Enter 'abort' to cancel.\n";
        std::cout << "Enter the index of the aspect to modify (1-6): ";
        std::getline(std::cin, input);
        std::cout << '\n'; // Add a space

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (input == "1") { // If the user chooses to modify the movie title
            std::cout << "'abort' to cancel.\n";
            std::cout << YELLOW_COLOR << "Movie title (" << RESET_COLOR << movie.title << YELLOW_COLOR << "): ";
            std::getline(std::cin, input);
            std::cout << '\n'; // Add a space

            if (input == "abort") {
                std::cout << "Movie modification canceled.\n";
                return;
            }

            if (input.empty()) {
                std::cout << RED_COLOR << "Invalid movie title!" << RESET_COLOR << "\n";
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
            } else {
                bool exists = false;
                for (std::pair<std::string, Movie> mov : movies)
                    if (mov.first == input)
                        exists = true;
                if (!exists) {
                    movie.title = input;
                    saveDataToFile();
                    std::cout << GREEN_COLOR << "Movie title modified successfully!" << RESET_COLOR << "\n";
                } else {
                    std::cout << RED_COLOR << "Movie with title " << input << " already exists!" << RESET_COLOR << "\n";
                    system("pause");
                }
                continue; // Go to the next iteration of the loop
            }
        } else if (input == "2") { // If the user chooses to modify the price
            while (true) {
                std::cout << "Price (" << movie.price << "): ";
                std::getline(std::cin, input);
                std::cout << '\n'; // Add a space

                if (input == "abort") {
                    std::cout << "Movie modification canceled.\n";
                    return;
                }

                std::stringstream ss(input);
                if (ss >> movie.price && movie.price > 0.0) {
                    std::cout << GREEN_COLOR << "Price modified successfully!" << RESET_COLOR << "\n";
                    saveDataToFile();
                    break;
                } else {
                    std::cout << RED_COLOR << "Invalid price!" << RESET_COLOR << "\n";
                    std::cout << "Press Enter to continue...";
                    system("pause");
                }
                system("pause");
            }
        } else if (input == "3") { // If the user chooses to modify the duration
            while (true) {
                std::cout << "Duration (hh:mm:ss) (" << movie.duration << "): ";
                std::getline(std::cin, input);
                std::cout << '\n'; // Add a space

                if (input == "abort") {
                    std::cout << "Movie modification canceled.\n";
                    return;
                }

                if (isValidDurationFormat(input)) { // Check if the duration format is valid
                    movie.duration = input;
                    std::cout << GREEN_COLOR << "Duration modified successfully!" << RESET_COLOR << "\n";
                    saveDataToFile();
                    break;
                } else {
                    std::cout << RED_COLOR << "Invalid duration! Use the format 'hh:mm:ss'." << RESET_COLOR << "\n";
                }
                system("pause");
            }
        } else if (input == "4") { // If the user chooses to modify the cinema number
            while (true) {
                clearScreen();

                std::cout << YELLOW_COLOR << "Cinema List:\n" << RESET_COLOR;
                std::cout << "Enter 'abort' to cancel.\n";

                for (unsigned int i = 0; i < 3; ++i) {
                    std::cout << i + 1 << ". Cinema " << i + 1 << std::endl;
                }

                std::cout << "Select the index of the cinema: ";
                std::getline(std::cin, input);
                std::cout << '\n';

                if (input == "abort") {
                    std::cout << "Movie modification canceled.\n";
                    return;
                }

                if (input == "1" || input == "2" || input == "3") {
                    movie.cinema = "Cinema " + input;
                    std::cout << GREEN_COLOR << "Cinema modified successfully!" << RESET_COLOR << "\n";
                    saveDataToFile();
                    break;
                } else {
                    std::cout << RED_COLOR << "Invalid input!" << RESET_COLOR << "\n";
                }
                system("pause");
            }
        } else if (input == "5") { // If the user chooses to modify the available times
            while (true) {
                clearScreen();

                std::cout << YELLOW_COLOR << "Available times:\n" << RESET_COLOR;
                std::cout << "Enter 'abort' to cancel.\n";

                for (unsigned int i = 0; i < movie.availableTimes.size(); ++i) {
                    std::cout << i + 1 << ". " << movie.availableTimes[i] << std::endl;
                }

                if (movie.availableTimes.size() < 3)
                    std::cout << "\nA. Add Time\n";
                std::cout << "S. Save Changes\n";

                std::cout << "Select the index of the time to modify: ";
                std::getline(std::cin, input);
                std::cout << '\n'; // Add a space

                if (input == "abort") {
                    std::cout << "Movie modification canceled.\n";
                    return;
                }

                if (input == "A") { // If the user chooses to add a new time
                    if (movie.availableTimes.size() >= 3)
                        break;
                    std::cout << "Enter a new time: ";
                    std::getline(std::cin, input);
                    std::cout << '\n'; // Add a space

                    if (input == "abort") {
                        std::cout << "Movie modification canceled.\n";
                        return;
                    }

                    if (isValidTimeFormat(input)) { // Check if the time format is valid
                        // Check if the time already exists in the vector
                        if (input[0] != '0')
                            input.insert(0, "0");
                        if (std::find(movie.availableTimes.begin(), movie.availableTimes.end(), input) != movie.availableTimes.end()) {
                            std::cout << RED_COLOR << "Time already exists!" << RESET_COLOR << "\n";
                        } else {
                            movie.availableTimes.push_back(input); // Add the new time to the vector
                            std::cout << GREEN_COLOR << "Time added successfully!" << RESET_COLOR << "\n";

                            // Display the added time and its index
                            int addedIndex = movie.availableTimes.size();
                            std::cout << "Added time: " << movie.availableTimes[addedIndex - 1] << ", Index: " << addedIndex << std::endl;
                        }
                    } else {
                        std::cout << RED_COLOR << "Invalid time format! Use 'hh:mmAM' or 'hh:mmPM'." << RESET_COLOR << "\n";
                    }
                } else if (input == "S") { // If the user chooses to save the changes
                    std::cout << "Saving modified data...\n";
                    saveDataToFile(); // Save the modified data to the file
                    std::cout << GREEN_COLOR << "Data saved successfully!" << RESET_COLOR << "\n";
                    break; // Exit the inner loop and proceed to the next iteration
                } else if (std::isdigit(input[0])) { // If the user selects a specific time
                    int index = std::stoi(input) - 1;
                    if (index >= 0 && static_cast<size_t>(index) < movie.availableTimes.size()) {
                        std::string selectedTime = movie.availableTimes[index];
                        std::cout << "Selected time: " << selectedTime << std::endl;

                        std::cout << "Choose an action (A: modify, B: delete): ";
                        std::getline(std::cin, input);
                        std::cout << '\n'; // Add a space

                        if (input == "abort") {
                            std::cout << "Movie modification canceled.\n";
                            return;
                        }

                        if (input == "A") { // If the user chooses to modify the selected time
                            std::cout << "Enter a new time: ";
                            std::getline(std::cin, input);
                            std::cout << '\n'; // Add a space

                            if (input == "abort") {
                                std::cout << "Movie modification canceled.\n";
                                return;
                            }

                            if (isValidTimeFormat(input)) { // Check if the time format is valid
                                if (input[0] != '0')
                                    input.insert(0, "0");
                                // Check if the time already exists in the vector
                                if (std::find(movie.availableTimes.begin(), movie.availableTimes.end(), input) != movie.availableTimes.end()) {
                                    std::cout << RED_COLOR << "Time already exists!" << RESET_COLOR << "\n";
                                } else {
                                    movie.availableTimes[index] = input;
                                    std::cout << GREEN_COLOR << "Time modified!" << RESET_COLOR << "\n";
                                }
                            } else {
                                std::cout << RED_COLOR << "Invalid time format! Use 'hh:mmAM' or 'hh:mmPM'." << RESET_COLOR << "\n";
                            }
                        } else if (input == "B") { // If the user chooses to delete the selected time
                            movie.availableTimes.erase(movie.availableTimes.begin() + index); // Delete the selected time
                            std::cout << GREEN_COLOR << "Time deleted successfully!" << RESET_COLOR << "\n";
                        } else {
                            std::cout << RED_COLOR << "Invalid action! Choose 'A' to modify or 'B' to delete." << RESET_COLOR << "\n";
                        }
                    } else {
                        std::cout << RED_COLOR << "Invalid index! Please enter a valid index." << RESET_COLOR << "\n";
                    }
                } else {
                    std::cout << RED_COLOR << "Invalid input! Please enter a valid index or 'A'." << RESET_COLOR << "\n";
                }
                system("pause");
            }

            while (true) {
                std::cout << "Modify another aspect of the movie? (yes/no): ";
                std::getline(std::cin, input);
                std::cout << '\n'; // Add a space

                if (input == "yes") {
                    break;
                } else if (input == "no") {
                    std::cout << "Movie modification completed.\n";
                    saveDataToFile(); // Save the modified data to the file
                    return;
                } else {
                    std::cout << RED_COLOR << "Invalid input! Enter 'yes' or 'no'." << RESET_COLOR << "\n";
                }
            }
        } else if (input == "6") { // If the user chooses to reset all seats for the movie
            clearScreen();
            std::string reset = "";
            while (true) {
                std::cout << "Reset all seats for movie " << movie.title << "? (yes/no):";
                std::getline(std::cin, reset);
                if (reset == "yes") {
                    movies[movie.title].seatAvailability.clear(); // Clear the seat availability for the movie
                    for (User& user : users) {
                        if (user.movieTitle == movie.title)
                            user.seat = ""; // Reset the seat for users associated with the movie
                    }
                    saveDataToFile(); // Save the modified data to the file
                    break;
                } else if (reset == "no") {
                    break;
                } else {
                    std::cout << RED_COLOR << "Invalid input!" << RESET_COLOR << "\n";
                }
            }
        }
    }
}



void deleteMovie() {
    loadDataFromFile(); // Load data from file

    clearScreen();
    std::cout << RED_COLOR << "Delete a movie" << RESET_COLOR << "\n\n";
    std::cout << "Enter 'abort' at any time to cancel.\n\n";

    while (true) {
        std::vector<std::string> movieTitles;
        for (const auto& movie : movies) {
            movieTitles.push_back(movie.first);
        }

        std::sort(movieTitles.begin(), movieTitles.end()); // Sort movie titles in alphabetical order
        std::cout << "Movie List:\n";
        for (size_t i = 0; i < movieTitles.size(); ++i) {
            std::cout << GREEN_COLOR << "[" << (i + 1) << "] " << RESET_COLOR << movieTitles[i] << "\n";
        }

        std::string movieIndexStr;
        std::cout << "\nEnter the index of the movie to delete: ";
        std::getline(std::cin, movieIndexStr);

        if (movieIndexStr == "abort") {
            std::cout << YELLOW_COLOR << "Movie deletion aborted." << RESET_COLOR << "\n";
            return;
        }

        int movieIndex = 0;
        try {
            movieIndex = std::stoi(movieIndexStr); // Convert movie index string to integer
        } catch (const std::invalid_argument& e) {
            std::cout << RED_COLOR << "Invalid movie index! Please enter a valid integer." << RESET_COLOR << "\n";
            continue;
        } catch (const std::out_of_range& e) {
            std::cout << RED_COLOR << "Invalid movie index! The entered value is out of range." << RESET_COLOR << "\n";
            continue;
        }

        if (movieIndex < 1 || movieIndex > static_cast<int>(movieTitles.size())) {
            std::cout << RED_COLOR << "Invalid movie index!" << RESET_COLOR << "\n";
            continue;
        }

        const std::string& movieTitle = movieTitles[movieIndex - 1]; // Get the selected movie title

        auto iter = movies.find(movieTitle);
        if (iter == movies.end()) {
            std::cout << RED_COLOR << "Movie title not found!" << RESET_COLOR << "\n";
            continue;
        }

        std::string confirm;
        while (true) {
            std::cout << "Are you sure you want to delete the movie '" << BLUE_COLOR << movieTitle << RESET_COLOR << "'? (yes/no): ";
            std::getline(std::cin, confirm);

            if (confirm == "yes") {
                std::vector<std::string> usersToDelete;
                for (const auto& user : users) {
                    if (user.movieTitle == movieTitle) {
                        usersToDelete.push_back(user.name); // Collect the usernames associated with the movie to delete
                    }
                }

                for (const auto& username : usersToDelete) {
                    auto userIter = users.begin();
                    while (userIter != users.end()) {
                        if (userIter->name == username) {
                            userIter = users.erase(userIter); // Delete users associated with the movie from the users vector
                        } else {
                            ++userIter;
                        }
                    }
                }

                movies.erase(iter); // Erase the movie from the movies map
                saveDataToFile(); // Save the modified data to the file
                loadDataFromFile(); // Load the updated data from the file

                std::cout << GREEN_COLOR << "Movie and associated user bookings deleted successfully!" << RESET_COLOR << "\n";
                break;
            } else if (confirm == "no") {
                std::cout << YELLOW_COLOR << "Movie deletion canceled." << RESET_COLOR << "\n";
                break;
            } else {
                std::cout << RED_COLOR << "Invalid choice! Please enter 'yes' or 'no'." << RESET_COLOR << "\n";
                continue;
            }
        }

        std::string deleteMore;
        while (true) {
            std::cout << "\nDo you want to delete more movies? (yes/no): ";
            std::getline(std::cin, deleteMore);

            if (deleteMore == "yes") {
                break;
            } else if (deleteMore == "no") {
                std::cout << "Exiting delete movie mode.\n";
                return;
            } else {
                std::cout << RED_COLOR << "Invalid choice! Please enter 'yes' or 'no'." << RESET_COLOR << "\n";
                continue;
            }
        }
    }
}



void viewMovieInfo() {
    loadDataFromFile(); // Load data from file
    clearScreen();
    std::cout << YELLOW_COLOR << "View movie information:\n\n" << RESET_COLOR;

    if (movies.empty()) {
        std::cout << "No movies available.\n";
    } else {
        std::vector<std::string> movieTitles;

        // Extract movie titles from the map
        for (const auto& movie : movies) {
            movieTitles.push_back(movie.first);
        }

        // Sort movie titles alphabetically
        std::sort(movieTitles.begin(), movieTitles.end());

        // Calculate the maximum lengths for other fields
        size_t maxTitleLength = 0;
        size_t maxPriceLength = 0;
        size_t maxCinemaLength = 0;

        for (const auto& title : movieTitles) {
            const Movie& movie = movies[title];
            maxTitleLength = std::max(maxTitleLength, movie.title.length());
            maxPriceLength = std::max(maxPriceLength, std::to_string(movie.price).length());
            maxCinemaLength = std::max(maxCinemaLength, movie.cinema.length());
        }

        // Display movie information
        for (const auto& title : movieTitles) {
            const Movie& movie = movies[title];

            std::cout << "Movie Title: " << std::left << std::setw(maxTitleLength) << movie.title << "\n";
            std::cout << "Price: " << std::left << std::setw(maxPriceLength) << movie.price << "\n";
            std::cout << "Duration: " << movie.duration << "\n";
            std::cout << "Cinema: " << std::left << std::setw(maxCinemaLength) << movie.cinema << "\n";
            std::cout << "Available Times: ";
            for (const auto& time : movie.availableTimes) {
                std::cout << time << " ";
            }
            std::cout << "\n";

            // Display partition line
            std::cout << BLUE_COLOR << std::string(79, '-') << RESET_COLOR << "\n";
        }
    }

    // Prompt user for input
    std::cout << "Enter 'Y' to proceed to the menu or any other key to remain in movie information: ";
    std::string choice;
    std::getline(std::cin, choice);

    if (choice.size() == 1 && (std::toupper(choice[0]) == 'Y')) {
        // Proceed to the menu
    } else {
        viewMovieInfo(); // Call the function recursively to remain in movie information
    }
}

