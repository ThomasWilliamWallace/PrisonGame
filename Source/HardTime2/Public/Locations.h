#pragma once

#include <iostream>
#include "GameFramework/Actor.h"
#include "ELocations.h"
#include "Locations.generated.h"

UCLASS()
class ALocations : public AActor  //just here so that locations show in editor TODO remove, since it's referenced in character instead?
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		ELocations m_location;
};

class LocationClass
{
public:
	ELocations location;
	LocationClass(ELocations l = ELocations::mainHall) : location(l) {}
	LocationClass(const LocationClass& l) : location(l.location) {}
	std::string ToString();
};

std::string LocationToString(ELocations location);
ELocations GetRandomLocation();
