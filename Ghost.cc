#include "Ghost.h"

Ghost::Ghost() : boredom(100) {}

Ghost::~Ghost()
{
    room = nullptr;
}

void Ghost::update()
{
    using namespace std::chrono_literals;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 2);
    int i = 0;
    while (boredom > 0)
    {
        std::cout << std::this_thread::get_id() << " itr: " << i++ << ", GHOST bordeom: " << boredom << std::endl;
        if (room->hasHunter())
        {
            if (dist1(rng) == 0)
            {
                if (room->lockRoom())
                {
                    createEvidence();
                    room->unlockRoom();
                }
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
                if (curr->lockRoom())
                {
                    if (next->lockRoom())
                    {
                        next->addGhost(curr->removeGhost());
                        setRoom(next);
                        next->unlockRoom();
                    }
                    curr->unlockRoom();
                }
                break;

            case 1:
                if (room->lockRoom())
                {
                    createEvidence();
                    room->unlockRoom();
                }
                break;

            case 2:
                break;
            }
        }

        if (!room->hasHunter())
            boredom--;

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

void Ghost::clear()
{
    room = nullptr;
}

std::ostream &operator<<(std::ostream &o, Ghost &g)
{
    return g.output(o);
}