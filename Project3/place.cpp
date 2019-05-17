/*
 * File: place.cpp
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing places in swimming pool
 */
#include "place.h"
#include "randomGen.h"
#include "swimmingPool.h"
#include "log.h"

int Place::highestUid = 0;
int Cashdesk::highestUid = 0;

Place::Place(std::string name, SwimmingPool& pool, int reqExp=0) :
        name(std::move(name)), requiredExp(reqExp), uid(highestUid++), currentTimeTick(0),
        places(pool.getPlaces()) {
    places.push_back(this);
}

Place::~Place() {
    for(Client* client : clients)
        delete client;          // Free memory occupied by all clients still being in this place
}

void Place::simulate(int _currentTimeTick) {
    currentTimeTick = _currentTimeTick;             // Copy currentTimeTick to local field, so other methods can use it
    for(int i = 0; i < clients.size(); i++) {
        Client* client = clients[i];

        if(client->isOutOfTime(currentTimeTick)) {  // Take care of clients without valid ticket - remove them
            Logger(currentTimeTick) << client->getName() << " has decided to go back to home";
            deleteClient(client, i);
            continue;
        }

        switch(genRandomNumber(0, 15)) {            // Simulate random action
            case CALL_INSTRUCTOR: {
                attachInstructorToClient(client);
                break;
            }
            case FREE_INSTRUCTOR: {
                detachInstructorFromClient(client);
                break;
            }
            case LEVEL_UP: {
                Logger(currentTimeTick) << "After spending some time in the water " << client->getName() << " leveled up without any help";
                client->levelUp();
                break;
            }
            case MOVE: {
                try {
                    Place& place = getRandomPlace(client->getExperience());
                    moveClientTo( *client, place );
                } catch(std::exception& ex) {
                    Logger(Logger::ERROR, currentTimeTick) << "There isn't an adequate place for " << client->getName() << " with experience: " << client->getExperience();
                    Logger(currentTimeTick) << client->getName() << " decided to go home";
                    deleteClient(client, i);
                }
                break;
            }
            case NEED_HELP: {
                try {
                    Rescuer &rescuer = getFreeRescuer();
                    Logger(currentTimeTick) << client->getName() << " was drowning, but thankfully rescuer was nearby";
                } catch ( std::exception &e ) {
                    Logger(Logger::ERROR, currentTimeTick) << "No rescuer near " << getName() << " and " << client->getName() << " has just drowned :/";
                    deleteClient(client, i);
                }
                break;
            }
            default:
                break;
        }
    }
}

void Place::deleteClient(Client* client, int& i) {
    removeClient(*client);
    i--;
    delete client;
}

void Place::detachInstructorFromClient(Client* client) {
    if(client->isInstructorAttached()) {
        int instructorId = client->detachInstructor();
        Instructor& instructor = getInstructorById(instructorId);
        instructor.setInstructorAvailability(true);
        Logger(currentTimeTick) << client->getName() << " has finished learning with " << instructor.getName()
                                << " and leveled up";
        client->levelUp();
    }
}

void Place::attachInstructorToClient(Client* client) {
    if(!client->isInstructorAttached()) {
        try {
            Instructor& instructor = getFreeInstructor();
            instructor.setInstructorAvailability(false);
            client->attachInstructor(instructor.getId());
            Logger(currentTimeTick) << client->getName() << " is being learned with help from "
                                    << instructor.getName();
        } catch(std::exception& ex) {
            Logger(Logger::ERROR, currentTimeTick) << client->getName() << ex.what();
        }
    }
}

void Place::addWorker(Worker& worker) {
    workers.push_back(&worker);
}

void Place::addClient(Client& client) {
    clients.push_back(&client);
}

// Removes client from vector of clients without releasing his memory
void Place::removeClient(Client& target) {
    for(int i = 0; i < clients.size(); i++) {
        if(clients[i]->getId() == target.getId()) {
            if(target.isInstructorAttached()) {
                int instructorId = target.detachInstructor();
                getInstructorById(instructorId).setInstructorAvailability(true);
            }
            clients.erase(clients.begin() + i, clients.begin() + i + 1);
            return;
        }
    }
    throw std::invalid_argument("{removeClient} Such client does not exist: " + std::to_string(target.getId()));
}

std::string Place::getName() const {
    return name + " #" + std::to_string(uid);
}

