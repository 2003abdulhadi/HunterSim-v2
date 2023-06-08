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

void Room::removeHunter(std::shared_ptr<Hunter> h)
{
    hunters.erase(h);
}

void Room::addGhost(std::shared_ptr<Ghost> g)
{
    ghost = g;
}

void Room::connectRoom(std::shared_ptr<Room> r)
{
    rooms.push_back(std::weak_ptr<Room>(r));
}

bool Room::shareEvidence(std::shared_ptr<Hunter> h)
{
    bool ghostly;
    for(auto& e : evidence)
    {
        if(e->getType() == h->getType())
        {
            h->addEvidence(e);
            evidence.erase(e);
            if(!ghostly && e->isGhostly())
                ghostly = true;
        }
    }
    return ghostly;
}

std::vector<std::weak_ptr<Room>> &Room::getRooms()
{
    return rooms;
}

std::string& Room::getName()
{
    return name;
}

std::weak_ptr<Room> Room::getRandRoom()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, rooms.size());

    return rooms.at(dist(rng));
}

std::weak_ptr<Hunter> Room::getRandHunter()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, hunters.size());
    int i, r;
    r = dist(rng);
    for(const auto& h : hunters)
    {
        i++;
        if(i == r)
            return std::weak_ptr<Hunter>(h);
    }
}

bool Room::hasGhost()
{
    return (ghost.get() != nullptr);
}

int Room::hasHunter()
{
    return hunters.size();
}

bool Room::hasEvidence()
{
    return (evidence.size() > 0);
}

bool Room::lockRoom()
{
    return lock.try_lock();
}

void Room::unlockRoom()
{
    return lock.unlock();
}
