#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <unordered_set>
#include <iomanip>
#include <regex>

struct Movie {
    std::string title;
    double price;
    std::string duration;
    std::vector<std::string> availableTimes;
    std::string cinema; // Add cinema member
    std::vector<std::vector<bool>> seatingPlan;
    int bookedSeatsCount; // New member variable for tracking booked seats

     // Default constructor
    Movie() : price(0), duration(""), bookedSeatsCount(0) {}

    // Parameterized constructor
    Movie(const std::string& t, float p, const std::string& d, const std::vector<std::string>& at, const std::vector<std::vector<bool>>& sp)
        : title(t), price(p), duration(d), availableTimes(at), seatingPlan(sp), bookedSeatsCount(0) {}
};


struct Seat {
    bool isAvailable;
    std::string code;
};

struct Client {
    std::string name;
    std::string phoneNumber;
    std::string emailAddress;
    std::string movieTitle;
    std::vector<std::string> bookedSeats;
    std::string availableTime;
};

std::unordered_map<std::string, Movie> movies;
std::vector<Client> clients;

void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
    std::cout << std::flush;
}



void showAdminConsole();
void showUserConsole();
void bookMovie();
void uploadMovie();
void viewClients();
void modifyClient();
void deleteClient();
void saveDataToFile();
void loadDataFromFile();
void modifyMovieInfo();
void viewMovieInfo();
void deleteMovie();



bool isValidTimeFormat(const std::string& time) {
    // Check if the time has the format 'hh:mmAM' or 'hh:mmPM'
    // You can implement your own validation logic here
    return true;
}
bool isValidDurationFormat(const std::string& duration) {
    // Check if the duration has the format 'hh:mm:ss'
    if (duration.length() != 8) {
        return false;
    }

    if (!isdigit(duration[0]) || !isdigit(duration[1]) || duration[2] != ':' ||
        !isdigit(duration[3]) || !isdigit(duration[4]) || duration[5] != ':' ||
        !isdigit(duration[6]) || !isdigit(duration[7])) {
        return false;
    }

    int hour = std::stoi(duration.substr(0, 2));
    int minute = std::stoi(duration.substr(3, 2));
    int second = std::stoi(duration.substr(6, 2));

    // Check if the hour is within the range of 0-23, minute is within the range of 0-59, and second is within the range of 0-59
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return false;
    }

    return true;
}


bool isValidFullName(const std::string& name) {
    return !name.empty();
}

bool isDuplicateFullName(const std::string& name) {
    for (const auto& client : clients) {
        if (client.name == name) {
            return true;
        }
    }
    return false;
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
    return phoneNumber.length() == 11;
}

bool isDuplicatePhoneNumber(const std::string& phoneNumber) {
    for (const auto& client : clients) {
        if (client.phoneNumber == phoneNumber) {
            return true;
        }
    }
    return false;
}

bool isValidEmailAddress(const std::string& emailAddress) {
    return true;
}

bool isDuplicateEmailAddress(const std::string& emailAddress) {
    for (const auto& client : clients) {
        if (client.emailAddress == emailAddress) {
            return true;
        }
    }
    return false;
}

bool isMovieTitleExists(const std::string& movieTitle) {
    return movies.find(movieTitle) != movies.end();
}

std::vector<std::string> parseSeats(const std::string& seatsStr) {
    // Implementation for parsing seat codes
    // ...
    std::vector<std::string> seats;
    // Parse seat codes and add them to the seats vector
    // ...
    return seats;
}

int getRowNumber(const std::string& rowNumber) {
    // Implementation for converting rowNumber to integer
    // ...
    return 0; // Replace 0 with the actual row number
}

int getCinemaCodeIndex(const std::string& cinemaCode) {
    // Implementation for converting cinemaCode to index
    // ...
    return 0; // Replace 0 with the actual index
}

