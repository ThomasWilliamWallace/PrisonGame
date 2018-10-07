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
    switch(m_mission)
    {
        case (Missions::increaseAgility):
            return "increase agility";
        case (Missions::increaseStrength):
            return "increase strength";
        case (Missions::increaseIntelligence):
            return "increase intelligence";
        case (Missions::bringItemToRoom):
            return "bring item to room";
        case (Missions::noMission):
            return "no mission";
    }
    return "UnrecognisedMission";
}

std::string MissionClass::MissionNarrative(Player player[])
{
    switch (m_mission)
    {
        case Missions::noMission:
            return "No Mission\n";
        case Missions::increaseAgility:
            return "Mission: " + player[m_targetPlayerIndex].name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(player[m_targetPlayerIndex].stats.getAgility()) + ")\n";
        case Missions::increaseStrength:
            return "Mission: " + player[m_targetPlayerIndex].name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(player[m_targetPlayerIndex].stats.getStrength()) + ")\n";
        case Missions::increaseIntelligence:
            return "Mission: " + player[m_targetPlayerIndex].name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(player[m_targetPlayerIndex].stats.getIntelligence()) + ")\n";
        case Missions::bringItemToRoom:
            return "Mission: " + player[m_targetPlayerIndex].name + " must bring a " + ItemTypeToString(m_itemType) + " to the " + m_locationClass.ToString() + ".\n";
    }
    return "ERROR: MISSION TYPE NOT RECOGNISED";
}

Missions GetRandomMission()
{
    int random = rand() % 100;
    if (random<25)
        return Missions::increaseStrength;
    else if (random<50)
        return Missions::increaseAgility;
    else if (random<75)
        return Missions::increaseIntelligence;
    else
        return Missions::bringItemToRoom;
}

MissionClass::MissionClass(Missions mission, double objective, int targetPlayerIndex) : m_mission(mission), m_objective(objective), m_targetPlayerIndex(targetPlayerIndex) {}

MissionClass::MissionClass(Missions mission, ItemType itemType, Locations location) : m_mission(mission), m_itemType(itemType), m_locationClass(location) {}

MissionClass::MissionClass() : m_mission(Missions::noMission), m_objective(101), m_targetPlayerIndex(-1) {}