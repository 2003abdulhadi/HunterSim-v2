#include "Bullies.h"

Bullies::Bullies() : Ghost() {}

Bullies::~Bullies() {}

std::shared_ptr<Evidence> Bullies::createEvidence()
{
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(NULL_EVIDENCE, 0);
    room->addEvidence(temp);
    return temp;
}

std::ostream& Bullies::output(std::ostream& o)
{
    return o << "Bullies" <<std::endl;
}