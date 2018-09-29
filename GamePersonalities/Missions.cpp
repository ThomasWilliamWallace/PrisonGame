//
//  Missions.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Missions.hpp"
#include "Stats.hpp"
#include "Player.hpp"

std::string MissionClass::MissionName()
{
    switch(mission)
    {
        case (Missions::increaseAgility):
            return "increase agility";
        case (Missions::increaseStrength):
            return "increase strength";
        case (Missions::increaseIntelligence):
            return "increase intelligence";
        case (Missions::noMission):
            return "no mission";
    }
    return "UnrecognisedMission";
}

std::string MissionClass::MissionNarrative(Player player[])
{
    std::string narrative =  "Mission: " + player[targetPlayerIndex].name + " must " + MissionName() + " to " + FormatDouble(objective) + " (current=";
    switch (mission)
    {
        case Missions::noMission:
            narrative += "N/A";
            break;
        case Missions::increaseAgility:
            narrative += FormatDouble(player[targetPlayerIndex].stats.getAgility());
            break;
        case Missions::increaseStrength:
            narrative += FormatDouble(player[targetPlayerIndex].stats.getStrength());
            break;
        case Missions::increaseIntelligence:
            narrative += FormatDouble(player[targetPlayerIndex].stats.getIntelligence());
            break;
    }
    narrative += ")\n";
    return narrative;
}

Missions GetRandomMission()
{
    int random = rand() % 100;
    if (random<20)
        return Missions::increaseStrength;
    if (random<60)
        return Missions::increaseAgility;
    else
        return Missions::increaseIntelligence;
}

MissionClass::MissionClass(Missions _mission, double _objective, int _targetPlayerIndex)
{
    mission = _mission;
    objective = _objective;
    targetPlayerIndex = _targetPlayerIndex;
}

MissionClass::MissionClass()
{
    mission = Missions::noMission;
    objective = 101;
    targetPlayerIndex = -1;
}