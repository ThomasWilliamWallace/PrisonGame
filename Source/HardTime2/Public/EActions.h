#pragma once

#ifndef TEXT_ONLY_HTN
#include "EActions.generated.h"
#endif

UENUM(BlueprintType, Blueprintable)
enum class EActions : uint8
{
    attack,
    study,
    workOut,
    runCircuits,
    sleep,
    goToLibrary,
    goToGym,
    goToCircuitTrack,
    goToBedroom,
    goToMainHall,
    drink,
    evade,
    makeFriends,
    offerMission,
    pickUpItemByPtr,
    pickUpItemByType,
    dropItem,
    requestItem,
    acceptRequest,
    declineRequest,
    noAction, // serves as a flag for any unset actions
    LAST = noAction
};
