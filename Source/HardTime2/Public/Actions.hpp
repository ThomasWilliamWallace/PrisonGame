#pragma once

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
	makeFriends,
	offerMission,
	pickUpItem,
	dropItem,
	noAction // serves as a flag for any unset actions
};