bool areSeatsAvailable(const std::vector<std::vector<bool>>& seatingPlan, const std::vector<std::string>& seats) {
    for (const auto& seat : seats) {
        std::string cinemaCode, rowNumber;
        // Parse the seat code to extract cinemaCode and rowNumber
        // ...
        int row = getRowNumber(rowNumber);
        int col = getCinemaCodeIndex(cinemaCode);
        if (row >= 0 && row < seatingPlan.size() && col >= 0 && col < seatingPlan[row].size()) {
            if (!seatingPlan[row][col]) {
                return false;  // Seat is not available
            }
        } else {
            return false;  // Seat code is invalid
        }
    }
    return true;  // All seats are available
}

bool isValidPrice(const std::string& price) {
    // Implement your validation logic here
    return true;
}

bool isValidDuration(const std::string& duration) {
    // Implement your validation logic here
    return true;
}

bool isValidAvailableTime(const std::string& time) {
    // Implement your validation logic here
    return true;
}

bool areSeatsValidFormat(const std::vector<std::string>& seats) {
    for (const auto& seat : seats) {
        // Check if the seat matches the expected format "CinemaCode-RowNumber"
        if (seat.length() != 3 || seat[1] != '-' ||
            (seat[0] < 'A' || seat[0] > 'F') ||
            (seat[2] < '1' || seat[2] > '9')) {
            return false;
        }
    }
    return true;
}

bool areSeatsAvailable(const std::vector<std::string>& availableTimes, const std::vector<std::string>& seats) {
    std::unordered_set<std::string> availableSeats(availableTimes.begin(), availableTimes.end());

    for (const auto& seat : seats) {
        if (availableSeats.find(seat) == availableSeats.end()) {
            return false; // Seat is not available
        }
    }

    return true; // All seats are available
}

bool areSeatsUnoccupied(const std::string& movieTitle, const std::vector<std::string>& seats) {
    for (const auto& client : clients) {
        if (client.movieTitle == movieTitle) {
            for (const auto& bookedSeat : client.bookedSeats) {
                for (const auto& seat : seats) {
                    if (bookedSeat == seat) {
                        return false; // Seat is already booked
                    }
                }
            }
        }
    }
    return true; // Seats are unoccupied
}

