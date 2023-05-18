#ifndef POLTERGEIST_H
#define POLTERGEIST_H

#include "Ghost.h"

class Poltergeist : public Ghost
{
public:
    Poltergeist();
    virtual ~Poltergeist();
    virtual std::shared_ptr<Evidence>& createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif