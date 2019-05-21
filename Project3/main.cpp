/*
 * File: main.cpp
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Entry point
 */
#include <iostream>
#include "swimmingPool.h"
#include "randomGen.h"
#include "log.h"

void runSimulation(std::ifstream& fd) {
    std::string swimmingPoolName;
    int withDelays, lengthOfSimulation, numberOfPlaces, numberOfCashdesks, numberOfInstructors, numberOfRescuers, seed;

    fd >> swimmingPoolName >> withDelays >> lengthOfSimulation;
    fd >> numberOfPlaces >> numberOfCashdesks >> numberOfInstructors >> numberOfRescuers >> seed;
    if(fd.fail())
        throw std::invalid_argument("Invalid config file! Exiting...");

    SwimmingPool pool(swimmingPoolName, withDelays);
    Place* places[numberOfPlaces];
    Cashdesk* cashdesks[numberOfCashdesks];
    Instructor* instructors[numberOfInstructors];
    Rescuer* rescuers[numberOfRescuers];
    initializeRandomGen(seed);

    for(int i = 0; i < numberOfCashdesks; i++)
        cashdesks[i] = new Cashdesk(pool);
    for(int i = 0; i < numberOfInstructors; i++)
        instructors[i] = new Instructor();
    for(int i = 0; i < numberOfRescuers; i++)
        rescuers[i] = new Rescuer();

    for(int i = 0; i < numberOfPlaces; i++) {
        std::string placeName;
        int exp, noIns, noRes, uid;
        fd >> placeName >> exp >> noIns >> noRes;
        if(placeName == "Track" || placeName == "TRACK")
            places[i] = new Track(pool, exp);
        else
            places[i] = new Place(placeName, pool, exp);
        for(int j = 0; j < noIns; j++) {
            fd >> uid;
            // Due to the 48-bit size of address space on x86_64, last 16 bits are always 0
            // We will use the MSB to indicate if instructor is already in use
            if(uid >= numberOfInstructors || ((long long)instructors[uid] & (1ll << 63)) != 0)
                throw std::invalid_argument("Invalid config file - invalid instructor! Exiting...");
            places[i]->addWorker(*instructors[uid]);
            instructors[uid] = (Instructor*)((long long)instructors[uid] | (1ll<<63));
        }
        for(int j = 0; j < noRes; j++) {
            fd >> uid;
            if(uid >= numberOfRescuers || ((long long)rescuers[uid] & (1ll << 63)) != 0)
                throw std::invalid_argument("Invalid config file - invalid rescuer! Exiting...");
            places[i]->addWorker(*rescuers[uid]);
            rescuers[uid] = (Rescuer*)((long long)rescuers[uid] | (1ll<<63));
        }
    }
    if(fd.fail())
        throw std::invalid_argument("Invalid config file! Exiting...");

    Logger() << "Launching simulation for " << lengthOfSimulation << " cycles";
    for(int i = 0; i < lengthOfSimulation; i++)
        pool.simulate();

    for(int i = 0; i < numberOfInstructors; i++)
        delete (Instructor*)((long long)instructors[i] & ~(1ll << 63));
    for(int i = 0; i < numberOfRescuers; i++)
        delete (Rescuer*)((long long)rescuers[i] & ~(1ll << 63));
    for(int i = 0; i < numberOfCashdesks; i++)
        delete cashdesks[i];
    for(int i = 0; i < numberOfPlaces; i++)
        delete places[i];

}

void runTests() {
    const char* testFiles [] = {"tests/test1.txt",
                                "tests/test2.txt",
                                "tests/test3.txt",
                                "tests/test4.txt",
                                "tests/test5.txt",
                                "tests/test6.txt"};

    for(const char* test : testFiles) {
        Logger() << "Starting test \"" << test << "\"";
        std::ifstream fd;
        fd.open(test);
        if(fd.fail()) {
            Logger(Logger::CRIT) << "Unable to read \"" << test << "\" ! Exiting...";
            continue;
        }

        try {
            runSimulation(fd);
            fd.close();
        } catch(std::exception& ex) {
            Logger(Logger::CRIT) << "Test \"" << test << "\" failed!";
            Logger(Logger::CRIT) << ex.what();
            continue;
        }
        Logger() << "Test \"" << test << "\" succeed!";
    }
}

int main(int argc, char** argv) {
    Logger().clear();
    if(argc != 2) {
        Logger() << "Launching program in test mode";
        runTests();
        return 0;
    }

    std::ifstream fd;
    fd.open(argv[1]);
    if(fd.fail()) {
        Logger(Logger::CRIT) << "Unable to read config file! Exiting...";
        exit(1);
    }

    try {
        runSimulation(fd);
    } catch(std::exception& ex) {
        Logger(Logger::CRIT) << ex.what();
        exit(1);
    }
    fd.close();
    return 0;
}
