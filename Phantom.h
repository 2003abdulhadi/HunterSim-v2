#ifndef PHANTOM_H
#define PHANTOM_H

#include "Ghost.h"

class Phantom : public Ghost
{
public:
    Phantom();
    virtual ~Phantom();
    virtual std::shared_ptr<Evidence> createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif