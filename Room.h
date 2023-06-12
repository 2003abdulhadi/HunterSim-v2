#ifndef ROOM_H
#define ROOM_H

#include "defs.h"
#include "Evidence.h"
#include "Ghost.h"
#include "Hunter.h"

class Room
{
    friend std::ostream &operator<<(std::ostream &, Room &);
public:
    Room(std::string);
    ~Room();
    void addEvidence(std::shared_ptr<Evidence>);
    void addHunter(std::shared_ptr<Hunter>);
    std::shared_ptr<Hunter> removeHunter(std::string);
    void addGhost(std::shared_ptr<Ghost>);
    std::shared_ptr<Ghost> removeGhost();
    void connectRoom(std::shared_ptr<Room>);
    bool shareEvidence(std::string);
    std::vector<std::weak_ptr<Room>> &getRooms();
    std::string &getName();
    std::weak_ptr<Room> getRandRoom();
    std::shared_ptr<Hunter> getRandHunter();
    bool hasGhost();
    int hasHunter();
    bool hasEvidence();
    bool lockRoom();
    void unlockRoom();
    void clear();

private:
    std::string name;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
    std::unordered_map<std::string, std::shared_ptr<Hunter>> hunters;
    std::vector<std::weak_ptr<Room>> rooms;
    std::shared_ptr<Ghost> ghost;
    std::mutex lock;
};

#endif