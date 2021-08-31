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
DoNothingPrim::DoNothingPrim() : HTNPrimitive("DoNothingPrim") {}

void DoNothingPrim::Effect(IHTNWorldState& iHTNWorldState)
{
    return;
}

bool DoNothingPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

//***********************************************************
StudyPrim::StudyPrim() : HTNPrimitive("StudyPrim") {}

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
SleepPrim::SleepPrim() : HTNPrimitive("SleepPrim") {}

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
UseGymPrim::UseGymPrim() : HTNPrimitive("UseGymPrim") {}

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
RunCircuitsPrim::RunCircuitsPrim() : HTNPrimitive("RunCircuitsPrim") {}

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
GoToGymPrim::GoToGymPrim() : HTNPrimitive("GoToGymPrim") {}

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
GoToLibraryPrim::GoToLibraryPrim() : HTNPrimitive("GoToLibraryPrim") {}

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
GoToCircuitTrackPrim::GoToCircuitTrackPrim() : HTNPrimitive("GoToCircuitTrackPrim") {}

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
GoToBedroomPrim::GoToBedroomPrim() : HTNPrimitive("GoToBedroomPrim") {}

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
GoToMainHallPrim::GoToMainHallPrim() : HTNPrimitive("GoToMainHallPrim") {}

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
DrinkPrim::DrinkPrim() : HTNPrimitive("DrinkPrim") {}

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
PunchPrim::PunchPrim(UPlayerData* opponent) : HTNPrimitive("PunchPrim"), m_targetPlayer(opponent) {}

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
EvadePrim::EvadePrim(UPlayerData* opponent) : HTNPrimitive("EvadePrim"), m_evadePlayer(opponent) {}

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
PickUpItemByPtrPrim::PickUpItemByPtrPrim(SimItemPtr itemFocus) : HTNPrimitive("PickUpItemByPtrPrim"), m_itemFocus(itemFocus)
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
PickUpItemByTypePrim::PickUpItemByTypePrim(EItemType itemType) : HTNPrimitive("PickUpItemByTypePrim"), m_itemType(itemType) {}

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
DropItemPrim::DropItemPrim() : HTNPrimitive("DropItemPrim") {}

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
	HTNPrimitive("RequestItemPrim"),
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
