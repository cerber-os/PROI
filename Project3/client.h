/*
 * File: client.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing clients of swimming pool - header file
 */

#ifndef PROJECT3_CLIENT_H
#define PROJECT3_CLIENT_H

#include <iostream>

/**
 * IClient - interface of class Client
 */
class IClient {
public:
    virtual             ~IClient            () = default;
    virtual void        setTicketTime       (int) = 0;
    virtual int         getTicketTime       ()    = 0;
    virtual void        setExperience       (int) = 0;
    virtual int         getExperience       ()    = 0;
    virtual void        attachInstructor    (int) = 0;
    virtual int         detachInstructor    ()    = 0;
    virtual bool        isInstructorAttached()    = 0;
    virtual void        levelUp             ()    = 0;
    virtual bool        isOutOfTime         (int) = 0;
    virtual int         getId               ()    = 0;
    virtual std::string getName             ()    = 0;
};

/**
 * Client - class representing clients of swimming pool
 *      fields:     uid - unique id of object
 *                  experience
 *                  ticketValidUntil - time tick until his ticket is valid
 *                  attachedInstructorId - (-1) if instructor isn't attached, otherwise his id
 *                  highestUid - first available id (starts with 0)
 *      examples:   Client(currentTimeTick + 10, experience);
 */
class Client : public IClient {
    int uid;
    int experience;
    int ticketValidUntil;
    int attachedInstructorId = -1;
    static int highestUid;

public:
    explicit Client(int ticketTime=0, int exp=1) : uid(highestUid++), experience(exp), ticketValidUntil(ticketTime) {};
    ~Client() = default;
    void        setTicketTime       (int);
    int         getTicketTime       ();
    void        setExperience       (int);
    int         getExperience       ();
    void        attachInstructor    (int);
    int         detachInstructor    ();
    bool        isInstructorAttached();
    void        levelUp             ();
    bool        isOutOfTime         (int);
    int         getId               ();
    std::string getName             ();
};
#endif //PROJECT3_CLIENT_H