bool isTimeAvailable(const std::vector<std::string>& availableTimes, const std::string& time) {
    for (const auto& availableTime : availableTimes) {
        if (availableTime == time) {
            return true; // Time is available
        }
    }
    return false; // Time is not available
}
void showAdminConsole() {
    std::string password = "jeroeinmagno";
    std::string inputPassword;

    clearScreen();

    std::cout << "Admin Console\n";
    std::cout << "-------------\n\n";

    int attempts = 3;
    bool authenticated = false;

    while (attempts > 0) {
        clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Enter password (Attempts left: " << attempts << "): ";

        // Masking the password input
        char c;
        while ((c = _getch()) != '\r') { // Read characters until Enter (Return) key is pressed
            if (c == '\b') { // Handle backspace
                if (!inputPassword.empty()) {
                    inputPassword.pop_back();
                    std::cout << "\b \b"; // Move cursor back, print a space, move cursor back again
                }
            } else {
                inputPassword += c;
                std::cout << '*'; // Print asterisk for each character
            }
        }

        if (inputPassword == password) {
            authenticated = true;
            break;
        } else {
            std::cout << "\nIncorrect password!\n";
            inputPassword = "";
            --attempts;

        }
    }

    if (authenticated) {

        clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Authentication successful!\n";

        clearScreen();

    } else {

    clearScreen();

        std::cout << "Admin Console\n";
        std::cout << "-------------\n\n";
        std::cout << "Maximum attempts exceeded. returning to main menu\n";

        return;
    }





    while (true) {
        std::cout << "Admin Console\n";
        std::cout << "1. Upload a movie\n";
        std::cout << "2. View clients booked movie\n";
        std::cout << "3. Modify a client's booked movie\n";
        std::cout << "4. Delete a client's booked movie\n";
        std::cout << "5. Modify movie information\n";
        std::cout << "6. View movies info\n";
        std::cout << "7. delete a movie\n";
        std::cout << "8. Exit\n";

        std::cout << "Enter your choice (1-8): ";
        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

       switch (choice) {
    case 1:
        std::cout << "Upload a movie\n";
        uploadMovie();
        break;
    case 2:
        std::cout << "View clients booked movie\n";
        viewClients();
        break;
    case 3:
        std::cout << "Modify a client's booked movie\n";
        modifyClient();
        break;
    case 4:
        std::cout << "Delete a client's booked movie\n";
        deleteClient();
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
        // Exit
        return;
    default:
        std::cout << "Invalid choice!\n";
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
    std::cout << "Upload a movie\n";

    while (true) {
        std::cout << "Movie title ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        if (input.empty()) {
            std::cout << "Invalid movie title!\n";
        } else {
            movie.title = input;
            break;
        }
    }

    while (true) {
        std::cout << "Price ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> movie.price && movie.price > 0.0) {
            break;
        } else {
            std::cout << "Invalid price!\n";
        }
    }

    while (true) {
        std::cout << "Duration (hh:mm:ss) ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        if (isValidDurationFormat(input)) {
            movie.duration = input;
            break;
        } else {
            std::cout << "Invalid duration! Use the format 'hh:mm:ss'.\n";
        }
    }

    while (true) {
        std::cout << "Choose a cinema to put the movie:\n";
        std::cout << "1. Cinema 1\n";
        std::cout << "2. Cinema 2\n";
        std::cout << "3. Cinema 3\n";
        std::cout << "('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

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
            std::cout << "Invalid cinema choice! Please enter a number from the list.\n";
        }
    }

    while (true) {
        std::cout << "Available time (hh:mmAM/PM) ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie upload canceled.\n";
            return;
        }

        std::string hourStr, minuteStr, meridiem;
        std::regex timeRegex(R"((\d{1,2}):(\d{2})(AM|PM))", std::regex_constants::icase);
        std::smatch timeMatch;

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

                while (true) {
                    std::cout << "Add more available times? (yes/no/abort): ";
                    std::getline(std::cin, input);

                    if (input == "yes") {
                        std::cout << "Available time (hh:mmAM/PM): ";
                        std::getline(std::cin, input);

                        if (input == "abort") {
                            std::cout << "Movie upload canceled.\n";
                            return;
                        }

                        std::regex timeRegex(R"((\d{1,2}):(\d{2})(AM|PM))", std::regex_constants::icase);
                        std::smatch timeMatch;

                        if (std::regex_match(input, timeMatch, timeRegex)) {
                            hourStr = timeMatch[1].str();
                            minuteStr = timeMatch[2].str();
                            meridiem = timeMatch[3].str();

                            hour = std::stoi(hourStr);
                            minute = std::stoi(minuteStr);

                            if ((hour >= 1 && hour <= 12) && (minute >= 0 && minute <= 59)) {
                                formattedTime.str("");
                                formattedTime << std::setw(2) << std::setfill('0') << hourStr << ":" << std::setw(2) << std::setfill('0') << minuteStr << meridiem;
                                movie.availableTimes.push_back(formattedTime.str());
                            } else {
                                std::cout << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format.\n";
                            }
                        } else {
                            std::cout << "Invalid time format! Please use the 'hh:mmAM/PM' format.\n";
                        }
                    } else if (input == "no") {
                        movies[movie.title] = movie; // Add the movie to the movies map
                        saveDataToFile();
                        std::cout << "Movie uploaded successfully!\n";
                        viewMovieInfo(); // Display movie information
                        return;
                    } else if (input == "abort") {
                        std::cout << "Movie upload canceled.\n";
                        return;
                    } else {
                        std::cout << "Invalid input! Enter 'yes', 'no', or 'abort'.\n";
                    }
                }
            } else {
                std::cout << "Invalid time! Please enter a valid time in 'hh:mmAM/PM' format.\n";
            }
        } else {
            std::cout << "Invalid time format! Please use the 'hh:mmAM/PM' format.\n";
        }
    }

    movies[movie.title] = movie; // Add the movie to the movies map

    std::cout << "Movie uploaded successfully!\n";
    viewMovieInfo(); // Display movie information
}





