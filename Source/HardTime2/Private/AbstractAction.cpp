#include "AbstractAction.h"
#include "HTNWorldState.h"
#include "EItemType.h"
#include "Missions.h"
#include "PlatformSpecificForPlanner.h"

std::string ActionToString(EActions action)
{
    switch(action)
    {
        case EActions::evade:
            return "Evade";
        case EActions::attack:
            return "Attack";
        case EActions::study:
            return "study";
        case EActions::workOut:
            return "workOut";
        case EActions::runCircuits:
            return "runCircuits";
        case EActions::sleep:
            return "sleep";
        case EActions::drink:
            return "drink";
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
        case EActions::makeFriends:
            return "MakeFriends";
        case EActions::offerMission:
            return "OfferMission";
        case EActions::pickUpItemByPtr:
            return "PickUpItem";
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
            return "noAction";
    }
    ThrowException("ERROR UnrecognisedAction");
    return "ERROR UnrecognisedAction";
}

std::string BaseAction::ToString() {
    return ActionToString(m_action);
}

bool BaseAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return true;
}

bool GoToGymAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::gym;
}

bool GoToLibraryAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::library;
}

bool GoToCircuitTrackAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::circuitTrack;
}

bool GoToBedroomAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::bedroom;
}

bool GoToMainHallAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

bool PickUpItemByPtrAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) && (htnWorldState.m_itemCarriedPtr->m_realItem == m_itemFocusPtr);
}

bool PickUpItemByTypeAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) && (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}
RequestItemAction::RequestItemAction(UPlayerData* targetPlayer, EItemType itemType):
    BaseAction(EActions::requestItem),
    m_targetPlayer(targetPlayer),
    m_itemTypeSpecified(true),
    m_itemType(itemType)
{}

RequestItemAction::RequestItemAction(UPlayerData* targetPlayer):
    BaseAction(EActions::requestItem),
    m_targetPlayer(targetPlayer),
    m_itemTypeSpecified(false),
    m_itemType(EItemType::ball)
{}

bool DropItemAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_itemCarriedPtr == nullptr;
}

bool RequestItemAction::LastActionSucceeded(HTNWorldState const& htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) && (!m_itemTypeSpecified || (m_itemTypeSpecified && htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType));
}