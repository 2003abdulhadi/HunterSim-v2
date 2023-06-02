#ifndef ROOM_H
#define ROOM_H

#include "defs.h"
#include "Evidence.h"
#include "Ghost.h"
#include "Hunter.h"

class Room
{
public:
    Room(std::string);
    ~Room();
    void addEvidence(std::shared_ptr<Evidence>);
    void addHunter(std::shared_ptr<Hunter>);
    void addGhost(std::shared_ptr<Ghost>);
    void connectRoom(std::shared_ptr<Room>);
    std::vector<std::weak_ptr<Room>> &getRooms();
    std::string& getName();

private:
    std::string name;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
    std::unordered_set<std::shared_ptr<Hunter>> hunters;
    std::vector<std::weak_ptr<Room>> rooms;
    std::shared_ptr<Ghost> ghost;
};

#endif