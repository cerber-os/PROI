/*
 * File: log.h
 * Author: Paweł Wieczorek
 * Date: 10 maj 2019
 * Description: Class providing logging features
 */

#ifndef PROJECT3_LOG_H
#define PROJECT3_LOG_H

#include <string>
#include <fstream>
#include <iostream>

/**
 * Logger - simple class providing logging on stdout and text file
 *      usage:      Logger(level, time) << message1 << message2 << ...
 *                  Logger().clear()
 *      examples:   Logger(Logger::ERROR, 10) << "Error occurred";
 *                  Logger() << "This is info message without time specified";
 *      arguments:  level - type of message (DEBUG, INFO, ERROR, CRIT)          | default: INFO
 *                  time  - the timestamp to be displayed before the message    | default: "---"
 */
class Logger {
    // Handler to the opened file
    std::ofstream fd;
    const std::string outputFileName  = "output.txt";

    // Const strings used in output formatting
    const std::string CONSOLE_DEFAULT = "\033[0m";
    const std::string CONSOLE_RED     = "\033[0;31m";
    const std::string CONSOLE_BLUE    = "\033[0;34m";
    const std::string CONSOLE_GREEN   = "\033[0;32m";
    const std::string COLORS[4]       = {CONSOLE_DEFAULT,
                                         CONSOLE_GREEN,
                                         CONSOLE_RED,
                                         CONSOLE_RED};
    const std::string DECORATORS[4]   = {"[D]","[+]","[!]","[FAIL]"};

public:
    enum levels{DEBUG, INFO, ERROR, CRIT};

    explicit Logger(levels logLevel, int time = -1) {
        // Open file in appending mode
        try { fd.open(outputFileName, std::ofstream::app); }
        catch(...) {        // Cannot open file
            std::cout << "ERROR: Unable to open log file for writing! Exiting..." << std::endl;
        }

        // Prepare timestamp string - if no provided (-1) insert "---"; otherwise convert to number and add padding
        std::string time_s = (time == -1 ? "---" : std::to_string(time));
        if(time_s.length() <= 4)
            time_s.insert(time_s.begin(), 4 - time_s.length(),' ');

        // Write the beginning of line in the form: "[time][S]"; use colors on stdout
        fd << "[" << time_s << "]"
           << DECORATORS[logLevel] << " ";

        std::cout << CONSOLE_BLUE << "[" << time_s << "]"
                  << COLORS[logLevel] << DECORATORS[logLevel] << CONSOLE_DEFAULT << " ";

    };
    explicit Logger(int time=-1) : Logger(INFO, time) {};

    ~Logger() {
        // Append new lines
        std::cout << std::endl;
        fd << std::endl;

        fd.close();
    };

    template<class T>
    Logger &operator<<(const T &msg) {
        std::cout << msg;
        fd << msg;
        return *this;
    }

    void clear() {
        fd.close();
        fd.open(outputFileName, std::ofstream::trunc);      // Reopen output file in truncate mode to cleat it
    }
};

#endif //PROJECT3_LOG_H