void viewClients() {
    clearScreen();
    std::cout << "View clients booked movie\n";

    // Sort clients by name in ascending order
    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    // Display client information
    for (const auto& client : clients) {
        if (!client.movieTitle.empty()) {  // Only display if movie title is not empty
            std::cout << "Name: " << client.name << "\n";
            std::cout << "Phone Number: " << client.phoneNumber << "\n";
            std::cout << "Email Address: " << client.emailAddress << "\n";
            std::cout << "Movie Title: " << client.movieTitle << "\n";

            // Display booked seats
            if (!client.bookedSeats.empty()) {
                std::cout << "Booked Seats: ";
                for (const auto& seat : client.bookedSeats) {
                    std::cout << seat << " ";
                }
                std::cout << "\n";
            }

            // Display available time
            if (!client.availableTime.empty()) {
                std::cout << "Available Time: " << client.availableTime << "\n";
            }

            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
}




void modifyClient() {
    clearScreen();
    std::cout << "Modify a client's booked movie\n";

    // Sort clients by name in ascending order
    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    // Display client names
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << i + 1 << ". " << clients[i].name << "\n";
    }

    std::string indexStr;
    size_t index;
    std::cout << "Enter the index number of the client to modify (or enter 'abort' to cancel): ";
    std::getline(std::cin, indexStr);

    if (indexStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }

    std::stringstream(indexStr) >> index;

    if (index <= 0 || index > clients.size()) {
        std::cout << "Invalid index number!\n";
        return;
    }

    Client& client = clients[index - 1];

    std::cout << "Select the action to modify:\n";
    std::cout << "1. Name\n";
    std::cout << "2. Phone number\n";
    std::cout << "3. Email address\n";
    std::cout << "4. Movie title\n";
    std::cout << "5. Seats\n";
    std::cout << "6. Available time\n";
    std::cout << "Enter the action number (or enter 'abort' to cancel): ";

    std::string actionStr;
    std::getline(std::cin, actionStr);

    if (actionStr == "abort") {
        std::cout << "Modification process aborted.\n";
        return;
    }

    int action;
    std::stringstream(actionStr) >> action;

    switch (action) {
        case 1: {
            std::string newName;
            std::cout << "Name (" << client.name << " or enter 'skip' to remain the information): ";
            std::getline(std::cin, newName);
            if (newName == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newName != "skip") {
                // Validate and update name
                if (!isValidFullName(newName)) {
                    std::cout << "Invalid full name! Please enter a valid full name.\n";
                    return;
                } else if (isDuplicateFullName(newName)) {
                    std::cout << "Name already exists! Please enter a different name.\n";
                    return;
                }
                client.name = newName;
            }
            break;
        }
        case 2: {
            std::string newPhoneNumber;
            std::cout << "Phone number (" << client.phoneNumber << " or enter 'skip' to remain the information): ";
            std::getline(std::cin, newPhoneNumber);
            if (newPhoneNumber == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newPhoneNumber != "skip") {
                // Validate and update phone number
                if (!isValidPhoneNumber(newPhoneNumber)) {
                    std::cout << "Invalid phone number! Please enter a valid 11-digit phone number.\n";
                    return;
                } else if (isDuplicatePhoneNumber(newPhoneNumber)) {
                    std::cout << "Phone number already exists! Please enter a different phone number.\n";
                    return;
                }
                client.phoneNumber = newPhoneNumber;
            }
            break;
        }
        case 3: {
            std::string newEmailAddress;
            std::cout << "Email address (" << client.emailAddress << " or enter 'skip' to remain the information): ";
            std::getline(std::cin, newEmailAddress);
            if (newEmailAddress == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newEmailAddress != "skip") {
                // Validate and update email address
                if (!isValidEmailAddress(newEmailAddress)) {
                    std::cout << "Invalid email address! Please enter a valid email address.\n";
                    return;
                } else if (isDuplicateEmailAddress(newEmailAddress)) {
                    std::cout << "Email address already exists! Please enter a different email address.\n";
                    return;
                }
                client.emailAddress = newEmailAddress;
            }
            break;
        }
        case 4: {
            std::string newMovieTitle;
            std::cout << "Movie title (" << client.movieTitle << " or enter 'skip' to remain the information): ";
            std::getline(std::cin, newMovieTitle);
            if (newMovieTitle == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newMovieTitle != "skip") {
                // Validate and update movie title
                if (!isMovieTitleExists(newMovieTitle)) {
                    std::cout << "Movie title not found! Please enter a valid movie title.\n";
                    return;
                }
                client.movieTitle = newMovieTitle;
            }
            break;
        }

    case 5: {
        std::string newSeats;
        std::cout << "Seats (" << client.bookedSeats.size() << " booked or enter 'skip' to remain the information): ";
        std::getline(std::cin, newSeats);
        if (newSeats == "abort") {
            std::cout << "Modification process aborted.\n";
            return;
        } else if (newSeats != "skip") {
            // Validate and update booked seats
            std::vector<std::string> newBookedSeats = parseSeats(newSeats);
            if (!areSeatsValidFormat(newBookedSeats)) {
                std::cout << "Invalid seat format! Please enter seats in the correct format.\n";
                return;
            }

            // Assign the movie based on the client's current movie title
            auto iter = movies.find(client.movieTitle);
            if (iter == movies.end()) {
                std::cout << "Movie title not found!\n";
                return;
            }
            Movie& movie = iter->second;

            if (!areSeatsAvailable(movie.availableTimes, newBookedSeats)) {
                std::cout << "Invalid seats or seats are not available! Please enter valid and available seats.\n";
                return;
            }
            client.bookedSeats = newBookedSeats;
        }
        break;
    }
        case 6: {
            std::string newTime;
            std::cout << "Available time (" << client.availableTime << " or enter 'skip' to remain the information): ";
            std::getline(std::cin, newTime);
            if (newTime == "abort") {
                std::cout << "Modification process aborted.\n";
                return;
            } else if (newTime != "skip") {
                // Validate and update available time
                if (!isValidTimeFormat(newTime)) {
                    std::cout << "Invalid time format! Please use the format 'hh:mmAM' or 'hh:mmPM'.\n";
                    return;
                }
                client.availableTime = newTime;
            }
            break;
        }
        default:
            std::cout << "Invalid action number!\n";
            return;
    }

    saveDataToFile();

    std::cout << "Client information modified successfully!\n";
    viewClients();
}

void modifyMovieInfo() {
    clearScreen();

    std::cout << "Modify movie information\n";

    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    if (movieTitles.empty()) {
        std::cout << "No movies available to modify.\n";
        std::cout << "Press Enter to exit...";
        std::cin.ignore();
        return;
    }

    // Display available movie titles
    std::cout << "Available movie titles:\n";
    std::cout << "----------------------\n";
    for (size_t i = 0; i < movieTitles.size(); ++i) {
        std::cout << i + 1 << ". " << movieTitles[i] << "\n";
    }
    std::cout << "----------------------\n";

    std::string input;
    int selectedIndex = -1;
    while (true) {
        std::cout << "Select the index of the movie to modify (1-" << movieTitles.size() << ") ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> selectedIndex && selectedIndex >= 1 && selectedIndex <= movieTitles.size()) {
            break;
        } else {
            std::cout << "Invalid index!\n";
        }
    }

    std::string movieTitle = movieTitles[selectedIndex - 1];
    Movie& movie = movies[movieTitle];

    while (true) {
        std::cout << "Movie title (" << movie.title << ") ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (input.empty()) {
            std::cout << "Invalid movie title!\n";
        } else {
            movie.title = input;
            break;
        }
    }

    while (true) {
        std::cout << "Price (" << movie.price << ") ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        std::stringstream ss(input);
        if (ss >> movie.price && movie.price > 0.0) {
            break;
        } else {
            std::cout << "Invalid price!\n";
        }
    }

    while (true) {
        std::cout << "Duration (hh:mm:ss) ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (isValidDurationFormat(input)) {
            movie.duration = input;
            break;
        } else {
            std::cout << "Invalid duration! Use the format 'hh:mm:ss'.\n";
        }
    }

    while (true) {
        std::cout << "Available time (hh:mmAM/PM, between 8:00AM and 11:00PM) ('abort' to cancel): ";
        std::getline(std::cin, input);

        if (input == "abort") {
            std::cout << "Movie modification canceled.\n";
            return;
        }

        if (isValidTimeFormat(input)) {
            std::string hourStr = input.substr(0, 2);
            std::string minuteStr = input.substr(3, 2);
            int hour = std::stoi(hourStr);
            int minute = std::stoi(minuteStr);

            if ((hour >= 8 && hour <= 11) || (hour == 12 && minute == 0)) {
                movie.availableTimes.push_back(input);

                while (true) {
                    std::cout << "Add more available times? (yes/no/abort): ";
                    std::getline(std::cin, input);

                    if (input == "yes") {
                        break;
                    } else if (input == "no") {
                        saveDataToFile();
                        std::cout << "Movie information modified successfully!\n";
                        return;
                    } else if (input == "abort") {
                        std::cout << "Movie modification canceled.\n";
                        return;
                    } else {
                        std::cout << "Invalid input! Enter 'yes', 'no', or 'abort'.\n";
                    }
                }
            } else {
                std::cout << "Invalid time! Must be between 8:00AM and 11:00PM.\n";
            }
        } else {
            std::cout << "Invalid time format! Use 'hh:mmAM' or 'hh:mmPM'.\n";
        }
    }
}



