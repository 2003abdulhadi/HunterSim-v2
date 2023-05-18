#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <ostream>

#include "defs.h"

class Evidence
{
    friend std::ostream& operator<<(std::ostream& o, Evidence& e);

public:
    Evidence(EvidenceType, float);
    ~Evidence();
    bool isGhostly();

private:
    EvidenceType type;
    float value;
};

#endif