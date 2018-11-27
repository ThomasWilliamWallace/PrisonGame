#include "PlayerData.h"
#include "Missions.hpp"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "pLog.hpp"

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

std::string CharacterName(UPlayerData* playerPtr)
{
    if (playerPtr == nullptr)
        return "c_empty";
    else
        return playerPtr->m_playerName;
}

void UPlayerData::PrintPlayer()
{
	std::stringstream ss;
    ss << "*** PLAYER " << m_playerName << " ***\n";
	ss << "action=" << ActionToString(action) << "\n";
	ss << "lastAction=" << ActionToString(lastAction) << "\n";
    ss << "location=" << locationClass.ToString() << "\n";
    ss << "lastLocation=" << lastLocationClass.ToString() << "\n";
//    ss << "attacked=" << BoolToString(attacked) << "\n";
    ss << "playerTargetPtr=" << playerTargetPtr << "\n";
    ss << "narrative=" << narrative << "\n";
    ss << "item=";
    if (itemPtr != nullptr)
        ss << itemPtr->ToString() << "\n";
    else
        ss << "null\n";
    ss << "itemFocus=";
    if (itemFocusPtr != nullptr)
        ss << itemFocusPtr->ToString() << "\n";
    else
        ss << "null\n";
    ss << "missionClass=" << missionClass.MissionNarrative() << "\n";
    ss << "missionOffer=" << missionOffer.MissionNarrative() << "\n";
    ss << "cash=" << cash << "\n";
    ss << "sentence=" << sentence << "\n";
    ss << "m_playerIndex=" << m_playerIndex << "\n";
    ss << "\n";
	pLog(ss);
//    pStats.PrintStats();
}

MissionClass CreateNewMission(UPlayerData* playerPtr)
{
    if (playerPtr == nullptr)
    {
        return MissionClass();
    }
    Missions tempMission = GetRandomMission();
    double tempObjective;
    switch (tempMission)
    {
        case Missions::noMission:
            return MissionClass();
        case Missions::increaseAgility:
            tempObjective = playerPtr->pStats.getAgility();
            break;
        case Missions::increaseStrength:
            tempObjective = playerPtr->pStats.getStrength();
            break;
        case Missions::increaseIntelligence:
            tempObjective = playerPtr->pStats.getIntelligence();
            break;
        case Missions::bringItemToRoom:
            return MissionClass(tempMission, playerPtr, GetRandomItemType(), GetRandomLocation());
		default:
			throw std::invalid_argument("Selected an invalid mission type.");
    }
    tempObjective += 3; //todo ensure that the mission is achievable, ie 100 or below
    return MissionClass(tempMission, playerPtr, tempObjective);
}

void UPlayerData::UpdateMissions(UPlayerData player[], USimWorld &world)
{
    if (missionClass.IsMissionComplete(world))
    {
        pStats.deltaSanity(5);
        missionClass = MissionClass(); //create a no_mission mission
    }
}

UPlayerData::UPlayerData():
	m_playerName("No-name"),
	lastPrimitiveAction(nullptr)
{
}
