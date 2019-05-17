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
        Place jacuzzi("Jacuzzi", test1, 1);
        Place shortSlide("Short slide", test1, 1);
        Cashdesk cashdesk(test1);

        track.addWorker(instructors[0]);
        track.addWorker(rescuers[0]);
        longSlide.addWorker(instructors[1]);
        longSlide.addWorker(rescuers[1]);
        jacuzzi.addWorker(instructors[2]);
        jacuzzi.addWorker(rescuers[2]);

        for(int i = 0; i < 1000; i++)
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
}