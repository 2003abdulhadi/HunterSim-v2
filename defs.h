#ifndef DEFS_H
#define DEFS_H

#define MAX_STR 64
#define FEAR_RATE 1
#define MAX_FEAR 100
#define MAX_HUNTERS 4
#define USLEEP_TIME 50000
#define BOREDOM_MAX 99

#include <unordered_set>
#include <set>
#include <unordered_map>
#include <string>
#include <ostream>
#include <memory>
#include <iostream>

typedef enum
{
    EMF,
    TEMPERATURE,
    FINGERPRINTS,
    SOUND
} EvidenceType;

#endif