//
//  Locations.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Locations.hpp"

std::string LocationToString(Locations location)
{
	switch (location)
	{
	case (Locations::gym):
		return "Gym";
	case (Locations::circuitTrack):
		return "Circuit track";
	case (Locations::library):
		return "Library";
	case (Locations::bedroom):
		return "Bedroom";
	case (Locations::mainHall):
		return "Main hall";
	}
	return "UnrecognisedLocation";
}

std::string LocationClass::ToString()
{
	return LocationToString(location);
}

Locations GetRandomLocation()
{
	int random = rand() % 100;
	if (random < 20)
		return Locations::bedroom;
	else if (random < 40)
		return Locations::circuitTrack;
	else if (random < 60)
		return Locations::gym;
	else if (random < 80)
		return Locations::library;
	else
		return Locations::mainHall;
}