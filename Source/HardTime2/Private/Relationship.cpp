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

double Relationship::getAggro()
{
    return aggro;
}

double Relationship::getFriendliness()
{
    return friendliness;
}

double Relationship::getFear()
{
    return fear;
}

double Relationship::getThreat()
{
    return threat;
}

double Relationship::getSubmissiveness()
{
    return submissiveness;
}

double Relationship::getPlotImportance()
{
    return plotImportance;
}

double Relationship::getTrust()
{
    return trust;
}

void Relationship::deltaAggro(double delta)
{
    aggro = transformStat(aggro + delta);
}

void Relationship::deltaFriendliness(double delta)
{
    friendliness = transformStat(friendliness + delta);
}

void Relationship::deltaFear(double delta)
{
    fear = transformStat(fear + delta);
}

void Relationship::deltaThreat(double delta)
{
    threat = transformStat(threat + delta);
}

void Relationship::deltaSubmissiveness(double delta)
{
    submissiveness = transformStat(submissiveness + delta);
}

void Relationship::deltaPlotImportance(double delta)
{
    plotImportance = transformStat(plotImportance + delta);
}

void Relationship::deltaTrust(double delta)
{
    trust = transformStat(trust + delta);
}

//void Relationship::RequestCooldownTimerElapsed()
//{
//	pLog("ENTERING RequestCooldownTimerElapsed", true);
//	isRequestedRecently = false;
//	GetWorldTimerManager().ClearTimer(requestCooldownTimer);
//}