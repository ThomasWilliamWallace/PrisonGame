//
//  Stats.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 24/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Stats.hpp"
#include "Missions.hpp"
#include <algorithm>
using namespace std;

//TODO write an exponentially decreasing add/subtract function, to adjust stats whilst keeping them within 0-100.
double transformStat(double inputStat)
{
    return std::max(std::min(inputStat, 100.0), 0.0);
}

double Stats::getHealth()
{
    return health;
}

double Stats::getSanity()
{
    return sanity;
}

double Stats::getStrength()
{
    return strength;
}

double Stats::getAgility()
{
    return agility;
}

double Stats::getIntelligence()
{
    return intelligence;
}

double Stats::getCharisma()
{
    return charisma;
}

double Stats::getReputation()
{
    return reputation;
}

double Stats::getRespect()
{
    return respect;
}

void Stats::deltaHealth(double delta)
{
    health = transformStat(health + delta);
}

void Stats::deltaSanity(double delta)
{
    sanity = transformStat(sanity + delta);
}

void Stats::deltaStrength(double delta)
{
    strength = transformStat(strength + delta);
}

void Stats::deltaAgility(double delta)
{
    agility = transformStat(agility + delta);
}

void Stats::deltaIntelligence(double delta)
{
    intelligence = transformStat(intelligence + delta);
}

void Stats::deltaCharisma(double delta)
{
    charisma = transformStat(charisma + delta);
}

void Stats::deltaReputation(double delta)
{
    reputation = transformStat(reputation + delta);
}

void Stats::deltaRespect(double delta)
{
    respect = transformStat(respect + delta);
}

void Stats::PrintStats()
{
    std::cout << "*** STATS ***\n";
    std::cout << "health=" << FormatDouble(getHealth()) << "\n";
    std::cout << "sanity=" << FormatDouble(getSanity()) << "\n";
    std::cout << "strength=" << FormatDouble(getStrength()) << "\n";
    std::cout << "agility=" << FormatDouble(getAgility()) << "\n";
    std::cout << "intelligence=" << FormatDouble(getIntelligence()) << "\n";
    std::cout << "charisma=" << FormatDouble(getCharisma()) << "\n";
    std::cout << "reputation=" << FormatDouble(getReputation()) << "\n";
    std::cout << "respect=" << FormatDouble(getRespect()) << "\n";
    std::cout << "\n";
    std::cout << "loyalty=" << loyalty << "\n";
    std::cout << "traitorous=" << traitorous << "\n";
    std::cout << "aggression=" << aggression << "\n";
    std::cout << "sociability=" << sociability << "\n";
    std::cout << "curiosity=" << curiosity << "\n";
    std::cout << "risktaking=" << risktaking << "\n";
    std::cout << "leader=" << leader << "\n";
    std::cout << "follower=" << follower << "\n";
    std::cout << "herdfollower=" << herdfollower << "\n";
    std::cout << "strongwilled=" << strongwilled << "\n";
    std::cout << "proud=" << proud << "\n";
    std::cout << "forgiving=" << forgiving << "\n";
    std::cout << "discreet=" << discreet << "\n";
    std::cout << "\n";
}

Stats::Stats()
{
}