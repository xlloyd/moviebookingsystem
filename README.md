Movie Booking System

This project is a command-line movie booking system implemented in C++. It allows users to book movie tickets, view movie information, and manage client data. The program provides separate consoles for administrators and users, each with different functionalities.

Features:
- Admin Console: Administrators can add new movies, delete movies, modify movie details, view movie information, view client information, modify client details, and delete client information.
- User Console: Users can book movie tickets by selecting from available movies, providing personal information, and confirming the booking.

Key Components:
- Structs and Classes: The code utilizes the `Movie` and `Client` structs to store movie and client information, respectively.
- Data Storage: Movie data is stored in a `std::map`, where the movie title serves as the key and the corresponding `Movie` struct is the value. Client data is stored in a `std::vector` of `Client` structs.
- File I/O: Movie and client data are read from and written to a data file (`1data.dat`) using functions `loadDataFromFile()` and `saveDataToFile()`, respectively.
- Input Validation: The code includes various input validation checks to ensure data integrity and prevent inconsistencies. It validates full names, phone numbers, email addresses, seat availability, and duplicates.
- Error Handling: The program incorporates error handling techniques to handle invalid input gracefully and provide meaningful error messages to guide the user.
- Utility Functions: Several utility functions are implemented for common tasks, such as clearing the console screen, parsing seats, and validating input.

Usage:
1. Clone the repository and navigate to the project directory.
2. Compile the code using a C++ compiler (e.g., g++).
3. Run the compiled executable.
4. Follow the on-screen prompts to access the admin or user console and interact with the program.

Dependencies:
- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

Contributing:
Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

License:
This project is licensed under the [MIT License](LICENSE).

Acknowledgments:
This project was inspired by the need for a simple movie booking system and aims to provide a foundational structure for similar applications.

