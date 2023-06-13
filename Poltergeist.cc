#include "Poltergeist.h"

Poltergeist::Poltergeist() : Ghost() {}

Poltergeist::~Poltergeist() {}

std::shared_ptr<Evidence> Poltergeist::createEvidence()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> typeDist(0, 2);

    EvidenceType type;
    switch (typeDist(rng))
    {
    case 0:
        type = EMF;
        break;

    case 1:
        type = TEMPERATURE;
        break;

    case 2:
        type = FINGERPRINTS;
        break;
    }

    float lower, upper;
    switch (type)
    {
    case EMF:
        lower = 47;
        upper = 50;
        break;
    case TEMPERATURE:
        lower = -10;
        upper = 0;
        break;
    case FINGERPRINTS:
        lower = 1;
        upper = 1;
        break;
    }

    std::uniform_real_distribution<float> valDist(lower, upper);
    float val = valDist(rng);
    return std::make_shared<Evidence>(type, val);
}

std::ostream &Poltergeist::output(std::ostream &o)
{
    return o << "Poltergeist";
}