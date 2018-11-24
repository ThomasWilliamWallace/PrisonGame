#pragma once

#include <iostream>

class UPlayerData;

enum class Actions //MUST KEEP IN SYNC WITH V_ACTION
{
	attack,
	useRoom,
	goToLibrary,
	goToGym,
	goToCircuitTrack,
	goToBedroom,
	goToMainHall,
	evade,
	pickUpItem,
	dropItem,
    requestItem,
    acceptRequest,
    declineRequest,
	noAction // serves as a flag for any unset actions
};

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, UPlayerData player[]);
std::string ActionToString(Actions action);
