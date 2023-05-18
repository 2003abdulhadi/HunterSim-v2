#ifndef CONTROL_H
#define CONTROL_H

#include "defs.h"
#include "Building.h"
#include "Hunter.h"
#include "Ghost.h"

class Control
{
public:
    Control();
    ~Control();
    void launch();
private:
    std::unique_ptr<Building> building;
    std::unordered_set<std::shared_ptr<Hunter>> hunters;
    std::shared_ptr<Ghost> ghost;
};

#endif