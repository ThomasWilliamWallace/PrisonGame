#include "PStats.h"
#include <algorithm>
#include "Constants.h"
#include <sstream>
#include "pLog.h"

UPStats::UPStats(const FObjectInitializer& ObjectInitializer):
    Super(ObjectInitializer)
{

    health = 70;
    sanity = 70;

    strength = 50;
    agility = 80;
    intelligence = 30;
    charisma = 40;
    reputation = 20;
    respect = 60;
    
    loyalty = rand() % 100;
    traitorous = rand() % 100;
    aggression = rand() % 100;
    sociability = rand() % 100;
    curiosity = rand() % 100;
    risktaking = rand() % 100;
    leader = rand() % 100;
    follower = rand() % 100;
    herdfollower = rand() % 100;
    strongwilled = rand() % 100;
    proud = rand() % 100;
    forgiving = rand() % 100;
    discreet = rand() % 100;
}

double UPStats::getHealth()
{
    return health;
}

double UPStats::getSanity()
{
    return sanity;
}

double UPStats::getStrength()
{
    return strength;
}

double UPStats::getAgility()
{
    return agility;
}

double UPStats::getIntelligence()
{
    return intelligence;
}

double UPStats::getCharisma()
{
    return charisma;
}

double UPStats::getReputation()
{
    return reputation;
}

double UPStats::getRespect()
{
    return respect;
}

void UPStats::deltaHealth(double delta)
{
    health = transformStat(health + delta);
}

void UPStats::deltaSanity(double delta)
{
    sanity = transformStat(sanity + delta);
}

void UPStats::deltaStrength(double delta)
{
    strength = transformStat(strength + delta);
}

void UPStats::deltaAgility(double delta)
{
    agility = transformStat(agility + delta);
}

void UPStats::deltaIntelligence(double delta)
{
    intelligence = transformStat(intelligence + delta);
}

void UPStats::deltaCharisma(double delta)
{
    charisma = transformStat(charisma + delta);
}

void UPStats::deltaReputation(double delta)
{
    reputation = transformStat(reputation + delta);
}

void UPStats::deltaRespect(double delta)
{
    respect = transformStat(respect + delta);
}

void UPStats::PrintStats()
{
    std::stringstream ss;
    ss << "*** STATS ***\n";
    ss << "health=" << FormatDouble(getHealth()) << "\n";
    ss << "sanity=" << FormatDouble(getSanity()) << "\n";
    ss << "strength=" << FormatDouble(getStrength()) << "\n";
    ss << "agility=" << FormatDouble(getAgility()) << "\n";
    ss << "intelligence=" << FormatDouble(getIntelligence()) << "\n";
    ss << "charisma=" << FormatDouble(getCharisma()) << "\n";
    ss << "reputation=" << FormatDouble(getReputation()) << "\n";
    ss << "respect=" << FormatDouble(getRespect()) << "\n";
    ss << "\n";
    ss << "loyalty=" << loyalty << "\n";
    ss << "traitorous=" << traitorous << "\n";
    ss << "aggression=" << aggression << "\n";
    ss << "sociability=" << sociability << "\n";
    ss << "curiosity=" << curiosity << "\n";
    ss << "risktaking=" << risktaking << "\n";
    ss << "leader=" << leader << "\n";
    ss << "follower=" << follower << "\n";
    ss << "herdfollower=" << herdfollower << "\n";
    ss << "strongwilled=" << strongwilled << "\n";
    ss << "proud=" << proud << "\n";
    ss << "forgiving=" << forgiving << "\n";
    ss << "discreet=" << discreet << "\n";
    ss << "\n";
    pLog(ss, true);
}

//TODO write an exponentially decreasing add/subtract function, to adjust stats whilst keeping them within 0-100.
double transformStat(double inputStat)
{
    return std::max(std::min(inputStat, 100.0), 0.0);
}