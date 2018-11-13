#pragma once

#include "ActorItem.hpp"

enum class Missions
{
	noMission,
	increaseStrength,
	increaseAgility,
	increaseIntelligence,
	bringItemToRoom
};

class AAICharacterC;

class MissionClass
{
public:
	Missions m_mission;
	double m_objective; //objective for stat increase missions
	int m_targetPlayerIndex;
	AAICharacterC* m_owner;
	ItemType m_itemType;
	LocationClass m_locationClass;
	std::string MissionName();
	MissionClass(Missions mission, double objective, AAICharacterC* owner);
	MissionClass(Missions mission, AAICharacterC* owner, ItemType itemE, Locations location);
	MissionClass();
	MissionClass(const MissionClass& missionClass);
	MissionClass(AAICharacterC* aiCharacterC);
	bool IsMissionComplete();
};

Missions GetRandomMission();