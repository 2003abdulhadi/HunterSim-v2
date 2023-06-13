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

    std::cout << "The " << *this << " is beginning in the " << room->getName() << std::endl;

    while (boredom > 0)
    {
        if (room->hasHunter())
        {
            std::cout << *this << " is in the " << room->getName() << " with a Hunter!" << std::endl;
            if (dist1(rng) == 0)
            {
                if (room->lockRoom())
                {
                    room->addEvidence(createEvidence());
                    std::cout << *this << " has dropped some spooky evidence in the " << room->getName() << std::endl;
                    room->unlockRoom();
                }
            }
            else
                std::cout << *this << " is just floating in the " << room->getName() << " with a hunter... menacingly" << std::endl;
        }
        else
        {
            std::shared_ptr<Room> curr, next;

            switch (dist2(rng))
            {
            case 0: // switch room;
                curr = room;
                next = room->getRandRoom().lock();
                if (curr->lockRoom() && next->lockRoom())
                {
                    next->addGhost(curr->removeGhost());
                    setRoom(next);
                    std::cout << *this << " has moved from the " << curr->getName() << " to the " << next->getName() << std::endl;
                }
                next->unlockRoom();
                curr->unlockRoom();

                break;

            case 1:
                if (room->lockRoom())
                {
                    room->addEvidence(createEvidence());
                    std::cout << *this << " has dropped some creepy evidence in the " << room->getName() << std::endl;
                    room->unlockRoom();
                }
                break;

            case 2:
                std::cout << *this << " is just floating in the " << room->getName() << "... menacingly" << std::endl;
                break;
            }
        }

        if (room->hasHunter() != 0)
            boredom--;

        std::this_thread::sleep_for(3s);
    }
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
    default:
        return std::make_shared<Banshee>();
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