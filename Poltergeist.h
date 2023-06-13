#ifndef POLTERGEIST_H
#define POLTERGEIST_H

#include "Ghost.h"

/// @brief Poltergeist is an implementation of ghost that only creates EMF, TEMPERATURE, and FINGERPRINT evidence
class Poltergeist : public Ghost
{
public:
    Poltergeist();
    virtual ~Poltergeist();
    virtual std::shared_ptr<Evidence> createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif