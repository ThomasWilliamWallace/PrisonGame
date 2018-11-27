#pragma once

#include <vector>
#include <iostream>
#include "Locations.h"
#include "Missions.hpp"
#include "Constants.hpp"

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
    bool m_inTheRoom[c_playerCount];
public:
	std::vector<int> m_v;
	std::vector< SimActorItem* > m_items;
	UPlayerData* m_ptrToSelf;
	SimActorItem* m_itemCarriedPtr;
	std::vector<bool> m_attackers;
	std::vector<ELocations> m_playerLocations;
    std::vector< UPlayerData* > m_playersInTheRoom;
    bool IsInTheRoom(UPlayerData* playerPtr);
	MissionClass m_missionClass;
	HTNWorldState(HTNWorldState &ws2);
	HTNWorldState(UPlayerData* playerPtr, USimWorld &world);
	~HTNWorldState();
	void CopyFrom(HTNWorldState &ws2);
    void Print();
};
