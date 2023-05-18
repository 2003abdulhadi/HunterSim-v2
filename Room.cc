#include "Room.h"

Room::Room(std::string n) : name(n) {}

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
    rooms.insert(std::weak_ptr(r));
}

std::set<std::weak_ptr<Room>> &Room::getRooms()
{
    return rooms;
}