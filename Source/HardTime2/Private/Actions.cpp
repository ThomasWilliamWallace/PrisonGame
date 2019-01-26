#include "Actions.hpp"
#include "PlayerData.h"

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap)
{
    if ((otherPlayerPtr->locationClass.location == playerPtr->locationClass.location) && (otherPlayerPtr != playerPtr))
        return true;
    else
        return false;
}

std::string ActionToString(Actions action)
{
    switch(action)
    {
        case Actions::evade:
            return "Evade";
        case Actions::attack:
            return "Attack";
        case Actions::useRoom:
            return "UseRoom";
        case Actions::goToGym:
            return "GoToGym";
        case Actions::goToBedroom:
            return "GoToBedroom";
        case Actions::goToLibrary:
            return "GoToLibrary";
        case Actions::goToMainHall:
            return "GoToMainHall";
        case Actions::goToCircuitTrack:
            return "GoToCircuitTrack";
        case Actions::pickUpItem:
            return "PickUpItem";
        case Actions::dropItem:
            return "DropItem";
        case Actions::requestItem:
            return "RequestItem";
        case Actions::acceptRequest:
            return "acceptRequest";
        case Actions::declineRequest:
            return "declineRequest";
        case Actions::noAction:
            return "ERROR NO ACTION";
    }
    return "ERROR UnrecognisedAction";
}
