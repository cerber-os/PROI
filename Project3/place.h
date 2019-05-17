/*
 * File: place.h
 * Author: anybody
 * Date: 08 maj 2019
 * Description:
 */

#ifndef PROJECT3_PLACE_H
#define PROJECT3_PLACE_H
#include <string>
#include <vector>
#include <queue>
#include "client.h"
#include "worker.h"
#include "swimmingPool.h"

class SwimmingPool;
class Place {
    static int highestUid;
    enum {CALL_INSTRUCTOR, FREE_INSTRUCTOR, LEVEL_UP, MOVE, NEED_HELP};
protected:
    int uid;
    std::string name;
    std::vector<Place*> const & places;
    std::vector<Place*> const & specialPlaces;
    std::vector<Client*> clients;
    std::vector<Worker*> workers;
    int requiredExp;
    int currentTimeTick;

public:
    explicit Place(std::string, SwimmingPool&, int);
    virtual void simulate(int);

    virtual void addWorker(Worker&);
    virtual void addClient(Client&);
    virtual void removeClient(Client&);
    virtual int getRequiredExp();
    virtual std::string getName() const;
    virtual Instructor& getFreeInstructor();
    virtual Instructor& getInstructorById(int);
    virtual Rescuer& getFreeRescuer();
    virtual Place& getRandomPlace(int maxExp);
    virtual void moveClientTo(Client&, Place&);
};

class Cashdesk : public Place {
    std::queue<Client*> clientsWaiting;
    std::queue<Client*> clientsReadyToGo;
    static int highestUid;

public:
    explicit Cashdesk(SwimmingPool&);
    void simulate(int) override;
    void moveClientTo(Client&, Place&) override;
    void moveClientsWithTicket();
    void serveClient();
};

#endif //PROJECT3_PLACE_H
