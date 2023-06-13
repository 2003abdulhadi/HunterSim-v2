#ifndef GHOST_H
#define GHOST_H

#include "defs.h"
#include "Room.h"
#include "Building.h"

/// @brief Ghost defines the base for the 4 ghost classes, Banshee, Bullies, Phantom and Poltergiest
/// Each ghost implements its own method to create evidence, and uses the base class methods to interact with the room
/// The update method defines the main game loop for a ghost
class Ghost
{
    friend std::ostream &operator<<(std::ostream &, Ghost &);

public:
    Ghost();
    virtual ~Ghost() = 0;
    static std::shared_ptr<Ghost> makeRandGhost();
    void update();
    std::thread spawn();
    int &getBoredom();
    void setRoom(std::shared_ptr<Room>);
    virtual std::ostream &output(std::ostream &) = 0;

    virtual std::shared_ptr<Evidence> createEvidence() = 0;

    void clear();

protected:
    std::shared_ptr<Room> room;
    int boredom;
};

#include "Banshee.h"
#include "Bullies.h"
#include "Phantom.h"
#include "Poltergeist.h"

#endif