#include "logger.h"
#include <thread>
#include <vector>
#include <iostream>

void loggerThread(int id, int iterations) {
    auto& logger = Logger::getInstance();
    for (int i = 0; i < iterations; ++i) {
        logger.log("Thread " + std::to_string(id) + ": Iteration " + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    try {

        auto& logger = Logger::getInstance();
        logger.setLogFile("application.log");

        std::vector<std::thread> threads;
        const int numThreads = 5;
        const int iterationsPerThread = 10;

        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(loggerThread, i, iterationsPerThread);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        std::cout << "Logging test completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
