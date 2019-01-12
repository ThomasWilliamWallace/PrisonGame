#pragma once

#include <vector>
#include <iostream>
#include "Locations.h"
#include "Missions.hpp"
#include "Constants.hpp"
#include "PlatformSpecific.hpp"

enum WorldE
{
	health,
	sanity,
	strength,
	agility,
	intelligence,

	evading,

	location,
	last
};

std::string WorldEToString(WorldE worldE);

class UPlayerData;
class SimActorItem;
class USimWorld;

class HTNWorldState
{
public:
    UPlayerData* m_ptrToSelf;
    int m_health;
    int m_sanity;
    int m_strength;
    int m_agility;
    int m_intelligence;
    int m_evading;
    ELocations m_location;
	std::vector< SimActorItemPtr > m_items;
	SimActorItemPtr m_itemCarriedPtr;
	std::vector< UPlayerData* > m_attackers;
	std::vector< ELocations > m_playerLocations;
    std::vector< UPlayerData* > m_playersInTheRoom;
    bool IsInTheRoom(UPlayerData* playerPtr);
	MissionClass m_missionClass;
	HTNWorldState(HTNWorldState &ws2);
	HTNWorldState(UPlayerData* playerPtr, USimWorld &world);
    HTNWorldState& operator=(const HTNWorldState& ws2);
    void Print();
};
