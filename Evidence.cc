#include "Evidence.h"

Evidence::Evidence(EvidenceType t, float v) : type(t), value(v) {}

Evidence::~Evidence() {}

bool Evidence::isGhostly()
{
    switch (type)
    {
    case EMF:
        return value >= 4.7 && value <= 5.0;
    case TEMPERATURE:
        return value >= -10.0 && value <= 1.0;
    case FINGERPRINTS:
        return value == 1.0;
    case SOUND:
        return value >= 65.0 && value <= 75.0;
    default:
        return false;
    }
}

EvidenceType Evidence::getType()
{
    return type;
}

std::string Evidence::typeToString(EvidenceType e)
{
    switch (e)
    {
    case EMF:
        return "EMF";
    case TEMPERATURE:
        return "TEMPERATURE";
    case SOUND:
        return "SOUND";
    case FINGERPRINTS:
        return "FINGERPRINTS";
    default:
        return "";
    }
}

std::ostream &operator<<(std::ostream &o, Evidence &e)
{
    return o << Evidence::typeToString(e.type) << " Evidence: " << e.value;
}
