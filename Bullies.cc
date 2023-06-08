#include "Bullies.h"

Bullies::Bullies() : Ghost() {}

Bullies::~Bullies() {}

std::shared_ptr<Evidence> Bullies::createEvidence()
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
        type = FINGERPRINTS;
        break;

    case 2:
        type = SOUND;
        break;
    default:
        std::cout << "THIS SHOULDN HAPPEN (SRC:Bullies::createEvidence())" << std::endl;
    }

    float lower, upper;
    switch (type)
    {
    case EMF:
        lower = 47;
        upper = 50;
        break;
    case FINGERPRINTS:
        lower = 1;
        upper = 1;
        break;
    case SOUND:
        lower = 65;
        upper = 75;
        break;
    default:
        std::cout << "THIS SHOULDN HAPPEN (SRC:Bullies::createEvidence())" << std::endl;
    }

    std::uniform_real_distribution<float> valDist(lower, upper);
    float val = valDist(rng);
    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(type, val);
    room->addEvidence(temp);
    return temp;
}

std::ostream &Bullies::output(std::ostream &o)
{
    return o << "Bullies" << std::endl;
}