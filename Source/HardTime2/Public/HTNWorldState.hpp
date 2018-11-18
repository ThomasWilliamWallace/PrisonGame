#pragma once

#include <vector>
#include "Locations.hpp"
#include "Missions.hpp"

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
public:
	std::vector<int> m_v;
	std::vector< SimActorItem* > m_items;
	Player* m_ptrToSelf;
	SimActorItem* m_itemCarriedPtr;
	std::vector<bool> m_attackers;
	std::vector<Locations> m_playerLocations;
	MissionClass m_missionClass;
	HTNWorldState(HTNWorldState &ws2);
	HTNWorldState(Player* playerPtr, World &world);
	~HTNWorldState();
	void CopyFrom(HTNWorldState &ws2);
    void Print();
};
