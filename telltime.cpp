#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>  // For system("CLS")

void display_time() {
    while (true) {
        // Get current time
        auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Convert time to string
        std::string time_str = std::ctime(&current_time);

        // Clear the screen (for Windows)
        system("CLS");

        // Display the current time
        std::cout << "Current time: " << time_str << std::flush;

        // Wait for 1 second before updating
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    display_time();
    return 0;
}
