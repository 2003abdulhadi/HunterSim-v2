#include "Building.h"

Building::Building() {}

Building::~Building() {}

void Building::addHunter(std::shared_ptr<Hunter> h)
{
    if (hunters.insert(h).second)
        std::cout << "Hunter: " << h->getName() << " added to building" << std::endl;
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

const std::shared_ptr<Room> Building::getRoom(std::string n)
{
    for(auto& node : rooms)
        if(node.first->getName() == n)
            return node.first;

    return nullptr;
}

const std::shared_ptr<Room> &Building::getRandRoom()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, rooms.size());
    int i, j;
    i = 0;
    j = dist(rng);
    for(const auto& r : rooms)
    {
        i++;
        if(i == j)
            return r.first;
    }
    return rooms.begin()->first;
}

void Building::printRooms()
{
    for(const auto& r : rooms)
    {
        std::cout << r.first->getName() << " - connects to:" << std::endl;
        for(const auto& a : r.first->getRooms())
        {
            std::cout << a.lock()->getName() << std::endl;
        }
        std::cout << std:: endl;
    }
}

void Building::initRooms()
{
    std::shared_ptr<Room> van = std::make_shared<Room>("Van");
    std::shared_ptr<Room> hallway = std::make_shared<Room>("Hallway");
    std::shared_ptr<Room> master_bedroom = std::make_shared<Room>("Master Bedroom");
    std::shared_ptr<Room> boys_room = std::make_shared<Room>("Boy's Room");
    std::shared_ptr<Room> bathroom = std::make_shared<Room>("Bathroom");
    std::shared_ptr<Room> basement = std::make_shared<Room>("Basement");
    std::shared_ptr<Room> basement_hallway = std::make_shared<Room>("Basement Hallway");
    std::shared_ptr<Room> right_storage_room = std::make_shared<Room>("Right Storage Room");
    std::shared_ptr<Room> left_storage_room = std::make_shared<Room>("Left Storage Room");
    std::shared_ptr<Room> kitchen = std::make_shared<Room>("Kitchen");
    std::shared_ptr<Room> living_room = std::make_shared<Room>("Living Room");
    std::shared_ptr<Room> garage = std::make_shared<Room>("Garage");
    std::shared_ptr<Room> utility_room = std::make_shared<Room>("Utility Room");
    std::shared_ptr<Room> front_yard = std::make_shared<Room>("Front Yard");

    addRoom(van);
    addRoom(hallway);
    addRoom(master_bedroom);
    addRoom(boys_room);
    addRoom(bathroom);
    addRoom(basement);
    addRoom(basement_hallway);
    addRoom(right_storage_room);
    addRoom(left_storage_room);
    addRoom(kitchen);
    addRoom(living_room);
    addRoom(garage);
    addRoom(utility_room);
    addRoom(front_yard);

    connectRoom(hallway, van);
    connectRoom(hallway, master_bedroom);
    connectRoom(hallway, boys_room);
    connectRoom(hallway, bathroom);
    connectRoom(hallway, kitchen);
    connectRoom(hallway, basement);
    connectRoom(basement_hallway, basement);
    connectRoom(basement_hallway, right_storage_room);
    connectRoom(basement_hallway, left_storage_room);
    connectRoom(kitchen, living_room);
    connectRoom(kitchen, garage);
    connectRoom(garage, utility_room);
    connectRoom(front_yard, van);
}