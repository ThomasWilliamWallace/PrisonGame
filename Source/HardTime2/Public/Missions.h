#pragma once

#include <iostream>
#include "ActorItem.h"
#include "EMissions.h"
#include "AbstractMission.h"

class UPlayerData;
class USimWorld;

class MissionClass : public AbstractMission
{
public:
	MissionClass(AbstractPlayerData* owner);
	MissionClass(const MissionClass& missionClass);
	MissionClass(EMissions mission, AbstractPlayerData* owner, double objective);
	MissionClass(EMissions mission, AbstractPlayerData* owner, EItemType itemE, ELocations location);

	bool IsMissionComplete(USimWorld &world);
};
