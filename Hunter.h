#ifndef HUNTER_H
#define HUNTER_H

#include "defs.h"
#include "Room.h"

class Hunter
{
public:
    Hunter(std::string, EvidenceType);
    ~Hunter();
    void addEvidence(std::shared_ptr<Evidence>);
    void setRoom(std::shared_ptr<Room>);
    std::shared_ptr<Evidence>& createEvidence();
private:
    std::string name;
    EvidenceType type;
    int fear;
    int boredom;
    std::shared_ptr<Room> room;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
};

#endif