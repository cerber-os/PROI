#include <iostream>
#include "swimmingPool.h"
#include "randomGen.h"
#include "log.h"

void test1() {
    try {
        Logger() << "Running test #1";
        initializeRandomGen(123);
        SwimmingPool test1("Test1", false);
        Instructor instructors[3];
        Rescuer rescuers[3];

        Place track("Swimming track", test1, 4);
        Place longSlide("Long slide", test1, 3);
        Place jacuzzi("Jacuzzi", test1, 0);
        Place shortSlide("Short slide", test1, 1);
        Cashdesk cashdesk(test1);

        track.addWorker(instructors[0]);
        track.addWorker(rescuers[0]);
        longSlide.addWorker(instructors[1]);
        longSlide.addWorker(rescuers[1]);
        jacuzzi.addWorker(instructors[2]);
        jacuzzi.addWorker(rescuers[2]);

        for(int i = 0; i < 5; i++)
            test1.simulate();
    } catch(std::exception& e) {
        Logger(Logger::CRIT) << e.what();
        Logger(Logger::CRIT) << "Fatal error occurred... Test failed";
    } catch(...) {
        Logger(Logger::CRIT) << "Unknown exception... Test failed";
    }
}

void runTests() {
    test1();
}

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

int main(int argc, char** argv) {
    Logger().clear();
    if(argc != 2) {
        Logger(Logger::CRIT) << "Usage: ./" << argv[0] << " configFile";
        exit(1);
    }

    std::ifstream fd;
    fd.open(argv[1]);
    if(fd.fail()) {
        Logger(Logger::CRIT) << "Unable to read config file! Exiting...";
        exit(1);
    }

    std::string mode;
    fd >> mode;
    if(mode == "TEST")
        runTests();
    else if(mode == "MANUAL") {
        try { runSimulation(fd);}
        catch(std::exception& ex) {
            Logger(Logger::CRIT) << ex.what();
            exit(1);
        }
    } else {
        Logger(Logger::CRIT) << "Invalid mode specified in config file: \"" << mode << "\"! Exiting...";
        exit(1);
    }
}