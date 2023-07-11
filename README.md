

## Movie Booking System

The Movie Booking System is a command-line application implemented in C++. It allows users to book movie tickets, view movie information, and manage user data. The program provides separate consoles for administrators and users, each with different functionalities.

This code uses the following data structures:

1. `std::unordered_map<std::string, Movie> movies`: This unordered map stores movies as key-value pairs, where the movie title is the key and the associated movie information is the value. It allows fast access to movie information based on the title.

2. `std::vector<User> users`: This vector stores user information. Each element in the vector represents a user and contains various attributes such as name, phone number, email address, movie title, available time, and cinema. The vector allows storing and accessing multiple user records.

Both data structures are used to store and manage movie and user data, respectively, throughout the program. The unordered map provides efficient lookup based on movie titles, while the vector allows storing and iterating over multiple user records.

### Features

- **Admin Console**: The Admin Console provides functionalities for administrators to perform various tasks:
  - Add new movies: Administrators can add new movies to the system by providing details such as movie title, price, duration, and available showtimes.
  - Delete movies: Administrators can delete movies from the system if they are no longer available.
  - Modify movie details: Administrators can modify the details of existing movies, such as title, price, duration, and available showtimes.
  - View movie information: Administrators can view detailed information about each movie, including its title, price, duration, available showtimes, and the number of booked seats.
  - View user information: Administrators can view information about the users who have booked movie tickets, including their names, phone numbers, email addresses, booked seats, and available showtimes.
  - Modify user details: Administrators can modify the details of users, such as their names, phone numbers, email addresses, booked seats, and available showtimes.
  - Delete user information: Administrators can delete user records from the system if necessary.

- **User Console**: The User Console allows users to book movie tickets:
  - View available movies: Users can view a list of available movies, including their titles, prices, durations, and available showtimes.
  - Book movie tickets: Users can select a movie from the available list and proceed to book tickets by providing their personal information, including their full name, phone number, email address, and selected seats.
  - Seat availability check: The system checks the availability of the selected seats and ensures they are not already booked.
  - Confirmation and saving: Once the user confirms the booking, the system saves the booking information and updates the availability of the selected seats.

### Key Components

The Movie Booking System code utilizes several important components:

- **Structs and Classes**: The code defines two main structures, `Movie` and `User`, to store movie and user information, respectively. The `Movie` struct includes attributes such as title, price, duration, available showtimes, and the number of booked seats. The `User` struct stores details about the user, including their name, phone number, email address, booked seats, and available showtimes.

- **Data Storage**: The movie data is stored using a `std::unordered_map` container, where the movie title serves as the key and the corresponding `Movie` struct is the value. This data structure allows for efficient lookup based on the movie title, enabling quick retrieval of movie information. The user data is stored in a `std::vector` of `User` structs, allowing for dynamic addition and removal of user records.

- **File I/O**: The code implements functions for reading movie and user data from a data file (`1data.dat`) and saving the data back to the file. The `loadDataFromFile()` function reads the data file and populates the movie and user data structures, while the `saveDataToFile()` function saves the updated data back to the file.

- **Input Validation**: To ensure data integrity and prevent inconsistencies, the code includes various input validation checks. It validates full names, phone numbers, email addresses, seat availability, and duplicate entries. These validations ensure that the data entered by users or administrators meets the required format and avoids conflicts with existing records.

- **Error Handling**: The program incorporates error handling techniques to handle invalid user input gracefully. It provides meaningful error messages to guide the user in correcting their input and prevents the program from crashing due to unexpected input.

- **Utility Functions**: The code includes several utility functions to perform common tasks. These functions include clearing the console screen, parsing seat information, and validating input formats. These utility functions help streamline the code and enhance its readability.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <unordered_set>
#include <iomanip>
#include <regex>
#include <string>

<iostream>: Used for input/output stream operations. It provides functionality for reading input from the user (std::cin) and displaying output to the console (std::cout).

<fstream>: Used for file stream operations. It allows reading from and writing to files (std::ifstream, std::ofstream).

<sstream>: Used for string stream operations. It provides functionality for reading from and writing to strings (std::stringstream).

<cstdlib>: Used for general-purpose functions. In your code, it is likely used for string conversions (std::stoi, std::stod) and generating random numbers (std::rand).

<unordered_map>: Used for storing key-value pairs in an unordered map data structure. In your code, it is used to store movie information, where the movie title is the key and the corresponding movie details are the value (std::unordered_map<std::string, Movie>).

<vector>: Used for dynamic arrays. In your code, it is used to store lists of movie titles and user information (std::vector<std::string>, std::vector<User>).

<algorithm>: Used for various algorithms. In your code, it is used for sorting movie titles (std::sort) and finding the maximum value for formatting output (std::max).

<windows.h> and <conio.h>: These are Windows-specific libraries used for console-related functions. In your code, they may be used for functions like clearing the console screen (clearScreen()) and reading user input without waiting for the Enter key (_getch()).

<unordered_set>: Used for storing unique elements in no particular order. In your code, it may be used to store unique phone numbers or email addresses (std::unordered_set<std::string>).

<iomanip>: Used for input/output manipulation. In your code, it may be used for formatting output, such as aligning text (std::setw, std::left).

<regex>: Used for regular expressions. In your code, it may be used for validating email addresses or performing pattern matching operations on strings (std::regex_match).

<string>: Used for string operations and manipulations. In your code, it is used for storing and manipulating strings (std::string).

### Usage

To use the Movie Booking System:

1. Clone the repository and navigate to the project directory.
2. Compile the code using a C++ compiler (e.g., g++).
3. Run the compiled executable.
4. Follow the on-screen prompts to access the admin or user console and interact with the program.

### Dependencies

The Movie Booking System has the following dependencies:

- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

### Contributing

Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

### License

This project is licensed under the [MIT License](LICENSE).

### Acknowledgments

This project was inspired by the need for a simple movie booking system. It aims to provide a foundational structure for similar applications, making it easier for developers to build upon and customize the system according to their specific requirements.

