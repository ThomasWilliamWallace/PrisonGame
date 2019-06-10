#include "Relationship.h"
#include "PlayerData.h"
#include "Missions.hpp"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "HardTime2Character.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "pLog.hpp"
//TODO cull unused includes

double URelationship::getAggro()
{
    return aggro;
}

double URelationship::getFriendliness()
{
    return friendliness;
}

double URelationship::getFear()
{
    return fear;
}

double URelationship::getThreat()
{
    return threat;
}

double URelationship::getSubmissiveness()
{
    return submissiveness;
}

double URelationship::getPlotImportance()
{
    return plotImportance;
}

double URelationship::getTrust()
{
    return trust;
}

void URelationship::deltaAggro(double delta)
{
    aggro = transformStat(aggro + delta);
}

void URelationship::deltaFriendliness(double delta)
{
    friendliness = transformStat(friendliness + delta);
}

void URelationship::deltaFear(double delta)
{
    fear = transformStat(fear + delta);
}

void URelationship::deltaThreat(double delta)
{
    threat = transformStat(threat + delta);
}

void URelationship::deltaSubmissiveness(double delta)
{
    submissiveness = transformStat(submissiveness + delta);
}

void URelationship::deltaPlotImportance(double delta)
{
    plotImportance = transformStat(plotImportance + delta);
}

void URelationship::deltaTrust(double delta)
{
    trust = transformStat(trust + delta);
}

void URelationship::SetRecentlyRequested()
{
	isRequestedRecently = true;
	pLog("Entering SetRecentlyRequested", true);
	UWorld* w = GetWorld();
	if (!IsValid(w))
	{
		if (w == nullptr)
		{
			pLog("Disaster: w set to NULLPTR!", true);
		}
		else {
			pLog("Disaster: w is not valid!", true);
		}
	}
	else
	{
		pLog("w successfully set to GetWorld()", true);
	}
	FTimerManager& tm = w->GetTimerManager();
//	if (!IsValid(tm))
//	{
//		if (tm == nullptr)
//		{
//			pLog("Disaster: tm set to NULLPTR!", true);
//		}
//		else {
//			pLog("Disaster: tm is not valid!", true);
//		}
//	}
//	else
//	{
		pLog("tm successfully set to w->GetTimerManager()", true);
//	}
	if (!(tm.IsTimerActive(requestCooldownTimer)))
	{
		pLog("set request cooldown timer", true);
		float cooldownTime = 5;//20 + rand() % 600;  //ask again sometime in the next 20 seconds to 10 minutes
		tm.SetTimer(
			requestCooldownTimer, this, &URelationship::RequestCooldownTimerElapsed, cooldownTime, false);
	}
}

void URelationship::RequestCooldownTimerElapsed()
{
	pLog("ENTERING RequestCooldownTimerElapsed", true);
	isRequestedRecently = false;
	GetWorld()->GetTimerManager().ClearTimer(requestCooldownTimer);
}

class UWorld* URelationship::GetWorld() const
{
	UObject* outer = GetOuter();

	if (!IsValid(outer))
		return nullptr;

	UPlayerData* owningPlayerData = Cast<UPlayerData>(outer);

	if (!IsValid(owningPlayerData))
		return nullptr;

	UWorld* w;
	if (owningPlayerData)
	{
		w = owningPlayerData->GetWorld();
		if (w == nullptr)
			pLog("Disaster", true);
	}
	else
		w = nullptr;
	return w;
}