void viewMovieInfo() {
    clearScreen();
    std::cout << "View movie information:\n\n";

    if (movies.empty()) {
        std::cout << "No movies available.\n";
        std::cout << "Press Enter to exit...";
        std::cin.ignore();
        return;
    }

    // Sort movies by title in ascending order
    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    // Display movie information
    for (const auto& title : movieTitles) {
        const Movie& movie = movies[title];
        std::cout << "Movie Title: " << movie.title << "\n";
        std::cout << "Price: " << movie.price << "\n";
        std::cout << "Duration: " << movie.duration << "\n";
        std::cout << "Available Times: ";
        for (const auto& time : movie.availableTimes) {
            std::cout << time << " ";
        }
        std::cout << "\n";

        // Load the number of booked seats from the "1data.dat" file
        int bookedSeatsCount = 0;
        for (const auto& client : clients) {
            if (client.movieTitle == title) {
                bookedSeatsCount += client.bookedSeats.size();
            }
        }
        std::cout << "Booked Seats: " << bookedSeatsCount << "\n";

        std::cout << "-------------------------\n";
    }

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
}




void deleteClient() {
    clearScreen();
    std::cout << "Delete a client's booked movie\n";

    // Sort clients by name in ascending order
    std::sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.name < b.name;
    });

    // Filter out clients without a movie title
    std::vector<Client> bookedClients;
    for (const auto& client : clients) {
        if (!client.movieTitle.empty()) {
            bookedClients.push_back(client);
        }
    }

    // Display client names
    if (bookedClients.empty()) {
        std::cout << "No clients found.\n";
        return;
    }

    for (size_t i = 0; i < bookedClients.size(); ++i) {
        std::cout << i + 1 << ". " << bookedClients[i].name << "\n";
    }

    std::string indexStr;
    int index;
    std::cout << "Enter the index number of the client to delete: ";
    std::getline(std::cin, indexStr);

    try {
        index = std::stoi(indexStr);

        if (index <= 0 || index > static_cast<int>(bookedClients.size())) {
            throw std::out_of_range("Invalid index number!");
        }

        std::cout << "Are you sure you want to delete the client's information? (yes/no): ";
        std::string confirm;
        std::getline(std::cin, confirm);

        if (confirm == "yes") {
            // Find the corresponding client in the original vector
            size_t clientIndex = 0;
            for (size_t i = 0; i < clients.size(); ++i) {
                if (clients[i].name == bookedClients[index - 1].name) {
                    clientIndex = i;
                    break;
                }
            }

            clients.erase(clients.begin() + clientIndex);
            saveDataToFile();
            std::cout << "Client information deleted successfully!\n";
        } else {
            std::cout << "Deletion canceled.\n";
        }
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid index number! Please enter a valid index.\n";
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << "\n";
    }
}


