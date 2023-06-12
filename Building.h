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
    const std::shared_ptr<Room> getRoom(std::string);
    const std::shared_ptr<Room>& getRandRoom();
    void printRooms();
    void printCharacters();
    void clear();
private:
    void addRoom(std::string);
    void connectRoom(std::string, std::string);
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;
    std::unordered_map<std::string, std::shared_ptr<Hunter>> hunters;
    std::shared_ptr<Ghost> ghost;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
};

#endif