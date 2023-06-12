#include "Hunter.h"

Hunter::Hunter(std::string n, EvidenceType t) : name(n), type(t), boredom(100), uniqueGhostly(0) {}

Hunter::~Hunter() {}

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
    std::uniform_real_distribution<float> dist(lower, upper);

    float result = dist(rng);

    std::shared_ptr<Evidence> temp = std::make_shared<Evidence>(type, result);
    room->addEvidence(temp);
    return temp;
}

void Hunter::sharedEvidence(std::shared_ptr<Hunter> h)
{
    for (const auto &e : evidence)
        if (e->isGhostly())
            h->addEvidence(e);
}

void Hunter::update()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 2);
    int i = 0;
    std::cout << std::this_thread::get_id << ", bordeom: " << boredom << std::endl;
    while (boredom > 0)
    {
        std::cout << std::this_thread::get_id << " itr: " << i++ << std::endl;
        if (uniqueGhostly >= 3)
            return;
        if (room->hasGhost())
        {
            if (fear < 100)
            {
                fear++;
                boredom = BOREDOM_MAX;
            }
            else
            {
                std::cout << "RAN AWAY" << std::endl;
                return;
            }
        }
        std::shared_ptr<Room> curr;
        std::shared_ptr<Room> next;
        switch (dist(rng))
        {

        case 0:
            while (!room->lockRoom())
            {
            }
            if (room->hasEvidence())
            {
                if (room->shareEvidence(name))
                    boredom = BOREDOM_MAX;
            }
            else
                createEvidence();
            break;

        case 1:
            curr = room;
            next = room->getRandRoom().lock();
            while (!(curr->lockRoom() && next->lockRoom()))
            {
            }
            next->addHunter(curr->removeHunter(name));
            setRoom(next);
            curr->unlockRoom();
            next->unlockRoom();
            break;

        case 2:
            // communiucating
            if (room->hasHunter() > 1)
            {
                std::shared_ptr<Hunter> temp;
                do
                {
                    temp = room->getRandHunter().lock();
                } while (temp.get() == this);
                sharedEvidence(temp);
            }
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
    std::cout << "DONE" << std::endl;
}

std::thread Hunter::spawn()
{
    return std::thread([this] {update();});
}

std::string &Hunter::getName()
{
    return name;
}

EvidenceType Hunter::getType()
{
    return type;
}

std::ostream &operator<<(std::ostream &o, Hunter &h)
{
    o << h.getName();
    return o;
}