void saveDataToFile() {
    std::ofstream outFile("1data.dat");
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
    }

    // Write client data
    outFile << clients.size() << "\n";
    for (const auto& client : clients) {
        outFile << client.name << "\n";
        outFile << client.phoneNumber << "\n";
        outFile << client.emailAddress << "\n";
        outFile << client.movieTitle << "\n";
        outFile << client.bookedSeats.size() << "\n";
        for (const auto& seat : client.bookedSeats) {
            outFile << seat << "\n";
        }
        outFile << client.availableTime << "\n";
    }

    outFile.close();
}



void loadDataFromFile() {
    std::ifstream inFile("1data.dat");
    if (!inFile.is_open()) {
        std::cout << "Failed to open data file for reading!\n";
        return;
    }

    movies.clear();
    clients.clear();

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
        movies[movie.title] = movie;
    }

    // Read client data
    int clientCount;
    inFile >> clientCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < clientCount; ++i) {
        Client client;
        std::getline(inFile, client.name);
        std::getline(inFile, client.phoneNumber);
        std::getline(inFile, client.emailAddress);
        std::getline(inFile, client.movieTitle);
        int seatCount;
        inFile >> seatCount;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int j = 0; j < seatCount; ++j) {
            std::string seat;
            std::getline(inFile, seat);
            client.bookedSeats.push_back(seat);
        }
        std::getline(inFile, client.availableTime);
        clients.push_back(client);
    }

    inFile.close();
}

