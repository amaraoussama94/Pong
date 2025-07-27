/**
 * @file Logger.hpp
 * @brief Minimal logging utility to write debug and error information to a log file.
 * @author Oussama Amara
 * @date 2025-07-27
 */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    Logger(const std::string& filename = "game.log") {
        logFile.open(filename, std::ios::app);
    }

    ~Logger() {
        if (logFile.is_open())
            logFile.close();
    }

    void info(const std::string& message) {
        log("[INFO] " + message);
    }

    void error(const std::string& message) {
        log("[ERROR] " + message);
    }

private:
    std::ofstream logFile;

    void log(const std::string& entry) {
        std::time_t now = std::time(nullptr);
        char buf[64];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        std::string finalEntry = "[" + std::string(buf) + "] " + entry;
        if (logFile.is_open())
            logFile << finalEntry << std::endl;

        std::cout << finalEntry << std::endl;
    }
};
