#include "Actions.h"
#include "PlayerData.h"

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap)
{
    if ((otherPlayerPtr->locationClass.location == playerPtr->locationClass.location) && (otherPlayerPtr != playerPtr))
        return true;
    else
        return false;
}

std::string ActionToString(EActions action)
{
    switch(action)
    {
        case EActions::evade:
            return "Evade";
        case EActions::attack:
            return "Attack";
        case EActions::useRoom:
            return "UseRoom";
        case EActions::goToGym:
            return "GoToGym";
        case EActions::goToBedroom:
            return "GoToBedroom";
        case EActions::goToLibrary:
            return "GoToLibrary";
        case EActions::goToMainHall:
            return "GoToMainHall";
        case EActions::goToCircuitTrack:
            return "GoToCircuitTrack";
        case EActions::pickUpItemByPtr:
            return "PickUpItemByPtr";
        case EActions::pickUpItemByType:
            return "PickUpItemByType";
        case EActions::dropItem:
            return "DropItem";
        case EActions::requestItem:
            return "RequestItem";
        case EActions::acceptRequest:
            return "acceptRequest";
        case EActions::declineRequest:
            return "declineRequest";
        case EActions::noAction:
            return "ERROR NO ACTION";
    }
    return "ERROR UnrecognisedAction";
}
