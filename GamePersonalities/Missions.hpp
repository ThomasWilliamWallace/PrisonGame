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

class Player;

class MissionClass
{
public:
	Missions mission;
	double objective; //objective for stat increase missions
	int targetPlayerIndex;
    std::string MissionName();
    MissionClass(Missions mission, double objective, int targetPlayerIndex);
    MissionClass();
    std::string MissionNarrative(Player player[]);
};

Missions GetRandomMission();

#endif /* Missions_hpp */
