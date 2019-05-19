/*
 * File: place.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing places in swimming pool - header
 */

#ifndef PROJECT3_PLACE_H
#define PROJECT3_PLACE_H
#include <string>
#include <vector>
#include <queue>
#include "client.h"
#include "worker.h"
#include "swimmingPool.h"

// Required to use SwimmingPool& in constructors
class SwimmingPool;

/**
 * Place - class representing places in swimming pool
 *      fields:     uid - unique id of object
 *                  name
 *                  places - reference to vector of places in swimming pool
 *                  clients - vector of clients in this place
 *                  workers - vector of workers in this place
 *                  requiredExp - minimal experience required to be in this place
 *                  currentTimeTick - current simulation tick
 *       notes:  place is being added to the swimming pool vector of places in constructor
 */
class Place {
    static int highestUid;
    // Simulated actions
    enum {CALL_INSTRUCTOR, FREE_INSTRUCTOR, LEVEL_UP, MOVE, NEED_HELP};
protected:
    int uid;
    std::string name;
    std::vector<Place*>& places;
    std::vector<Client*> clients;
    std::vector<Worker*> workers;
    int requiredExp;
    int currentTimeTick;

public:
    explicit Place(std::string, SwimmingPool&, int);
    virtual ~Place();
    virtual void simulate(int);

    virtual void        addWorker                   (Worker&);
    virtual void        addClient                   (Client&);
    virtual void        removeClient                (Client&);
    virtual void        deleteClient                (Client& client, size_t& i);
    virtual int         getRequiredExp              ();
    virtual std::string getName                     () const;
    virtual Instructor& getFreeInstructor           ();
    virtual Instructor& getInstructorById           (int);
    virtual Rescuer&    getFreeRescuer              ();
    virtual Place&      getRandomPlace              (int maxExp);
    virtual void        moveClientTo                (Client&, Place&);
    virtual bool        availableToGo               ();
    virtual void        attachInstructorToClient    (Client& client);
    virtual void        detachInstructorFromClient  (Client& client);
};

/**
 * Cashdesk - class representing cash desk in swimming pool
 *      fields:     clientsWaiting - queue of clients waiting to be served
 *                  clientsReadyToGo - queue of clients already served and ready to enter swimming pool
 */
class Cashdesk : public Place {
    std::queue<Client*> clientsWaiting;
    std::queue<Client*> clientsReadyToGo;
    static int highestUid;

public:
    explicit Cashdesk(SwimmingPool&);
    ~Cashdesk();
    void simulate(int) override;

    void                moveClientTo                (Client&, Place&) override;
    bool                availableToGo               () override;
    void                moveClientsWithTicket       ();
    void                serveClient                 ();
};

/**
 * Track - class representing tracks in swimming pool
 *      fields:     depth - depth of track of value based on required experience
 */
class Track : public Place {
    double depth;
    static int highestUid;

public:
    explicit Track(SwimmingPool&, int);
    std::string         getName                     () const override;
};

#endif //PROJECT3_PLACE_H
