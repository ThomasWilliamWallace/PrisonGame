#include "Locations.h"

std::string LocationToString(ELocations location)
{
	switch (location)
	{
	case (ELocations::gym):
		return "Gym";
	case (ELocations::circuitTrack):
		return "Circuit track";
	case (ELocations::library):
		return "Library";
	case (ELocations::bedroom):
		return "Bedroom";
	case (ELocations::mainHall):
		return "Main hall";
	}
	return "UnrecognisedLocation";
}

std::string LocationClass::ToString()
{
	return LocationToString(location);
}

ELocations GetRandomLocation()
{
	int random = rand() % 100;
	if (random < 20)
		return ELocations::bedroom;
	else if (random < 40)
		return ELocations::circuitTrack;
	else if (random < 60)
		return ELocations::gym;
	else if (random < 80)
		return ELocations::library;
	else
		return ELocations::mainHall;
}
