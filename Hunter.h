#ifndef HUNTER_H
#define HUNTER_H

#include "defs.h"
#include "Room.h"
#include "Evidence.h"

/// @brief Hunter class defines a hunter with methods to intreact with the room and to create evidence
/// The update() method defines the main game loop for a hunter
class Hunter
{
    friend std::ostream &operator<<(std::ostream &, Hunter &);

public:
    Hunter(std::string, EvidenceType);
    ~Hunter();
    void shareEvidence(std::shared_ptr<Hunter> h);
    void update();
    std::thread spawn();
    std::string &getName();
    EvidenceType getType();
    bool hasGhostly();
    void setRoom(std::shared_ptr<Room>);

    void addEvidence(std::shared_ptr<Evidence>);
    std::shared_ptr<Evidence> createEvidence();
    std::unordered_set<std::shared_ptr<Evidence>> getEvidence();

    void clear();

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