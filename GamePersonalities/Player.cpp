//
//  Player.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Player.hpp"
#include "Missions.hpp"

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

bool Player::IsMissionComplete()
{
    switch (missionClass.mission)
    {
        case Missions::increaseAgility:
            if (missionClass.objective <= stats.getAgility())
            {
                return true;
            } else
            {
                return false;
            }
        case Missions::increaseStrength:
            if (missionClass.objective <= stats.getStrength())
            {
                return true;
            } else
            {
                return false;
            }
        case Missions::increaseIntelligence:
            if (missionClass.objective <= stats.getIntelligence())
            {
                return true;
            } else
            {
                return false;
            }
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
    std::cout << "mission.name=" << missionClass.MissionName() << "\n";
    std::cout << "mission.objective=" << FormatDouble(missionClass.objective) << "\n";
    std::cout << "mission.targetPlayerIndex=" << missionClass.targetPlayerIndex << "\n";
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
        case (Missions::noMission):
            break;
        case (Missions::increaseAgility):
            tempObjective = player[playerIndex].stats.getAgility();
            break;
        case (Missions::increaseStrength):
            tempObjective = player[playerIndex].stats.getStrength();
            break;
        case (Missions::increaseIntelligence):
            tempObjective = player[playerIndex].stats.getIntelligence();
            break;
    }
    tempObjective += 3; //todo ensure that the mission is achievable, ie 100 or below
    return MissionClass(tempMission, tempObjective, playerIndex); //TODO targetPlayerIndex not set
}

void Player::UpdateMissions(Player player[])
{
    if (IsMissionComplete())
    {
        std::cout << name << " has completed his mission to " << missionClass.MissionName() << " and now has sanity=" << FormatDouble(stats.getSanity()) << "!\n";
        stats.deltaSanity(5);
        missionClass = MissionClass(); //create a no_mission mission
    }
}