// Returns reference to the first free instructor. Throws std::invalid_argument exception if no one is available
Instructor& Place::getFreeInstructor() {
    for(Worker* instructor : workers) {
        if(instructor->isFreeInstructor())
            return *(Instructor*)instructor;
    }
    throw std::invalid_argument(" requested instructor, but no one was available");
}

// Returns reference to the first free rescuer. Throws std::invalid_argument exception if no one is available
Rescuer& Place::getFreeRescuer() {
    for(Worker* rescuer : workers) {
        if(rescuer->isFreeRescuer())
            return *(Rescuer*)rescuer;
    }
    throw std::invalid_argument(" requested rescuer, but no one was available");
}

// Returns reference to random place, which requeired experience is low enough for client.
// Throws std::invalid_argument exception if there isn't such place
Place& Place::getRandomPlace(int maxExp) {
    std::vector<Place*> possiblePlaces;
    for(Place* place : places)
        if(place->availableToGo() && place->getRequiredExp() <= maxExp)
            possiblePlaces.push_back(place);

    if(possiblePlaces.empty())
        throw std::invalid_argument("There isn't an adequate place for such amateur");

    return *possiblePlaces[genRandomNumber(0, possiblePlaces.size())];
}

// Moves client to given place and releases his instructor if necessary
void Place::moveClientTo(Client& client, Place& place) {
    // Detach instructor if necessary
    if (client.isInstructorAttached()) {
        int instructorId = client.detachInstructor();
        getInstructorById(instructorId).setInstructorAvailability(true);
        client.levelUp();
        Logger(currentTimeTick) << client.getName() << " decided to move just seconds after increasing his experience";
    }

    place.addClient(client);
    removeClient(client);
    Logger(currentTimeTick) << client.getName() << " moved to " << place.getName();
}

// Returns reference to the instructor with provided id.
// Throws std::invalid_argument exception if such instructor doesn't exist
Instructor& Place::getInstructorById(int id) {
    for(Worker* worker : workers) {
        if(worker->isInstructor() && worker->getId() == id)
            return *((Instructor*)worker);
    }
    throw std::invalid_argument("Instructor with such id doesn't exist");
}

int Place::getRequiredExp() {
    return requiredExp;
}

// Could clients go there by themselves?
bool Place::availableToGo() {
    return true;
}

/**
 * Cashdesk implementation
 */

Cashdesk::Cashdesk(SwimmingPool& pool) : Place("Cashdesk", pool) {
    uid = highestUid++;
}

// Removes clients still waiting in queues
Cashdesk::~Cashdesk() {
    while(!clientsWaiting.empty()) {
        Client* client = clientsWaiting.front();
        delete client;
        clientsWaiting.pop();
    }
    while(!clientsReadyToGo.empty()) {
        Client* client = clientsReadyToGo.front();
        delete client;
        clientsReadyToGo.pop();
    }
}

// Moves client to the swimming pool
void Cashdesk::moveClientTo(Client& client, Place& place) {
    place.addClient(client);
    Logger(currentTimeTick) << client.getName() << " moved to " << place.getName();
}

void Cashdesk::simulate(int _currentTimeTick) {
    currentTimeTick = _currentTimeTick;
    moveClientsWithTicket();
    serveClient();

    // Create some new clients
    if(genRandomNumber(0, 2) == 0) {
        Client* newClient = new Client();
        clientsWaiting.push(newClient);
        Logger(currentTimeTick) << newClient->getName() << " came to the swimming pool";
    }
}

// Sells ticket to the first client in queue
void Cashdesk::serveClient() {
    if(!clientsWaiting.empty()) {
        Client* client = clientsWaiting.front();
        clientsWaiting.pop();
        clientsReadyToGo.push(client);

        int ticketValidFor = currentTimeTick + genRandomNumber(5, 20);
        client->setTicketTime(ticketValidFor);
        Logger(currentTimeTick) << client->getName() << " bought a ticket for " << ticketValidFor << " cycles";
    }
}

// Moves client with ticket to the aquapark
void Cashdesk::moveClientsWithTicket() {
    for(; !clientsReadyToGo.empty(); clientsReadyToGo.pop()) {
        Client* client = clientsReadyToGo.front();
        try {
            moveClientTo(*client, getRandomPlace(client->getExperience()));
        } catch(std::exception& ex) {
            Logger(Logger::ERROR, currentTimeTick) << "There isn't an adequate place for " << client->getName()
                                                   << " with experience: " << client->getExperience();
            Logger(currentTimeTick) << client->getName() << " decided to go home";
            delete client;
        }
    }
}

bool Cashdesk::availableToGo() {
    return false;
}
