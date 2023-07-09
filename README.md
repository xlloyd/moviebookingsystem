

## Movie Booking System

The Movie Booking System is a command-line application implemented in C++. It allows users to book movie tickets, view movie information, and manage client data. The program provides separate consoles for administrators and users, each with different functionalities.

### Features

- **Admin Console**: The Admin Console provides functionalities for administrators to perform various tasks:
  - Add new movies: Administrators can add new movies to the system by providing details such as movie title, price, duration, and available showtimes.
  - Delete movies: Administrators can delete movies from the system if they are no longer available.
  - Modify movie details: Administrators can modify the details of existing movies, such as title, price, duration, and available showtimes.
  - View movie information: Administrators can view detailed information about each movie, including its title, price, duration, available showtimes, and the number of booked seats.
  - View client information: Administrators can view information about the clients who have booked movie tickets, including their names, phone numbers, email addresses, booked seats, and available showtimes.
  - Modify client details: Administrators can modify the details of clients, such as their names, phone numbers, email addresses, booked seats, and available showtimes.
  - Delete client information: Administrators can delete client records from the system if necessary.

- **User Console**: The User Console allows users to book movie tickets:
  - View available movies: Users can view a list of available movies, including their titles, prices, durations, and available showtimes.
  - Book movie tickets: Users can select a movie from the available list and proceed to book tickets by providing their personal information, including their full name, phone number, email address, and selected seats.
  - Seat availability check: The system checks the availability of the selected seats and ensures they are not already booked.
  - Confirmation and saving: Once the user confirms the booking, the system saves the booking information and updates the availability of the selected seats.

### Key Components

The Movie Booking System code utilizes several important components:

- **Structs and Classes**: The code defines two main structures, `Movie` and `Client`, to store movie and client information, respectively. The `Movie` struct includes attributes such as title, price, duration, available showtimes, and the number of booked seats. The `Client` struct stores details about the client, including their name, phone number, email address, booked seats, and available showtimes.

- **Data Storage**: The movie data is stored using a `std::unordered_map` container, where the movie title serves as the key and the corresponding `Movie` struct is the value. This data structure allows for efficient lookup based on the movie title, enabling quick retrieval of movie information. The client data is stored in a `std::vector` of `Client` structs, allowing for dynamic addition and removal of client records.

- **File I/O**: The code implements functions for reading movie and client data from a data file (`1data.dat`) and saving the data back to the file. The `loadDataFromFile()` function reads the data file and populates the movie and client data structures, while the `saveDataToFile()` function saves the updated data back to the file.

- **Input Validation**: To ensure data integrity and prevent inconsistencies, the code includes various input validation checks. It validates full names, phone numbers, email addresses, seat availability, and duplicate entries. These validations ensure that the data entered by users or administrators meets the required format and avoids conflicts with existing records.

- **Error Handling**: The program incorporates error handling techniques to handle invalid user input gracefully. It provides meaningful error messages to guide the user in correcting their input and prevents the program from crashing due to unexpected input.

- **Utility Functions**: The code includes several utility functions to perform common tasks. These functions include clearing the console screen, parsing seat information, and validating input formats. These utility functions help streamline the code and enhance its readability.

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

