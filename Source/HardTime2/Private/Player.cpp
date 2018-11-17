#include "Player.hpp"
#include "Missions.hpp"
#include "World.hpp"
#include "Locations.hpp"

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

std::string CharacterName(Player* playerPtr)
{
    if (playerPtr == nullptr)
        return "c_empty";
    else
        return playerPtr->name;
}

MissionClass CreateNewMission(Player* playerPtr)
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

void Player::UpdateMissions(Player player[], World &world)
{
    if (missionClass.IsMissionComplete(world))
    {
        pStats.deltaSanity(5);
        missionClass = MissionClass(); //create a no_mission mission
    }
}
