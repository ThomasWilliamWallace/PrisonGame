#include "PStats.hpp"
#include "Missions.hpp"
#include <algorithm>
#include "Constants.hpp"
using namespace std;

//TODO write an exponentially decreasing add/subtract function, to adjust stats whilst keeping them within 0-100.
double transformStat(double inputStat)
{
    return std::max(std::min(inputStat, 100.0), 0.0);
}

double PStats::getHealth()
{
    return health;
}

double PStats::getSanity()
{
    return sanity;
}

double PStats::getStrength()
{
    return strength;
}

double PStats::getAgility()
{
    return agility;
}

double PStats::getIntelligence()
{
    return intelligence;
}

double PStats::getCharisma()
{
    return charisma;
}

double PStats::getReputation()
{
    return reputation;
}

double PStats::getRespect()
{
    return respect;
}

void PStats::deltaHealth(double delta)
{
    health = transformStat(health + delta);
}

void PStats::deltaSanity(double delta)
{
    sanity = transformStat(sanity + delta);
}

void PStats::deltaStrength(double delta)
{
    strength = transformStat(strength + delta);
}

void PStats::deltaAgility(double delta)
{
    agility = transformStat(agility + delta);
}

void PStats::deltaIntelligence(double delta)
{
    intelligence = transformStat(intelligence + delta);
}

void PStats::deltaCharisma(double delta)
{
    charisma = transformStat(charisma + delta);
}

void PStats::deltaReputation(double delta)
{
    reputation = transformStat(reputation + delta);
}

void PStats::deltaRespect(double delta)
{
    respect = transformStat(respect + delta);
}

PStats::PStats()
{
}