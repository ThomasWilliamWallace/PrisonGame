//
//  Missions.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Missions_hpp
#define Missions_hpp

#include <iostream>
#include "Constants.hpp"
#include "Item.hpp"

class Player;

class MissionClass
{
public:
	Missions m_mission;
	double m_objective; //objective for stat increase missions
	int m_targetPlayerIndex;
    ItemType m_itemType;
    LocationClass m_locationClass;
    std::string MissionName();
    MissionClass(Missions mission, double objective, int targetPlayerIndex);
    MissionClass(Missions mission, int targetPlayerIndex, ItemType itemE, Locations location);
    MissionClass();
    MissionClass(const MissionClass& missionClass);
    std::string MissionNarrative(Player player[]);
};

Missions GetRandomMission();

#endif /* Missions_hpp */
