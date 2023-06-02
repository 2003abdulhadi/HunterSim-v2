#include "Room.h"

Room::Room(std::string n) : name(n) {}

Room::~Room() {}

void Room::addEvidence(std::shared_ptr<Evidence> e)
{
    evidence.insert(e);
}

void Room::addHunter(std::shared_ptr<Hunter> h)
{
    hunters.insert(h);
}

void Room::addGhost(std::shared_ptr<Ghost> g)
{
    ghost = g;
}

void Room::connectRoom(std::shared_ptr<Room> r)
{
    rooms.push_back(std::weak_ptr<Room>(r));
}

std::vector<std::weak_ptr<Room>> &Room::getRooms()
{
    return rooms;
}

std::string& Room::getName()
{
    return name;
}