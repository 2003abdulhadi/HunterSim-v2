#include "Control.h"

Control::Control()
{
    building = std::make_unique<Building>();
    ghost = std::make_shared<Banshee>();
    std::shared_ptr<Hunter> harry = std::make_shared<Hunter>("Harry", EMF);
    std::shared_ptr<Hunter> barry = std::make_shared<Hunter>("Barry", TEMPERATURE);
    std::shared_ptr<Hunter> bob = std::make_shared<Hunter>("Bob", FINGERPRINTS);
    std::shared_ptr<Hunter> ross = std::make_shared<Hunter>("Ross", SOUND);

    building->addGhost(ghost);

    building->addHunter(harry);
    building->addHunter(barry);
    building->addHunter(bob);
    building->addHunter(ross);

    building->initRooms();
    auto van = building->getRoom("Van");
    van->addHunter(harry);
    van->addHunter(barry);
    van->addHunter(bob);
    van->addHunter(ross);

    auto kitchen = building->getRoom("Kitchen");
    kitchen->addGhost(ghost);
}

Control::~Control() {}

void Control::launch()
{
    int i = -1;
    while (i)
    {
        view.display(i);
        switch (i)
        {
        case 0:
            return;
        case 1:
            building->printRooms();
        default:
            break;
        }
    }
    
}