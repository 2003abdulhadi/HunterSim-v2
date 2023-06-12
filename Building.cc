#include "Building.h"

Building::Building() {}

Building::~Building() {}

void Building::addHunter(std::shared_ptr<Hunter> h)
{
    hunters.insert(std::make_pair(h->getName(), h));
}

void Building::addGhost(std::shared_ptr<Ghost> g)
{
    ghost = g;
}

void Building::addRoom(std::string r)
{
    rooms.insert(std::make_pair(r, std::make_shared<Room>(r)));
}

void Building::connectRoom(std::string r1, std::string r2)
{
    auto x = rooms.at(r1);
    auto y = rooms.at(r2);

    x->connectRoom(y);
    y->connectRoom(x);
}

const std::shared_ptr<Room> Building::getRoom(std::string n)
{
    return rooms.at(n);
}

const std::shared_ptr<Room> &Building::getRandRoom()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, rooms.size()-1);
    int i, j;
    i = 0;
    j = dist(rng);
    for(const auto& r : rooms)
    {
        i++;
        if(i == j)
            return r.second;
    }
    return rooms.begin()->second;
}

void Building::printRooms()
{
    for(const auto& r : rooms)
    {
        std::cout << r.first << " - connects to:" << std::endl;
        for(const auto& a : r.second->getRooms())
        {
            std::cout << a.lock()->getName() << std::endl;
        }
        std::cout << std::endl;
    }
}

void Building::printCharacters()
{
    std::cout<< *ghost << std::endl;
    for(const auto& h : hunters)
        std::cout << *(h.second) << std::endl;
}

void Building::initRooms()
{
    addRoom("Van");
    addRoom("Hallway");
    addRoom("Master Bedroom");
    addRoom("Boys Room");
    addRoom("Bathroom");
    addRoom("Basement");
    addRoom("Basement Hallway");
    addRoom("Right Storage Room");
    addRoom("Left Storage Room");
    addRoom("Kitchen");
    addRoom("Living Room");
    addRoom("Garage");
    addRoom("Utility Room");
    addRoom("Front Yard");

    connectRoom("Hallway", "Van");
    connectRoom("Hallway", "Master Bedroom");
    connectRoom("Hallway", "Boys Room");
    connectRoom("Hallway", "Bathroom");
    connectRoom("Hallway", "Kitchen");
    connectRoom("Hallway", "Basement");
    connectRoom("Basement Hallway", "Basement");
    connectRoom("Basement Hallway", "Right Storage Room");
    connectRoom("Basement Hallway", "Left Storage Room");
    connectRoom("Kitchen", "Living Room");
    connectRoom("Kitchen", "Garage");
    connectRoom("Garage", "Utility Room");
    connectRoom("Front Yard", "Van");
}