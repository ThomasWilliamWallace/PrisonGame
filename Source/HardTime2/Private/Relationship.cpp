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
	if (!(GetWorld()->GetTimerManager().IsTimerActive(requestCooldownTimer)))
	{
		pLog("set request cooldown timer", true);
		GetWorld()->GetTimerManager().SetTimer(
			requestCooldownTimer, this, &URelationship::RequestCooldownTimerElapsed, 10.0f, false);
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
	UPlayerData* owningPlayerData = Cast<UPlayerData>(GetOuter());

	if (owningPlayerData)
		return owningPlayerData->GetWorld();
	else
		return nullptr;
}