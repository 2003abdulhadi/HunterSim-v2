#include "Ghost.h"

Ghost::Ghost() {}

Ghost::~Ghost() {}

void Ghost::setRoom(std::shared_ptr<Room> r)
{
    room = r;
}

int& Ghost::getBoredom()
{
    return boredom;
}

std::ostream& operator<<(std::ostream& o, Ghost& g)
{
    return g.output(o);
}