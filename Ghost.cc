#include "Ghost.h"

Ghost::Ghost() : boredom(100) {}

Ghost::~Ghost() {}

void Ghost::update()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 2);
    int i = 0;
    std::cout << std::this_thread::get_id << ", bordeom: " << boredom << std::endl;
    while (boredom > 0)
    {
        std::cout << std::this_thread::get_id << " itr: " << i++ << std::endl;
        if (room->hasHunter())
        {
            if (dist1(rng) == 0)
            {
                while (!room->lockRoom())
                {
                }
                createEvidence();
                room->unlockRoom();
            }
        }
        else
        {
            std::shared_ptr<Room> curr;
            std::shared_ptr<Room> next;

            switch (dist2(rng))
            {
            case 0:
                curr = room;
                next = room->getRandRoom().lock();
                while (!(curr->lockRoom() && next->lockRoom()))
                {
                }
                next->addGhost(curr->removeGhost());
                setRoom(next);
                curr->unlockRoom();
                next->unlockRoom();
                break;

            case 1:
                while (!room->lockRoom())
                {
                }
                createEvidence();
                room->unlockRoom();
                break;

            case 2:
                break;
            }
        }

        if (!room->hasHunter())
            boredom--;

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
    std::cout << "DONE" << std::endl;
}

std::thread Ghost::spawn()
{
    return std::thread([this]
                       { update(); });
}

void Ghost::setRoom(std::shared_ptr<Room> r)
{
    room = r;
}

int &Ghost::getBoredom()
{
    return boredom;
}

std::shared_ptr<Ghost> Ghost::makeRandGhost()
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

std::ostream &operator<<(std::ostream &o, Ghost &g)
{
    return g.output(o);
}