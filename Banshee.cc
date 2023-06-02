#include "Banshee.h"

Banshee::Banshee() : Ghost() {}

Banshee::~Banshee() {}

std::shared_ptr<Evidence> Banshee::createEvidence()
{
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(NULL_EVIDENCE, 0);
    room->addEvidence(temp);
    return temp;
}

std::ostream& Banshee::output(std::ostream& o)
{
    return o << "Banshee" <<std::endl;
}