#ifndef BANSHEE_H
#define BANSHEE_H

#include "Ghost.h"

class Banshee : public Ghost
{
public:
    Banshee();
    virtual ~Banshee();
    virtual std::shared_ptr<Evidence>& createEvidence();
    virtual std::ostream &output(std::ostream &);
};

#endif