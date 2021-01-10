#pragma once

#include <iostream>
#include "ActorItem.h"
#include "EMissions.h"

class UPlayerData;
class USimWorld;

//https://stackoverflow.com/questions/7010827/named-constructor-idiom-and-new-operator
enum class RandomMission{
    CreateRandomMission
};

class MissionClass
{
public:
    MissionClass(RandomMission r, UPlayerData* playerPtr);
	MissionClass(UPlayerData* owner);
	MissionClass(const MissionClass& missionClass);
	MissionClass(EMissions mission, UPlayerData* owner, double objective);
	MissionClass(EMissions mission, UPlayerData* owner, EItemType itemE, ELocations location);

	bool IsMissionComplete(USimWorld &world);
    std::string MissionNarrative();
public:
    EMissions m_mission;
    UPlayerData* m_owner;
    double m_objective; //objective for stat increase missions
    EItemType m_itemType;
    LocationClass m_locationClass;
    
    std::string MissionName();
};

EMissions GetRandomMission();
