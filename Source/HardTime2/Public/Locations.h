#pragma once

#include <iostream>
#include "GameFramework/Actor.h"
#include "Locations.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class ELocations : uint8
{
	mainHall		UMETA(DisplayName="Main hall"),
	gym				UMETA(DisplayName="Gym"),
	circuitTrack	UMETA(DisplayName="Circuit track"),
	library			UMETA(DisplayName="Library"),
	bedroom			UMETA(DisplayName="Bedroom")
};

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