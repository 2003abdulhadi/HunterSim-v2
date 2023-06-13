#ifndef HUNTER_H
#define HUNTER_H

#include "defs.h"
#include "Room.h"
#include "Evidence.h"

class Hunter
{
    friend std::ostream &operator<<(std::ostream &, Hunter &);

public:
    Hunter(std::string, EvidenceType);
    ~Hunter();
    void addEvidence(std::shared_ptr<Evidence>);
    void setRoom(std::shared_ptr<Room>);
    std::shared_ptr<Evidence> createEvidence();
    void shareEvidence(std::shared_ptr<Hunter> h);
    void update();
    std::thread spawn();
    std::string &getName();
    EvidenceType getType();
    void clear();
    bool hasGhostly();
    std::unordered_set<std::shared_ptr<Evidence>> getEvidence();
private:
    std::string name;
    EvidenceType type;
    int fear;
    int boredom;
    std::shared_ptr<Room> room;
    std::unordered_set<std::shared_ptr<Evidence>> evidence;
    int uniqueGhostly;
};

#endif