#pragma once

#include <iostream>
#include "ActorItem.h"
#include "EMissions.h"

class UPlayerData;
class USimWorld;

class MissionClass
{
public:
	EMissions m_mission;
	UPlayerData* m_owner;
	double m_objective; //objective for stat increase missions
	EItemType m_itemType;
	LocationClass m_locationClass;
	std::string MissionName();
	MissionClass(EMissions mission, UPlayerData* owner, double objective);
	MissionClass(EMissions mission, UPlayerData* owner, EItemType itemE, ELocations location);
	MissionClass();
	MissionClass(const MissionClass& missionClass);
	MissionClass(UPlayerData* owner);
	bool IsMissionComplete(USimWorld &world);
    std::string MissionNarrative();
};

EMissions GetRandomMission();
