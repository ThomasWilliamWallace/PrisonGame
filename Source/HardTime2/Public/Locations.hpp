#pragma once
//
//  Locations.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include <iostream>

enum class Locations
{
	gym,
	circuitTrack,
	library,
	bedroom,
	mainHall
};

class LocationClass
{
public:
	Locations location;
	LocationClass(Locations l = Locations::mainHall) : location(l) {}
	LocationClass(const LocationClass& l) : location(l.location) {}
	std::string ToString();
};

std::string LocationToString(Locations location);
Locations GetRandomLocation();