#ifndef BUILDING_H
#define BUILDING_H

#include "defs.h"
#include "Room.h"
#include "Hunter.h"
#include "Ghost.h"
#include "Evidence.h"

class Building
{
public:
    Building();
    ~Building();
    void addHunter(std::shared_ptr<Hunter>);
    void addGhost(std::shared_ptr<Ghost>);
    void initRooms();
    const std::shared_ptr<Room>& getRoom(std::string);
    void printRooms();
private:
    void addRoom(std::shared_ptr<Room>);
    bool connectRoom(std::shared_ptr<Room>, std::shared_ptr<Room>);
    std::unordered_map<std::shared_ptr<Room>, std::vector<std::weak_ptr<Room>>> rooms;
    std::unordered_set<std::shared_ptr<Hunter>> hunters;
    std::shared_ptr<Ghost> ghost;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
};

#endif