#pragma once

#include <iostream>
#include "ActorItem.h"

enum class Missions
{
	noMission,
	increaseStrength,
	increaseAgility,
	increaseIntelligence,
	bringItemToRoom
};

class Player;
class World;

class MissionClass
{
public:
	Missions m_mission;
	Player* m_owner;
	double m_objective; //objective for stat increase missions
	EItemType m_itemType;
	LocationClass m_locationClass;
	std::string MissionName();
	MissionClass(Missions mission, Player* owner, double objective);
	MissionClass(Missions mission, Player* owner, EItemType itemE, Locations location);
	MissionClass();
	MissionClass(const MissionClass& missionClass);
	MissionClass(Player* owner);
	bool IsMissionComplete(World &world);
    std::string MissionNarrative();
};

Missions GetRandomMission();
