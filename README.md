<div align="center">
  <h1>Movie Booking System</h1>
  <p>A Command-Line Application for Booking Movie Tickets</p>
</div>

## Introduction

The Movie Booking System is a command-line application implemented in C++. It allows users to book movie tickets, view movie information, and manage user data. The program provides separate consoles for administrators and users, each with different functionalities.

## Data Structures

The code utilizes the following data structures:

- `std::unordered_map<std::string, Movie>`: This unordered map stores movies as key-value pairs, where the movie title is the key and the associated movie information is the value. It allows fast access to movie information based on the title.

- `std::vector<User>`: This vector stores user information. Each element in the vector represents a user and contains attributes such as name, phone number, and email address. The vector allows storing and accessing multiple user records.

Both data structures are used to store and manage movie and user data, respectively, throughout the program. The unordered map provides efficient lookup based on movie titles, while the vector allows storing and iterating over multiple user records.

## Algorithms

The program incorporates various algorithms to implement its functionality:

- **Input Validation**: The program uses regular expressions (`std::regex_match`) to validate user input, such as full names, phone numbers, and email addresses. Regular expressions allow for pattern matching and ensure that the entered data meets the required format.

- **Error Handling**: Error handling techniques are used to handle invalid user input gracefully. The program provides meaningful error messages to guide the user in correcting their input and prevents the program from crashing due to unexpected input.

- **Sorting**: The `std::sort` algorithm is used to sort movie titles in alphabetical order. This allows for a more organized display of movie information.

## Functionality

### Admin Console

The Admin Console provides functionalities for administrators to perform various tasks:

- **Add new movies**: Administrators can add new movies to the system by providing details such as movie title, price, duration, and available showtimes. The program adds the new movie to the `std::unordered_map` of movies.

- **Delete movies**: Administrators can delete movies from the system if they are no longer available. The program removes the movie from the `std::unordered_map` of movies.

- **Modify movie details**: Administrators can modify the details of existing movies, such as title, price, duration, and available showtimes. The program updates the corresponding movie information in the `std::unordered_map` of movies.

- **View movie information**: Administrators can view detailed information about each movie, including its title, price, duration, available showtimes, and the number of booked seats. The program retrieves the movie information from the `std::unordered_map` of movies and displays it.

- **View user information**: Administrators can view information about the users who have booked movie tickets, including their names, phone numbers, and email addresses. The program retrieves the user information from the `std::vector` of users and displays it.

- **Modify user details**: Administrators can modify the details of users, such as their names, phone numbers, and email addresses. The program updates the corresponding user information in the `std::vector` of users.

- **Delete user information**: Administrators can delete user records from the system if necessary. The program removes the user record from the `std::vector` of users.

### User Console

The User Console allows users to book movie tickets:

- **View available movies**: Users can view a list of available movies, including their titles, prices, durations, and available showtimes. The program retrieves the movie information from the `std::unordered_map` of movies and displays it.

- **Book movie tickets**: Users can select a movie from the available list and proceed to book tickets by providing their personal information, including their full name, phone number, and email address. The program creates a new user record and adds it to the `std::vector` of users.

## Libraries Used

The following libraries are used in the code:

- `iostream`: Provides input/output stream operations for reading input from the user (`std::cin`) and displaying output to the console (`std::cout`).
- `fstream`: Enables file stream operations, allowing reading from and writing to files (`std::ifstream`, `std::ofstream`).
- `sstream`: Provides string stream operations for reading from and writing to strings (`std::stringstream`).
- `cstdlib`: Provides general-purpose functions for C programming language.
- `unordered_map`: Used for storing key-value pairs in an unordered map data structure. In this code, it is used to store movie information, with the movie title as the key and the corresponding movie details as the value (`std::unordered_map<std::string, Movie>`).
- `vector`: Supports dynamic arrays and is used to store lists of movie titles and user information (`std::vector<std::string>`, `std::vector<User>`).
- `algorithm`: Provides various algorithms such as sorting (`std::sort`) and finding the maximum value (`std::max`). It is used in this code to sort movie titles and format output.
- `windows.h` and `conio.h`: These Windows-specific libraries are used for console-related functions. In this code, they may be used for clearing the console screen (`clearScreen()`) and reading user input without waiting for the Enter key (`_getch()`).
- `unordered_set`: Used for storing unique elements in no particular order. In this code, it may be used to store unique phone numbers or email addresses (`std::unordered_set<std::string>`).
- `iomanip`: Provides input/output manipulation for formatting output, such as aligning text (`std::setw`, `std::left`).
- `regex`: Supports regular expressions for pattern matching and validation. In this code, it may be used for validating email addresses or performing pattern matching operations on strings (`std::regex_match`).
- `string`: Used for string operations and manipulations (`std::string`).

These libraries provide essential functionalities for various aspects of the code, including input/output handling, file operations, data storage, manipulation of strings, and more.

## Usage

To use the Movie Booking System:

1. Clone the repository and navigate to the project directory.
2. Compile the code using a C++ compiler (e.g., g++).
3. Run the compiled executable.
4. Follow the on-screen prompts to access the admin or user console and interact with the program.

## Dependencies

The Movie Booking System has the following dependencies:

- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

## Contributing

Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

This project was inspired by the need for a simple movie booking system. It aims to provide a foundational structure for similar applications, making it easier for developers to build upon and customize the system according to their specific requirements.
