#include "Hunter.h"

Hunter::Hunter(std::string n, EvidenceType t) : name(n), type(t), fear(0), boredom(100), uniqueGhostly(0) {}

Hunter::~Hunter()
{
    room = nullptr;
}

void Hunter::addEvidence(std::shared_ptr<Evidence> e)
{
    evidence.insert(e);
    if (e->isGhostly())
        uniqueGhostly++;
}

void Hunter::setRoom(std::shared_ptr<Room> r)
{
    room = r;
}

std::shared_ptr<Evidence> Hunter::createEvidence()
{
    std::random_device dev;
    std::mt19937 rng(dev());

    int lower, upper;
    switch (type)
    {
    case EMF:
        lower = 0;
        upper = 4.7;
        break;
    case TEMPERATURE:
        lower = 0;
        upper = 27;
        break;
    case FINGERPRINTS:
        lower = 0;
        upper = 0;
        break;
    case SOUND:
        lower = 40;
        upper = 65;
        break;
    default:
        break;
    }

    std::uniform_real_distribution<float> valDist(lower, upper);
    float val = valDist(rng);
    return std::make_shared<Evidence>(type, val);
}

void Hunter::shareEvidence(std::shared_ptr<Hunter> h)
{
    for (const auto &e : evidence)
        if (e->isGhostly())
            h->addEvidence(e);
}

void Hunter::update()
{
    using namespace std::chrono_literals;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 2);

    std::cout << "Hunter " << name << " beginning in the " << room->getName() << ". Type: " << Evidence::typeToString(type) << std::endl;

    while (boredom > 0)
    {
        if (uniqueGhostly >= 3) // win condition
        {
            std::cout << name << " has collected 3 pieces of ghostly evidence and is leaving the building!" << std::endl;
            return;
        }
        if (room->hasGhost()) // special interactions while ghost is present
        {
            std::cout << name << " is in the " << room->getName() << " with the ghost!" << std::endl;
            if (fear < 100)
            {
                fear++;
                boredom = BOREDOM_MAX;
            }
            else
            {
                std::cout << name << " has gotten too scared and is leaving the building!" << std::endl;
                return;
            }
        }
        std::shared_ptr<Room> curr, next;
        switch (dist(rng))
        {
        case 0: // collect or create evidence
            if (room->lockRoom())
            {
                if (room->hasEvidence())
                {
                    if (room->shareEvidence(name))
                    {
                        std::cout << name << " has collected some GHOSTLY evidence!" << std::endl;
                        boredom = BOREDOM_MAX;
                    }
                    else
                        std::cout << name << " has collected some evidence." << std::endl;
                }
                else
                {
                    room->addEvidence(createEvidence());
                    std::cout << name << " has created some evidence and left it in the " << room->getName() << std::endl;
                }
                room->unlockRoom();
            }
            break;

        case 1: // move rooms
            curr = room;
            next = room->getRandRoom().lock();
            if (curr->lockRoom() && next->lockRoom())
            {
                next->addHunter(curr->removeHunter(name));
                setRoom(next);
                std::cout << name << " has moved from the " << curr->getName() << " to the " << next->getName() << std::endl;
            }
            next->unlockRoom();
            curr->unlockRoom();

            break;

        case 2: // share evidence
            if (room->lockRoom() && room->hasHunter() > 1)
            {
                std::shared_ptr<Hunter> temp = room->getRandHunter();
                while (temp->name == name)
                {
                    temp = room->getRandHunter();
                }
                shareEvidence(temp);

                std::cout << name << " has shared evidence with " << temp->name << std::endl;

                room->unlockRoom();
            }
            break;
        }
        boredom--;
        std::this_thread::sleep_for(3s);
    }
}

std::thread Hunter::spawn()
{
    return std::thread([this]
                       { update(); });
}

std::string &Hunter::getName()
{
    return name;
}

EvidenceType Hunter::getType()
{
    return type;
}

void Hunter::clear()
{
    room = nullptr;
}

bool Hunter::hasGhostly()
{
    return uniqueGhostly >= 3;
}

std::unordered_set<std::shared_ptr<Evidence>> Hunter::getEvidence()
{
    return evidence;
}

std::ostream &operator<<(std::ostream &o, Hunter &h)
{
    o << h.getName();
    return o;
}