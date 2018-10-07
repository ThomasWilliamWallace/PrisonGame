//
//  Player.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

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

void Relationship::PrintRel(std::string name1, std::string name2)
{
    std::cout << "*** " << name1 << " OPINION OF " << name2 << " ***\n";
    std::cout << "aggro=" << FormatDouble(getAggro()) << "\n";
    std::cout << "friendliness=" << FormatDouble(getFriendliness()) << "\n";
    std::cout << "fear=" << FormatDouble(getFear()) << "\n";
    std::cout << "threat=" << FormatDouble(getThreat()) << "\n";
    std::cout << "submissiveness=" << FormatDouble(getSubmissiveness()) << "\n";
    std::cout << "plotImportance=" << FormatDouble(getPlotImportance()) << "\n";
    std::cout << "trust=" << FormatDouble(getTrust()) << "\n";
    std::cout << "\n";
}

bool Player::IsMissionComplete(World &world)
{
    switch (missionClass.m_mission)
    {
        case Missions::increaseAgility:
            return (missionClass.m_objective <= stats.getAgility());
        case Missions::increaseStrength:
            return (missionClass.m_objective <= stats.getStrength());
        case Missions::increaseIntelligence:
            return (missionClass.m_objective <= stats.getIntelligence());
        case Missions::bringItemToRoom:
            for (auto &item : world.items)
            {
                if ((item->m_itemType == missionClass.m_itemType) && (item->m_locationClass.location == missionClass.m_locationClass.location))
                {
                    return true;
                }
            }
            return false;
        case Missions::noMission:
            return false;
    }
	return false;
}

std::string CharacterName(Player player[], int playerIndex)
{
    if (playerIndex==c_empty)
        return "c_empty";
    else
        return player[playerIndex].name;
}

void Player::PrintPlayer()
{
    std::cout << "*** PLAYER " << name << " ***\n";
    std::cout << "action=" << ActionToString(action) << "\n";
    std::cout << "lastAction=" << ActionToString(lastAction) << "\n";
    std::cout << "location=" << locationClass.ToString() << "\n";
    std::cout << "lastLocation=" << lastLocationClass.ToString() << "\n";
    std::cout << "attacked=" << BoolToString(attacked) << "\n";
    std::cout << "playerTarget=" << playerTarget << "\n";
    std::cout << "narrative=" << narrative << "\n";
    std::cout << "mission.MissionName()=" << missionClass.MissionName() << "\n";
    std::cout << "mission.m_objective=" << FormatDouble(missionClass.m_objective) << "\n";
    std::cout << "mission.m_targetPlayerIndex=" << missionClass.m_targetPlayerIndex << "\n";
    std::cout << "mission.m_itemType=" << ItemTypeToString(missionClass.m_itemType) << "\n";
    std::cout << "mission.m_locationClass=" << missionClass.m_locationClass.ToString() << "\n";
    std::cout << "cash=" << cash << "\n";
    std::cout << "sentence=" << sentence << "\n";
    std::cout << "m_playerIndex=" << m_playerIndex << "\n";
    std::cout << "\n";
    stats.PrintStats();
}

MissionClass CreateNewMission(Player player[], int playerIndex)
{
    if (playerIndexOutOfBounds(playerIndex))
    {
        return MissionClass();
    }
    Missions tempMission = GetRandomMission();
    double tempObjective;
    switch (tempMission)
    {
        case Missions::noMission:
            break;
        case Missions::increaseAgility:
            tempObjective = player[playerIndex].stats.getAgility();
            break;
        case Missions::increaseStrength:
            tempObjective = player[playerIndex].stats.getStrength();
            break;
        case Missions::increaseIntelligence:
            tempObjective = player[playerIndex].stats.getIntelligence();
            break;
        case Missions::bringItemToRoom:
            return MissionClass(tempMission, GetRandomItemType(), GetRandomLocation());
    }
    tempObjective += 3; //todo ensure that the mission is achievable, ie 100 or below
    return MissionClass(tempMission, tempObjective, playerIndex); //TODO targetPlayerIndex not set
}

void Player::UpdateMissions(Player player[], World &world)
{
    if (IsMissionComplete(world))
    {
        std::cout << name << " has completed his mission to " << missionClass.MissionName() << " and now has sanity=" << FormatDouble(stats.getSanity()) << "!\n";
        stats.deltaSanity(5);
        missionClass = MissionClass(); //create a no_mission mission
    }
}
