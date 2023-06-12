#include "Room.h"

Room::Room(std::string n) : name(n), ghost(nullptr) {}

Room::~Room()
{
    ghost = nullptr;
    rooms.clear();
}

void Room::addEvidence(std::shared_ptr<Evidence> e)
{
    evidence.insert(e);
}

void Room::addHunter(std::shared_ptr<Hunter> h)
{
    hunters.insert(std::make_pair(h->getName(), h));
}

std::shared_ptr<Hunter> Room::removeHunter(std::string h)
{
    auto hunter = hunters.at(h);
    hunters.erase(h);
    return hunter;
}

void Room::addGhost(std::shared_ptr<Ghost> g)
{
    ghost = g;
}

std::shared_ptr<Ghost> Room::removeGhost()
{
    auto g = ghost;
    ghost = nullptr;
    return g;
}

void Room::connectRoom(std::shared_ptr<Room> r)
{
    rooms.push_back(r);
}

bool Room::shareEvidence(std::string h)
{
    bool ghostly = false;
    std::shared_ptr<Hunter> hunter = hunters[h];
    for (auto &e : evidence)
    {
        if (e->getType() == hunter->getType())
        {
            hunter->addEvidence(e);
            evidence.erase(e);
            if (!ghostly && e->isGhostly())
                ghostly = true;
        }
    }
    return ghostly;
}

std::vector<std::weak_ptr<Room>> &Room::getRooms()
{
    return rooms;
}

std::string &Room::getName()
{
    return name;
}

std::weak_ptr<Room> Room::getRandRoom()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, rooms.size() - 1);

    return rooms.at(dist(rng));
}

std::shared_ptr<Hunter> Room::getRandHunter()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, hunters.size() - 1);
    int i, r;
    i = 0;
    r = dist(rng);
    for (const auto &h : hunters)
        if (i++ == r)
            return h.second;
    return hunters.begin()->second;
}

bool Room::hasGhost()
{
    return ghost != nullptr;
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
    std::cout << "LOCKING " << name << std::endl;
    return lock.try_lock();
}

void Room::unlockRoom()
{
    std::cout << "UNLOCKING " << name << std::endl;
    return lock.unlock();
}

void Room::clear()
{
    rooms.clear();
    hunters.clear();
    ghost = nullptr;
}

std::ostream &operator<<(std::ostream &o, Room &r)
{
    return o << r.name << ", has ghost?: " << r.hasGhost();
}
