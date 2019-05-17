#include <iostream>
#include "swimmingPool.h"
#include "randomGen.h"
#include "log.h"

void test1() {
    try {
        Logger() << "Running test #1";
        initializeRandomGen(123);
        SwimmingPool test1("Test1");
        Instructor instructors[3];
        Rescuer rescuers[3];

        Place track("Swimming track", test1, 4);
        Place longSlide("Long slide", test1, 3);
        Place jacuzzi("Jacuzzi", test1, 1);
        Place shortSlide("Short slide", test1, 1);
        Cashdesk cashdesk(test1);

        track.addWorker(instructors[0]);
        track.addWorker(rescuers[0]);
        longSlide.addWorker(instructors[1]);
        longSlide.addWorker(rescuers[1]);
        jacuzzi.addWorker(instructors[2]);
        jacuzzi.addWorker(rescuers[2]);

        test1.addPlace(track);
        test1.addPlace(longSlide);
        test1.addPlace(jacuzzi);
        test1.addPlace(shortSlide);
        test1.addSpecialPlace(cashdesk);

        for(int i = 0; i < 20; i++)
            test1.simulate();
    } catch(std::exception& e) {
        Logger(Logger::CRIT) << e.what();
        Logger(Logger::CRIT) << "Fatal error occurred... Test failed";
    } catch(...) {
        Logger(Logger::CRIT) << "Unknown exception... Test failed";
    }
}

int main() {
    Logger() << "Program starting";
    test1();
    /*initializeRandomGen();
    SwimmingPool pool("Hello world Park");

    Instructor instructors[20];
    Rescuer rescuers[20];

    Place track("Swimming track", pool, 4);
    Place longSlide("Long slide", pool, 3);
    Place jacuzzi("Jacuzzi", pool, 1);
    Place shortSlide("Short slide", pool, 1);
    Cashdesk cashdesk(pool);

    track.addWorker(instructors[0]);
    track.addWorker(rescuers[0]);
    longSlide.addWorker(instructors[1]);
    longSlide.addWorker(rescuers[1]);
    jacuzzi.addWorker(instructors[2]);
    jacuzzi.addWorker(rescuers[2]);

    pool.addPlace(track);
    pool.addPlace(longSlide);
    pool.addPlace(jacuzzi);
    pool.addPlace(shortSlide);
    pool.addSpecialPlace(cashdesk);

    try {
        for(int i = 0; i < 40; i++)
            pool.simulate();
    } catch(std::exception& e) {
        Logger(Logger::CRIT) << e.what();
        Logger(Logger::CRIT) << "Fatal error occurred... Terminating";
        std::abort();
    } catch(...) {
        Logger(Logger::CRIT) << "Unknown exception... Terminating";
        std::abort();
    }*/
    return 0;
}