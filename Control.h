#ifndef CONTROL_H
#define CONTROL_H

#include "defs.h"
#include "Building.h"
#include "Hunter.h"
#include "Ghost.h"
#include "Banshee.h"
#include "Poltergeist.h"
#include "Bullies.h"
#include "Phantom.h"
#include "View.h"

class Control
{
public:
    Control();
    ~Control();
    void launch();
private:
    std::shared_ptr<Ghost> makeRandGhost();
    void run();
    void test();
    View view;
    std::unique_ptr<Building> building;
    std::unordered_set<std::shared_ptr<Hunter>> hunters;
    std::shared_ptr<Ghost> ghost;
};

#endif