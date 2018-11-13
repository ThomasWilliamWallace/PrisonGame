#pragma once
//
//  HTNWorldState.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

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
class ActorItem;
class World;
class AAICharacterC;

class HTNWorldState
{
public:
	std::vector<int> m_v;
	std::vector< SimActorItem* > m_items;
	AAICharacterC* m_ptrToSelf;
	SimActorItem* m_itemCarriedPtr;
	std::vector<bool> m_attackers;
	std::vector<Locations> m_playerLocations;
	MissionClass m_missionClass;
	HTNWorldState(HTNWorldState &ws2);
	HTNWorldState(AAICharacterC* aiCharacterC);
	~HTNWorldState();
	void CopyFrom(HTNWorldState &ws2);
};