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

/// @brief Control class deines the main control flow of the program via the launch() method
/// the run method is used to spawn the threads for the hunters and ghost
/// the test method is used to test functionality
class Control
{
public:
    Control();
    ~Control();
    void launch();

private:
    void run();
    void test();

    View view;
    std::unique_ptr<Building> building;
    std::unordered_set<std::shared_ptr<Hunter>> hunters;
    std::shared_ptr<Ghost> ghost;
};

#endif