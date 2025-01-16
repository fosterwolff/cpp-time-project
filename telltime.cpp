#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>  // For file I/O

int main() {
    std::cout << "Press Enter to update the time and log your input...\n";

    // Define the full path for the CSV file
    std::string logFilePath = "C:\\Users\\foste\\source\\repos\\time\\time\\user_log.csv";

    // Open the user_log.csv file in append mode
    std::ofstream logFile(logFilePath, std::ios::app);

    // Check if the file is open successfully
    if (!logFile.is_open()) {
        std::cerr << "Failed to open the log file!" << std::endl;
        return 1;
    }

    // Write the header only once, if the file is empty.
    logFile.seekp(0, std::ios::end);  // Move to the end of the file
    if (logFile.tellp() == 0) {  // If the file is empty, tellp() returns 0
        logFile << "Date/Time,User Input\n";  // Write the header once
    }

    while (true) {
        // Wait for the user to press Enter
        std::cin.get();  // Wait for the Enter key

        // Get the current time as a time_t object
        std::time_t currentTime = std::time(nullptr);

        // Convert the time_t object to a human-readable format
        std::tm* localTime = std::localtime(&currentTime);

        // Print the updated date and time
        std::cout << "\rDate/Time: "
            << std::setw(2) << std::setfill('0') << localTime->tm_mday << "/"
            << std::setw(2) << std::setfill('0') << (localTime->tm_mon + 1) << "/"
            << (localTime->tm_year + 1900) << " "
            << std::setw(2) << std::setfill('0') << localTime->tm_hour << ":"
            << std::setw(2) << std::setfill('0') << localTime->tm_min << ":"
            << std::setw(2) << std::setfill('0') << localTime->tm_sec
            << std::flush;

        // Move to the next line after printing the date/time
        std::cout << "\n";

        // Allow the user to type input on the next line
        std::cout << "Your input: ";
        std::string userInput;
        std::getline(std::cin, userInput);  // Get the user's input on the new line
        std::cout << "You typed: " << userInput << "\n";

        // Combine the date/time and user input
        std::string dateTime = std::to_string(localTime->tm_mday) + "/" +
            std::to_string(localTime->tm_mon + 1) + "/" +
            std::to_string(localTime->tm_year + 1900) + " " +
            std::to_string(localTime->tm_hour) + ":" +
            std::to_string(localTime->tm_min) + ":" +
            std::to_string(localTime->tm_sec);

        // Write the date/time and user input to the CSV file
        logFile << "\"" << dateTime << "\",\"" << userInput << "\"\n";
        logFile.flush();  // Ensure the data is written to the file immediately
    }

    // Close the file (although in this case, it will never reach this point in the infinite loop)
    logFile.close();

    return 0;
}
