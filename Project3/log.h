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
        fd.open(outputFileName, std::ios_base::app);

        // Prepare timestamp string - if no provided (-1) insert "---"; otherwise convert to number and add padding
        std::string time_s = (time == -1 ? "---" : std::to_string(time));
        time_s.insert(time_s.begin(), 3 - time_s.length(),' ');

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
};

#endif //PROJECT3_LOG_H
