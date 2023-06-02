#include "Hunter.h"

Hunter::Hunter(std::string n, EvidenceType t) : name(n), type(t) {}

Hunter::~Hunter() {}

void Hunter::addEvidence(std::shared_ptr<Evidence> e)
{
    evidence.insert(e);
}

void Hunter::setRoom(std::shared_ptr<Room> r)
{
    room = r;
}

std::shared_ptr<Evidence> Hunter::createEvidence()
{
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(NULL_EVIDENCE, 0);
    room->addEvidence(temp);
    return temp;
}