#include "Poltergeist.h"

Poltergeist::Poltergeist() : Ghost() {}

Poltergeist::~Poltergeist() {}

std::shared_ptr<Evidence> Poltergeist::createEvidence()
{
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(NULL_EVIDENCE, 0);
    room->addEvidence(temp);
    return temp;
}

std::ostream& Poltergeist::output(std::ostream& o)
{
    return o << "Poltergeist" <<std::endl;
}