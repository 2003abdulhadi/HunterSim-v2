#ifndef ROOM_H
#define ROOM_H

#include "defs.h"
#include "Evidence.h"
#include "Ghost.h"
#include "Hunter.h"

/// @brief Room class defines a room with methods to interact with the adjacent rooms, hunters, ghost and evidence
class Room
{
    friend std::ostream &operator<<(std::ostream &, Room &);

public:
    Room(std::string);
    ~Room();

    void connectRoom(std::shared_ptr<Room>);
    std::vector<std::weak_ptr<Room>> &getRooms();
    std::string &getName();
    std::weak_ptr<Room> getRandRoom();

    void addHunter(std::shared_ptr<Hunter>);
    std::shared_ptr<Hunter> removeHunter(std::string);
    int hasHunter();
    std::shared_ptr<Hunter> getRandHunter();
    bool shareEvidence(std::string);

    void addGhost(std::shared_ptr<Ghost>);
    std::shared_ptr<Ghost> removeGhost();
    bool hasGhost();

    void addEvidence(std::shared_ptr<Evidence>);
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