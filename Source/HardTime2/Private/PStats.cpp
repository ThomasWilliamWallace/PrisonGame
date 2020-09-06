#include "PStats.hpp"
#include "Missions.h"
#include <algorithm>
#include "Constants.h"
#include <sstream>
#include "pLog.hpp"

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

void PStats::PrintStats()
{
	/*
	std::sstringstreams ss;
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
	pLog(ss);
	*/
}

PStats::PStats()
{
}