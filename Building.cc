#include "Building.h"

Building::Building() {}

Building::~Building() {}

void Building::addHunter(std::shared_ptr<Hunter> h)
{
    if (hunters.insert(h).second)
        std::cout << "Hunter: " << h << "added to building" << std::endl;
    else
        std::cout << "Building already contains Hunter: " << h << std::endl;
}

void Building::addGhost(std::shared_ptr<Ghost> g)
{
    ghost = g;
}

void Building::addRoom(std::shared_ptr<Room> r)
{
    rooms.insert(std::make_pair(r, r.get()->getRooms()));
}

bool Building::connectRoom(std::shared_ptr<Room> r1, std::shared_ptr<Room> r2)
{
    auto x = rooms.find(r1);
    auto y = rooms.find(r1);
    if (x == rooms.end())
    {
        std::cout << "Room " << r1.get() << "is not in building" << std::endl;
        return false;
    }
    if (y == rooms.end())
    {
        std::cout << "Room " << r2.get() << "is not in building" << std::endl;
        return false;
    }

    r1.get()->connectRoom(r2);
    r2.get()->connectRoom(r1);
    return true;
}