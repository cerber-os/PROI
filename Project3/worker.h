/*
 * File: worker.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing workers of swimming pool - header
 */

#ifndef PROJECT3_WORKER_H
#define PROJECT3_WORKER_H
#include <string>
#include <iostream>

/**
 * Worker - class representing workers of swimming pool
 *      fields:     uid - unique id of object
 *                  name - name of worker; default: Generic
 *                  highestUid - first available id (starts with 0)
 *      examples:   Worker("Plumber");
 */
class Worker {
    static int highestUid;
protected:
    int uid;
    std::string name;

public:
    explicit Worker(std::string name = "Generic") : uid(highestUid++), name(std::move(name)) {};
    virtual ~Worker() = default;
    virtual std::string getName();
    virtual bool isFreeInstructor();
    virtual bool isFreeRescuer();
    virtual bool isInstructor();
    virtual bool isRescuer();
    virtual int getId();
};

/**
 * Instructor - class representing instructor
 */
class Instructor : public Worker {
    bool isFree = true;
    static int highestUid;
public:
    explicit Instructor(std::string displayedName = "Instructor");
    bool isFreeInstructor() override;
    bool isInstructor() override;
    void setInstructorAvailability(bool free);
};

/**
 * Instructor - class representing rescuer
 */
class Rescuer : public Worker {
    bool isFree = true;
    static int highestUid;
public:
    explicit Rescuer(std::string displayedName = "Rescuer");
    bool isFreeRescuer() override;
    bool isRescuer() override;
};

#endif //PROJECT3_WORKER_H
