#pragma once

#ifndef TEXT_ONLY_HTN
#include "ELocations.generated.h"
#endif

UENUM(BlueprintType, Blueprintable)
enum class ELocations : uint8
{
    mainHall,
    gym,
    circuitTrack,
    library,
    bedroom,
    LAST = bedroom
};
