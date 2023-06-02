#include "Evidence.h"

Evidence::Evidence(EvidenceType t, float v) : type(t), value(v) {}

Evidence::~Evidence() {}

bool Evidence::isGhostly()
{
    switch (type)
    {
    case 0:
        return value >= 4.7 && value <= 5.0;
    case 1:
        return value >= -10.0 && value <= 1.0;
    case 2:
        return value == 1.0;
    case 3:
        return value >= 65.0 && value <= 75.0;
    default:
        std::cout << "THIS SHOULDNT HAPPEN" << std::endl;
        return false;
    }
}