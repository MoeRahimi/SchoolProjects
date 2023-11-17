#include <iostream>
#include <thread>
#include "WashingCycle.hpp"

int main() {
    // Create instances of different cycles
    QuickCycle quickCycle;
    ManualCycle manualCycle("temperate", 1200, false, std::chrono::seconds(60));

    // Start the timer for QuickCycle and wait for a few seconds
    quickCycle.startTimer();
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate 5 seconds passing
    quickCycle.pauseTimer();
    std::cout << "Quick Cycle - Temperature: " << quickCycle.getTemp() << ", Speed: " << quickCycle.getSpeed() << ", Elapsed Time: " << quickCycle.getElapsedTime().count() << " seconds" << std::endl;
    quickCycle.resumeTimer();
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate 3 more seconds
    quickCycle.pauseTimer();
    std::cout << "Quick Cycle - Elapsed Time after resuming: " << quickCycle.getElapsedTime().count() << " seconds" << std::endl;

    // Test ManualCycle
    manualCycle.startTimer();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    manualCycle.pauseTimer();
    std::cout << "Manual Cycle - Temperature: " << manualCycle.getTemp() << ", Speed: " << manualCycle.getSpeed() << ", Elapsed Time: " << manualCycle.getElapsedTime().count() << " seconds" << std::endl;

    return 0;
}