#include "Control.h"

Control::Control()
{
    building = std::make_unique<Building>();

    ghost = Ghost::makeRandGhost();

    hunters.insert(std::make_shared<Hunter>("Harry", EMF));
    hunters.insert(std::make_shared<Hunter>("Barry", TEMPERATURE));
    hunters.insert(std::make_shared<Hunter>("Bob", FINGERPRINTS));
    hunters.insert(std::make_shared<Hunter>("Ross", SOUND));
}

Control::~Control()
{
    building->clear();
    ghost = nullptr;
    hunters.clear();
    building = nullptr;
}

void Control::launch()
{

    building->initRooms();

    building->addGhost(ghost);
    auto ghostStart = building->getRandRoom();
    while (ghostStart->getName() == "Van")
        ghostStart = building->getRandRoom();
    ghost->setRoom(ghostStart);
    ghostStart->addGhost(ghost);

    auto van = building->getRoom("Van");
    for (const auto &h : hunters)
    {
        building->addHunter(h);
        van->addHunter(h);
        h->setRoom(van);
    }

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
            return;
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
    for (auto &h : hunters)
    {
        hunterThreads[i++] = h->spawn();
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    std::thread ghostThread = ghost->spawn();

    for (auto &t : hunterThreads)
        if (t.joinable())
            t.join();

    if (ghostThread.joinable())
        ghostThread.join();

    for (auto &h : hunters)
        if (h->hasGhostly())
        {
            std::cout << "Hunters have won" << std::endl;
            return;
        }

    std::cout << "Ghost has won" << std::endl;
}

void Control::test()
{
    auto room = building->getRoom("Van");
    for (int i = 0; i < 2; i++)
    {
        room->addEvidence(ghost->createEvidence());
        for (const auto &h : hunters)
        {
            room->addEvidence(h->createEvidence());
        }
    }

    for (auto &h : hunters)
    {
        room->shareEvidence(h->getName());
    }
}