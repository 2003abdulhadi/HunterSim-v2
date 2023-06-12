#include "Control.h"

Control::Control()
{
    building = std::make_unique<Building>();
    building->initRooms();

    ghost = Ghost::makeRandGhost();

    building->addGhost(ghost);
    auto ghostStart = building->getRandRoom();
    while(ghostStart->getName() == "Van")
        ghostStart = building->getRandRoom();
    ghost->setRoom(ghostStart);
    ghostStart->addGhost(ghost);

    hunters.insert(std::make_shared<Hunter>("Harry", EMF));
    hunters.insert(std::make_shared<Hunter>("Barry", TEMPERATURE));
    hunters.insert(std::make_shared<Hunter>("Bob", FINGERPRINTS));
    hunters.insert(std::make_shared<Hunter>("Ross", SOUND));
    auto van = building->getRoom("Van");
    for(const auto& h : hunters)
    {
        building->addHunter(h);
        van->addHunter(h);
        h->setRoom(van);
    }
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
            building->printCharacters();
            break;
        case 3:
            run();
            break;
        case 4:
            test();
            break;
        default:
            break;
        }
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

void Control::test()
{
    for(const auto& h : hunters)
    {
        std::cout << h->getName() << std::endl;
        std::cout << h->getType() << std::endl;
        return;
    }

    // std::cout << ghost->getBoredom() << std::endl;
    // for(int i = 0; i < 10; i++)
    // {   
    //     auto& r = building->getRandRoom();
    //     ghost->setRoom(r);
    // }
    // while(true)
    // {   
    //     auto& r = building->getRandRoom();
    //     ghost->setRoom(r);
    //     if(r->getName() == "Van")
    //         break;
    // }
    // building->printCharacters();
    // building->printRooms();
}