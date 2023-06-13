#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <ostream>

#include "defs.h"

/// @brief Evidence class defines a simple data type with a name and a value
class Evidence
{
    friend std::ostream &operator<<(std::ostream &o, Evidence &e);

public:
    Evidence(EvidenceType, float);
    ~Evidence();
    bool isGhostly();
    EvidenceType getType();
    static std::string typeToString(EvidenceType);

private:
    EvidenceType type;
    float value;
};

#endif