#include "Phantom.h"

Phantom::Phantom() : Ghost() {}

Phantom::~Phantom() {}

std::shared_ptr<Evidence> Phantom::createEvidence()
{
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(NULL_EVIDENCE, 0);
    room->addEvidence(temp);
    return temp;
}

std::ostream& Phantom::output(std::ostream& o)
{
    return o << "Phantom" <<std::endl;
}