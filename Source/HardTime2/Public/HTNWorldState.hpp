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

	punches,
	evading,

	location,
	last
};

std::string WorldEToString(WorldE worldE);

class Player;
class SimActorItem;
class World;

class HTNWorldState
{
    bool m_inTheRoom[c_playerCount];
public:
	std::vector<int> m_v;
	std::vector< SimActorItem* > m_items;
	Player* m_ptrToSelf;
	SimActorItem* m_itemCarriedPtr;
	std::vector<bool> m_attackers;
	std::vector<ELocations> m_playerLocations;
    bool IsInTheRoom(Player* playerPtr);
	MissionClass m_missionClass;
	HTNWorldState(HTNWorldState &ws2);
	HTNWorldState(Player* playerPtr, World &world);
	~HTNWorldState();
	void CopyFrom(HTNWorldState &ws2);
    void Print();
};
