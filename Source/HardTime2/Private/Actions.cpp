#include "Actions.hpp"

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
        case Actions::noAction:
            return "ERROR NO ACTION";
    }
    return "ERROR UnrecognisedAction";
}
