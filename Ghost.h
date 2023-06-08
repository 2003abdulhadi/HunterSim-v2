#ifndef GHOST_H
#define GHOST_H

#include "defs.h"
#include "Room.h"
#include "Building.h"

class Ghost
{
    friend std::ostream &operator<<(std::ostream &, Ghost &);

public:
    Ghost();
    virtual ~Ghost() = 0;
    virtual std::shared_ptr<Evidence> createEvidence() = 0;
    virtual std::ostream &output(std::ostream &) = 0;
    void update();
    std::thread spawn();
    void setRoom(std::shared_ptr<Room>);
    int &getBoredom();

protected:
    std::shared_ptr<Room> room;
    int boredom;
};

#endif