#pragma once

#ifndef TEXT_ONLY_HTN
#include "EMissions.generated.h"
#endif

UENUM(BlueprintType, Blueprintable)
enum class EMissions : uint8
{
    noMission,
    increaseStrength,
    increaseAgility,
    increaseIntelligence,
    bringItemToRoom,
    LAST = bringItemToRoom
};