void deleteMovie() {
    clearScreen();
    std::cout << "Delete a movie\n";

    std::string movieTitle;
    std::cout << "Enter the movie title to delete (or enter 'abort' to cancel): ";
    std::getline(std::cin, movieTitle);

    if (movieTitle == "abort") {
        std::cout << "Movie deletion aborted.\n";
        return;
    }

    auto iter = movies.find(movieTitle);
    if (iter == movies.end()) {
        std::cout << "Movie title not found!\n";
        return;
    }

    std::string confirm;
    while (true) {
        std::cout << "Are you sure you want to delete the movie? (yes/no/abort): ";
        std::getline(std::cin, confirm);

        if (confirm == "yes") {
            movies.erase(iter);
            saveDataToFile();

            std::cout << "Movie deleted successfully!\n";
            return;
        } else if (confirm == "no") {
            std::cout << "Movie deletion canceled.\n";
            return;
        } else if (confirm == "abort") {
            std::cout << "Movie deletion aborted.\n";
            return;
        } else {
            std::cout << "Invalid choice! Please enter 'yes', 'no', or 'abort'.\n";
        }
    }
}

void showUserConsole() {
    std::cout << "User Console\n";
    std::cout << "------------\n\n";
    clearScreen();
    while (true) {
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
    std::cout << "Available Movies:\n";
    std::cout << "-----------------\n\n";

    clearScreen();

    // Sort movies by title in ascending order
    std::vector<std::string> movieTitles;
    for (const auto& movie : movies) {
        movieTitles.push_back(movie.first);
    }
    std::sort(movieTitles.begin(), movieTitles.end());

    // Display available movies
    for (const auto& title : movieTitles) {
        const Movie& movie = movies[title];
        std::cout << "Title: " << movie.title << "\n";
        std::cout << "Price: " << movie.price << "\n";
        std::cout << "Duration: " << movie.duration << "\n";
        std::cout << "Available Times: ";
        for (const auto& time : movie.availableTimes) {
            std::cout << time << " ";
        }
        std::cout << "\n";
        std::cout << "-------------------------\n";
    }

    std::string movieTitle;
    std::cout << "Enter the movie title you want to book (or enter 'abort' to cancel): ";
    std::getline(std::cin, movieTitle);

    if (movieTitle == "abort") {
        std::cout << "Booking process canceled.\n";
        return;
    }

    auto iter = movies.find(movieTitle);
    if (iter == movies.end()) {
        std::cout << "Movie title not found!\n";
        return;
    }

    Movie& movie = iter->second;
    Client client;

    // Get client information
    while (true) {
        std::cout << "Enter your full name: ";
        std::getline(std::cin, client.name);

        if (!isValidFullName(client.name)) {
            std::cout << "Invalid full name! Please enter a valid full name.\n";
        } else if (isDuplicateFullName(client.name)) {
            std::cout << "Name already exists! Please enter a different name.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your phone number (11 digits): ";
        std::getline(std::cin, client.phoneNumber);

        if (!isValidPhoneNumber(client.phoneNumber)) {
            std::cout << "Invalid phone number! Please enter a valid 11-digit phone number.\n";
        } else if (isDuplicatePhoneNumber(client.phoneNumber)) {
            std::cout << "Phone number already exists! Please enter a different phone number.\n";
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter your email address: ";
        std::getline(std::cin, client.emailAddress);

        if (!isValidEmailAddress(client.emailAddress)) {
            std::cout << "Invalid email address! Please enter a valid email address.\n";
        } else if (isDuplicateEmailAddress(client.emailAddress)) {
            std::cout << "Email address already exists! Please enter a different email address.\n";
        } else {
            break;
        }
    }

    // Display available seats
    std::cout << "Available Seats:\n";
    std::cout << "-----------------\n\n";

    for (const auto& row : movie.seatingPlan) {
        for (const auto& seat : row) {
            if (seat) {
                std::cout << "XX ";
            } else {
                std::cout << seat << " ";
            }
        }
        std::cout << "\n";
    }

    // Select seats
    while (true) {
        std::cout << "Select seats (format: CinemaCode-RowNumber, e.g., A-1): ";
        std::string seatsStr;
        std::getline(std::cin, seatsStr);

        std::vector<std::string> seats = parseSeats(seatsStr);

        if (!areSeatsValidFormat(seats)) {
            std::cout << "Invalid seat format! Please enter seats in the correct format.\n";
        } else if (!areSeatsAvailable(movie.seatingPlan, seats)) {
            std::cout << "Invalid seats or seats are not available! Please enter valid and available seats.\n";
        } else if (!areSeatsUnoccupied(movieTitle, seats)) {
            std::cout << "Selected seats are already booked! Please choose different seats.\n";
        } else {
            client.bookedSeats = seats;
            break;
        }
    }

    // Select available time
    while (true) {
        std::cout << "Select available time: ";
        std::string time;
        std::getline(std::cin, time);

        if (!isTimeAvailable(movie.availableTimes, time)) {
            std::cout << "Invalid time or time is not available! Please enter a valid and available time.\n";
        } else {
            client.availableTime = time;
            break;
        }
    }

    // Save the booking
client.movieTitle = movieTitle;
clients.push_back(client);
saveDataToFile();

// Update the number of booked seats for the movie
movie.bookedSeatsCount += client.bookedSeats.size();

std::cout << "Movie booked successfully!\n";

    clearScreen();
}







int main() {
    loadDataFromFile();

    std::cout << "Welcome to the Movie Booking System!\n";

    while (true) {
        std::cout << "Please select an option:\n";
        std::cout << "1. Admin\n";
        std::cout << "2. User\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";

        std::string choiceStr;
        std::getline(std::cin, choiceStr);

        int choice;
        std::stringstream(choiceStr) >> choice;

        switch (choice) {
            case 1:
                // Admin console
                showAdminConsole();
                break;
            case 2:
                // User console
                showUserConsole();
                break;
            case 3:
                // Exit
                std::cout << "Exiting the Movie Booking System...\n";
                saveDataToFile();
                return 0;
            default:
                std::cout << "Invalid choice!\n";
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();

        clearScreen();
    }

    return 0;
}
