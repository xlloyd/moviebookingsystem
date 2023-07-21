#include "user.h"

const std::string RESET_COLOR = "\033[0m";    // Reset color code for console
const std::string RED_COLOR = "\033[31m";     // Red color code for console
const std::string GREEN_COLOR = "\033[32m";   // Green color code for console
const std::string YELLOW_COLOR = "\033[33m";  // Yellow color code for console
const std::string BLUE_COLOR = "\033[34m";    // Blue color code for console

void showUserConsole() {
    std::cout << GREEN_COLOR << "User Console" << RESET_COLOR << "\n";      // Display "User Console" in green color
    std::cout << "------------\n\n";                                         // Display a separator
    clearScreen();

    while (true) {
        std::cout << YELLOW_COLOR << "HELLO PLEASE CHOOSE" << RESET_COLOR << "\n";   // Display "HELLO PLEASE CHOOSE" in yellow color
        std::cout << "1. " << "Book a movie"<< "\n";                                  // Display option 1: "Book a movie"
        std::cout << "2. " << "Exit" << "\n";                                         // Display option 2: "Exit"
        std::cout << "Enter your choice (1-2): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                std::cout << "Book a movie\n";                // Perform actions for option 1: "Book a movie"
                bookMovie();
                break;
            case 2:
                std::cout << "Exiting User Console...\n";      // Perform actions for option 2: "Exit"
                return;
            default:
                std::cout << RED_COLOR << "Invalid choice!" << RESET_COLOR << "\n";    // Display error message for invalid choices
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }
}

void displaySeats(const std::vector<User>& users) {
    const int numRows = 6;   // Number of rows (A to F)
    const int numCols = 20;  // Number of columns (1 to 20)

    // Create a matrix to represent the seats
    std::vector<std::vector<std::string>> seatMatrix(numRows, std::vector<std::string>(numCols, " "));

    // Update the matrix with booked seats
    for (const User& user : users) {
        if (user.seat.empty()) continue;   // Skip if the user doesn't have a booked seat
        char row = user.seat[0];
        int col = std::stoi(user.seat.substr(1)) - 1;

        int rowIndex = row - 'A';
        seatMatrix[rowIndex][col] = "X";
    }

    // Display the screen and seat matrix
    std::cout << std::string(110, '=') << "\n";
    std::cout << "                                           " << YELLOW_COLOR << "Screen" << RESET_COLOR << "\n";
    std::cout << std::string(110, '=') << "\n";
    std::cout << "                                           \n";
    std::cout << "                                           \n";
    std::cout << "                                           \n";

    std::cout << "     ";
    for (int col = 1; col <= numCols; ++col) {
        std::cout << "[" << std::setw(3) << col << "]";
    }
    std::cout << "\n";

    for (int row = 0; row < numRows; ++row) {
        char rowLabel = 'A' + row;
        std::cout << "[" << rowLabel << "]: ";
        for (int col = 0; col < numCols; ++col) {
            std::cout << "[" << (seatMatrix[row][col] == "X" ? RED_COLOR : GREEN_COLOR) << std::setw(3) << seatMatrix[row][col] << RESET_COLOR << "]";
        }
        std::cout << "\n";
    }
}

void bookMovie() {
    loadDataFromFile();
    clearScreen();

    std::cout << "Available Movies:\n";
    std::cout << "'abort' to cancel\n";
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
        std::cout << RED_COLOR << "Movie title not found!" << RESET_COLOR << "\n";
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
            std::cout << RED_COLOR << "Invalid full name! Please enter a valid full name." << RESET_COLOR << "\n";
        } else if (isDuplicateFullName(user.name)) {
            std::cout << RED_COLOR << "Name already exists! Please enter a different name." << RESET_COLOR << "\n";
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
            std::cout << RED_COLOR << "Invalid phone number! Please enter a valid 11-digit phone number." << RESET_COLOR << "\n";
        } else if (isDuplicatePhoneNumber(user.phoneNumber)) {
            std::cout << RED_COLOR << "Phone number already exists! Please enter a different phone number." << RESET_COLOR << "\n";
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
            std::cout << RED_COLOR << "Invalid email address! Please enter a valid email address." << RESET_COLOR << "\n";
        } else if (isDuplicateEmailAddress(user.emailAddress)) {
            std::cout << RED_COLOR << "Email address already exists! Please enter a different email address." << RESET_COLOR << "\n";
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
                std::cout << RED_COLOR << "Invalid index! Please enter a valid index." << RESET_COLOR << "\n";
                continue;
            }
        } else {
            std::cout << RED_COLOR << "Invalid input! Please enter a valid index." << RESET_COLOR << "\n";
            continue;
        }
    }

    clearScreen();

    while (true) {
        displaySeats(users);    // Display the seat matrix

        std::cout << "Enter the seat number (e.g., A1): ";
        std::string seat;
        std::getline(std::cin, seat);

        if (seat == "abort") {
            std::cout << "Booking process canceled.\n";
            return;
        }

        if (!isValidSeat(seat)) {
            std::cout << RED_COLOR << "Invalid seat number! Please enter a valid seat number (e.g., A1)." << RESET_COLOR << "\n";
            continue;
        }

        if (isSeatBooked(seat, users)) {
            std::cout << RED_COLOR << "Seat already booked! Please select a different seat." << RESET_COLOR << "\n";
            continue;
        }

        // Book the seat
        user.seat = seat;
        user.movieTitle = movie->title;    // Assign the movie title to the user
        users.push_back(user);

        std::cout << GREEN_COLOR << "Seat " << seat << " booked successfully." << RESET_COLOR << "\n";

        saveDataToFile();

        loadDataFromFile();

        return;
        clearScreen();
    }
}
