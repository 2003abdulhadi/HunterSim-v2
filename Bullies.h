#ifndef BULLIES_H
#define BULLIES_H

#include "Ghost.h"

/// @brief Bullies is an implementation of ghost that only creates EMF, FINGERPRINT, and SOUND evidence
class Bullies : public Ghost
{
public:
    Bullies();
    virtual ~Bullies();
    virtual std::shared_ptr<Evidence> createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif