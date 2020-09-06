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

class UPlayerData;
class USimWorld;

class MissionClass
{
public:
	Missions m_mission;
	UPlayerData* m_owner;
	double m_objective; //objective for stat increase missions
	EItemType m_itemType;
	LocationClass m_locationClass;
	std::string MissionName();
	MissionClass(Missions mission, UPlayerData* owner, double objective);
	MissionClass(Missions mission, UPlayerData* owner, EItemType itemE, ELocations location);
	MissionClass();
	MissionClass(const MissionClass& missionClass);
	MissionClass(UPlayerData* owner);
	bool IsMissionComplete(USimWorld &world);
    std::string MissionNarrative();
};

Missions GetRandomMission();
