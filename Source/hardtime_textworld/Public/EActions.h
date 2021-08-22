#pragma once

#ifndef TEXT_ONLY_HTN
#include "EActions.generated.h"
#endif

UENUM(BlueprintType, Blueprintable)
enum class EActions : uint8
{
    attack,
    useRoom,
    goToLibrary,
    goToGym,
    goToCircuitTrack,
    goToBedroom,
    goToMainHall,
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
