#include "Control.h"

Control::Control()
{
    building = std::make_unique<Building>();
    ghost = makeRandGhost();
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

    auto ghostStart = building->getRandRoom();
    while(ghostStart->getName() == "Van")
        ghostStart = building->getRandRoom();
    ghost->setRoom(ghostStart);
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
            break;
        case 2:
            std::cout << *ghost << std:: endl;
            for(auto &h : hunters)
                std::cout << *h << std::endl;
            break;
        case 3:
            run();
            break;
        default:
            break;
        }
    }
}

std::shared_ptr<Ghost> Control::makeRandGhost()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> typeDist(0, 3);
    switch (typeDist(rng))
    {
    case 0:
        return std::make_shared<Banshee>();
    case 1:
        return std::make_shared<Bullies>();
    case 2:
        return std::make_shared<Phantom>();
    case 3:
        return std::make_shared<Poltergeist>();
    }
}

void Control::run()
{
    std::thread hunterThreads[MAX_HUNTERS];
    int i = 0;
    for(auto& h : hunters)
    {
        hunterThreads[i++] = h->spawn();
    }
    std::thread ghostThread = ghost->spawn();

    for(auto& t : hunterThreads)
        if(t.joinable())
            t.join();
    if(ghostThread.joinable())
        ghostThread.join();
}