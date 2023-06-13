#ifndef BANSHEE_H
#define BANSHEE_H

#include "Ghost.h"

/// @brief Banshee is an implementation of ghost that only creates EMF, TEMPERATURE, and SOUND evidence
class Banshee : public Ghost
{
public:
    Banshee();
    virtual ~Banshee();
    virtual std::shared_ptr<Evidence> createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif