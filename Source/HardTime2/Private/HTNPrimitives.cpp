#include "HTNPrimitives.h"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include <stdexcept>
#include "pLog.h"
#include "HTNWorldState.h"
#include "PlayerData.h"
#include "AbstractItem.h"
#include "PlatformSpecificForPlanner.h"

//***********************************************************
DoNothingPrim::DoNothingPrim() : Primitive("DoNothingPrim", EActions::noAction) {}

void DoNothingPrim::Effect(IHTNWorldState& iHTNWorldState)
{
    return;
}

bool DoNothingPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

//***********************************************************
StudyPrim::StudyPrim() : Primitive("StudyPrim", EActions::study) {}

void StudyPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState &>(iHTNWorldState);
    state.m_intelligence += 1;
	return;
}

bool StudyPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::library;
}

//***********************************************************
SleepPrim::SleepPrim() : Primitive("SleepPrim", EActions::sleep) {}

void SleepPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_health += 1;
	return;
}

bool SleepPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::bedroom;
}

//***********************************************************
UseGymPrim::UseGymPrim() : Primitive("UseGymPrim", EActions::workOut) {}

void UseGymPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_strength += 1;
	return;
}

bool UseGymPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::gym;
}

//***********************************************************
RunCircuitsPrim::RunCircuitsPrim() : Primitive("RunCircuitsPrim", EActions::runCircuits) {}

void RunCircuitsPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_agility += 1;
	return;
}

bool RunCircuitsPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::circuitTrack;
}

//***********************************************************
GoToGymPrim::GoToGymPrim() : Primitive("GoToGymPrim", EActions::goToGym) {}

void GoToGymPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_location = ELocations::gym;
	return;
}

bool GoToGymPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_location == ELocations::mainHall;
}

//***********************************************************
GoToLibraryPrim::GoToLibraryPrim() : Primitive("GoToLibraryPrim", EActions::goToLibrary) {}

void GoToLibraryPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_location = ELocations::library;
	return;
}

bool GoToLibraryPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_location == ELocations::mainHall;
}

//***********************************************************
GoToCircuitTrackPrim::GoToCircuitTrackPrim() : Primitive("GoToCircuitTrackPrim", EActions::goToCircuitTrack) {}

void GoToCircuitTrackPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_location = ELocations::circuitTrack;
	return;
}

bool GoToCircuitTrackPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_location == ELocations::mainHall;
}

//***********************************************************
GoToBedroomPrim::GoToBedroomPrim() : Primitive("GoToBedroomPrim", EActions::goToBedroom) {}

void GoToBedroomPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_location = ELocations::bedroom;
	return;
}

bool GoToBedroomPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_location == ELocations::mainHall;
}

//***********************************************************
GoToMainHallPrim::GoToMainHallPrim() : Primitive("GoToMainHallPrim", EActions::goToMainHall) {}

void GoToMainHallPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_location = ELocations::mainHall;
	return;
}

bool GoToMainHallPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_location != ELocations::mainHall;
}

//***********************************************************
DrinkPrim::DrinkPrim() : Primitive("DrinkPrim", EActions::drink) {}

void DrinkPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_intelligence -= 1;
    return;
}

bool DrinkPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

//***********************************************************
PunchPrim::PunchPrim(UPlayerData* opponent) : Primitive("PunchPrim", EActions::attack), m_targetPlayer(opponent) {}

void PunchPrim::Effect(IHTNWorldState &iHTNWorldState)
{
}

bool PunchPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return true;
	//return state.m_playerLocations[m_targetPlayer->m_key] == static_cast<ELocations>(state.m_v.at(WorldE::location));
}

//***********************************************************
EvadePrim::EvadePrim(UPlayerData* opponent) : Primitive("EvadePrim", EActions::evade), m_evadePlayer(opponent) {}

void EvadePrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_evading = 1;
}

bool EvadePrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

//***********************************************************
PickUpItemByPtrPrim::PickUpItemByPtrPrim(SimItemPtr itemFocus) : Primitive("PickUpItemByPtrPrim", EActions::pickUpItemByPtr), m_itemFocus(itemFocus)
{
    check(itemFocus != nullptr);
}

void PickUpItemByPtrPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    m_itemFocus->m_carryingPlayer = state.m_ptrToSelf;
    state.m_itemCarriedPtr = m_itemFocus;
}

bool PickUpItemByPtrPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    SimItemPtr currentSimItem = nullptr; //if we are re-checking the preconditions, we need to find the simulated item in iHTNWorldState, rather than use the old simulated item m_itemFocus
    for (auto &simItem : state.m_items)
    {
        if (simItem->m_realItem == m_itemFocus->m_realItem)
        {
            currentSimItem = simItem;
            break;
        }
    }
	if (currentSimItem == nullptr) {
		ThrowException("Failed to find relevant SimItem in PickUpItemByPtrPrim::preconditions");
    }
    //TODO hook this into the actions code
    if (currentSimItem != nullptr
      && state.m_location == currentSimItem->m_locationClass.location
      && currentSimItem->m_carryingPlayer == nullptr)
    {
        return true;
    }
    return false;
}

//***********************************************************
PickUpItemByTypePrim::PickUpItemByTypePrim(EItemType itemType) : Primitive("PickUpItemByTypePrim", EActions::pickUpItemByType), m_itemType(itemType) {}

void PickUpItemByTypePrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
	for (auto &item : state.m_items)
	{
		if (state.m_itemCarriedPtr == nullptr
            && item->m_itemType == m_itemType
            && item->m_locationClass.location == state.m_location
			&& item->m_carryingPlayer == nullptr)
		{
			item->m_carryingPlayer = state.m_ptrToSelf;
			state.m_itemCarriedPtr = item;
			return;
		}
	}
}

bool PickUpItemByTypePrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	for (auto &item : state.m_items)
	{
        if (item->m_itemType == m_itemType
            && item->m_locationClass.location == state.m_location
			&& item->m_carryingPlayer == nullptr)
		{
			return true;
		}
	}
	return false;
}

//***********************************************************
DropItemPrim::DropItemPrim() : Primitive("DropItemPrim", EActions::dropItem) {}

void DropItemPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_itemCarriedPtr->m_locationClass.location = state.m_location;
	state.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	state.m_itemCarriedPtr = nullptr;
}

bool DropItemPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_itemCarriedPtr != nullptr; //TODO hook this into the actions code
}

//***********************************************************
RequestItemPrim::RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType):
	Primitive("RequestItemPrim", EActions::requestItem),
	m_itemType(itemType),
    m_requestedPlayer(requestedPlayer)
{}

void RequestItemPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    for (auto &item : state.m_items)
    {
        if (item->m_carryingPlayer == m_requestedPlayer)
        {
            state.m_itemCarriedPtr = item;
            break;
        }
    }
    state.m_itemCarriedPtr->m_carryingPlayer = m_requestedPlayer;
}

bool RequestItemPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    /*if (state.m_itemCarriedPtr != nullptr)
    {
		pLog("state.m_itemCarriedPtr is not null", true);
        return false;
    }*/
    for (auto &item : state.m_items)
    {
        if (item->m_carryingPlayer == m_requestedPlayer
			&& item->m_itemType == m_itemType
			&& state.IsInTheRoom(*(item->m_carryingPlayer))
			//&& !state.m_ptrToSelf->IsRequestedRecently(m_requestedPlayer, m_itemType)
            )
        {
            return true;
        }
    }
    return false; //TODO hook this into the actions code
}
