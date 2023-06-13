#ifndef PHANTOM_H
#define PHANTOM_H

#include "Ghost.h"

/// @brief Phantom is an implementation of ghost that only creates TEMPERATURE, FINGERPRINT, and SOUND evidence
class Phantom : public Ghost
{
public:
    Phantom();
    virtual ~Phantom();
    virtual std::shared_ptr<Evidence> createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif