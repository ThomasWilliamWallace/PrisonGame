#pragma once

#include <iostream>

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
	noAction // serves as a flag for any unset actions
};

std::string ActionToString(Actions action);
