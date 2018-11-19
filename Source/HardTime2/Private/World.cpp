#include "World.hpp"
#include "ActorItem.h"
#include <sstream>
#include "pLog.hpp"

World::World()
{
    weightsOccupied  = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    bedOccupied      = nullptr;
}

void World::Clean()
{
    bedOccupied      = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    weightsOccupied  = nullptr;
}

void World::WorldEffects(Player player[], int frame)
{
    if (bedOccupied != nullptr)
    {
        bedOccupied->pStats.deltaHealth(1);
    }
    if (circuitsOccupied != nullptr)
    {
        circuitsOccupied->pStats.deltaAgility(1);
    }
    if (studyOccupied != nullptr)
    {
        studyOccupied->pStats.deltaIntelligence(1);
    }
    if (weightsOccupied != nullptr)
    {
        weightsOccupied->pStats.deltaStrength(1);
        weightsOccupied->narrative = "weightlift; strength = " + FormatDouble(weightsOccupied->pStats.getStrength());
    }
}

void World::PrintWorld(Player player[])
{
	/*
	std::sstringstream ss;
    ss << "*** WORLD DATA ***\n";
    ss << "weightsOccupied=" << CharacterName(weightsOccupied) << "\n";
    ss << "circuitsOccupied=" << CharacterName(circuitsOccupied) << "\n";
    ss << "studyOccupied=" << CharacterName(studyOccupied) << "\n";
    ss << "bedOccupied=" << CharacterName(bedOccupied) << "\n";
    ss << "\n";
    for (auto &item : items)
    {
        ss << item->ToString() << " is in the " << item->m_locationClass.ToString() << ".\n";
    }
    ss << "\n";
	pLog(ss.str());
	*/
}

void World::FullDisplay(Player player[])
{
	/*
    PrintWorld(player);
    
    for (int playerIndex = 0; playerIndex < c_playerCount; playerIndex++)
    {
        player[playerIndex].PrintPlayer(player);
    }
	*/
}
