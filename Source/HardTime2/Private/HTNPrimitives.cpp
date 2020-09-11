#include "HTNPrimitives.h"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include <stdexcept>
#include "pLog.h"
#include "PlatformSpecific.h"

//***********************************************************
StudyPrim::StudyPrim() : HTNPrimitive("StudyPrim") {}

void StudyPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_intelligence += 1;
	return;
}

EActions StudyPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::useRoom;
}

bool StudyPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_location == ELocations::library;
}

//***********************************************************
SleepPrim::SleepPrim() : HTNPrimitive("SleepPrim") {}

void SleepPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_health += 1;
	return;
}

EActions SleepPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::useRoom;
}

bool SleepPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_location == ELocations::bedroom;
}

//***********************************************************
UseGymPrim::UseGymPrim() : HTNPrimitive("UseGymPrim") {}

void UseGymPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_strength += 1;
	return;
}

EActions UseGymPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::useRoom;
}

bool UseGymPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_location == ELocations::gym;
}

//***********************************************************
RunCircuitsPrim::RunCircuitsPrim() : HTNPrimitive("RunCircuitsPrim") {}

void RunCircuitsPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_agility += 1;
	return;
}

EActions RunCircuitsPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::useRoom;
}

bool RunCircuitsPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_location == ELocations::circuitTrack;
}

//***********************************************************
GoToGymPrim::GoToGymPrim() : HTNPrimitive("GoToGymPrim") {}

void GoToGymPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::gym;
	return;
}

EActions GoToGymPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::goToGym;
}

bool GoToGymPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

bool GoToGymPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::gym;
}

//***********************************************************
GoToLibraryPrim::GoToLibraryPrim() : HTNPrimitive("GoToLibraryPrim") {}

void GoToLibraryPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::library;
	return;
}

EActions GoToLibraryPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::goToLibrary;
}

bool GoToLibraryPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

bool GoToLibraryPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::library;
}

//***********************************************************
GoToCircuitTrackPrim::GoToCircuitTrackPrim() : HTNPrimitive("GoToCircuitTrackPrim") {}

void GoToCircuitTrackPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::circuitTrack;
	return;
}

EActions GoToCircuitTrackPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::goToCircuitTrack;
}

bool GoToCircuitTrackPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

bool GoToCircuitTrackPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::circuitTrack;
}

//***********************************************************
GoToBedroomPrim::GoToBedroomPrim() : HTNPrimitive("GoToBedroomPrim") {}

void GoToBedroomPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::bedroom;
	return;
}

EActions GoToBedroomPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::goToBedroom;
}

bool GoToBedroomPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

bool GoToBedroomPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::bedroom;
}

//***********************************************************
GoToMainHallPrim::GoToMainHallPrim() : HTNPrimitive("GoToMainHallPrim") {}

void GoToMainHallPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::mainHall;
	return;
}

EActions GoToMainHallPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::goToMainHall;
}

bool GoToMainHallPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location != ELocations::mainHall;
}

bool GoToMainHallPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

//***********************************************************
DrinkPrim::DrinkPrim() : HTNPrimitive("DrinkPrim") {}

void DrinkPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_intelligence -= 1;
	return;
}

EActions DrinkPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::noAction;
}

bool DrinkPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
PunchPrim::PunchPrim(UPlayerData* opponent) : HTNPrimitive("PunchPrim"), m_targetPlayer(opponent) {}

void PunchPrim::Effect(HTNWorldState &htnWorldState)
{
}

EActions PunchPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	playerData->playerTargetPtr = m_targetPlayer;
	return EActions::attack;
}

bool PunchPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
	//return htnWorldState.m_playerLocations[m_targetPlayer->m_key] == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
}

//***********************************************************
EvadePrim::EvadePrim() : HTNPrimitive("EvadePrim") {}

void EvadePrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_evading = 1;
}

EActions EvadePrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::evade;
}

bool EvadePrim::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
PickUpItemByPtrPrim::PickUpItemByPtrPrim(SimActorItemPtr itemFocus) : HTNPrimitive("PickUpItemByPtrPrim"), m_itemFocus(itemFocus) {}

void PickUpItemByPtrPrim::Effect(HTNWorldState &htnWorldState)
{
    m_itemFocus->m_carryingPlayer = htnWorldState.m_ptrToSelf;
    htnWorldState.m_itemCarriedPtr = m_itemFocus;
}

EActions PickUpItemByPtrPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
    playerData->itemFocusPtr = &(m_itemFocus->m_realItem);
    return EActions::pickUpItemByPtr;
}

bool PickUpItemByPtrPrim::Preconditions(HTNWorldState &htnWorldState)
{
    SimActorItemPtr currentSimItem = nullptr; //if we are re-checking the preconditions, we need to find the simulated item in htnWorldState, rather than use the old simulated item m_itemFocus
    for (auto &simItem : htnWorldState.m_items)
    {
        if (&(simItem->m_realItem) == &(m_itemFocus->m_realItem))
        {
            currentSimItem = simItem;
            break;
        }
    }
	if (GetRaw(currentSimItem) == nullptr)
		throw std::runtime_error("Failed to find relevant SimItem in PickUpItemByPtrPrim::preconditions");
    //TODO hook this into the actions code
    if (GetRaw(htnWorldState.m_itemCarriedPtr) == nullptr
      && GetRaw(currentSimItem) != nullptr
      && htnWorldState.m_location == currentSimItem->m_locationClass.location
      && currentSimItem->m_carryingPlayer == nullptr)
    {
        return true;
    }
    return false;
}

bool PickUpItemByPtrPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr == m_itemFocus);
}

//***********************************************************
PickUpItemByTypePrim::PickUpItemByTypePrim(EItemType itemType) : HTNPrimitive("PickUpItemByTypePrim"), m_itemType(itemType) {}

void PickUpItemByTypePrim::Effect(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_itemType == m_itemType
            && item->m_locationClass.location == htnWorldState.m_location
			&& item->m_carryingPlayer == nullptr)
		{
			item->m_carryingPlayer = htnWorldState.m_ptrToSelf;
			htnWorldState.m_itemCarriedPtr = item;
			return;
		}
	}
}

EActions PickUpItemByTypePrim::Operate(UPlayerData* playerData, USimWorld &world)
{
    for (auto &item : world.items)
	{
		if (item->m_itemType == m_itemType &&
			item->m_locationClass.location == playerData->locationClass.location &&
			item->m_carryingPlayer == nullptr)
		{
			playerData->itemFocusPtr = item;
			return EActions::pickUpItemByPtr;
		}
	}
	playerData->itemFocusPtr = nullptr;
	return EActions::noAction;
}

bool PickUpItemByTypePrim::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
        if (GetRaw(htnWorldState.m_itemCarriedPtr) == nullptr
            		&& item->m_itemType == m_itemType
            && item->m_locationClass.location == htnWorldState.m_location
			&& item->m_carryingPlayer == nullptr)
		{
			return true;
		}
	}
	return false;
}

bool PickUpItemByTypePrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return (GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr) && (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

//***********************************************************
DropItemPrim::DropItemPrim() : HTNPrimitive("DropItemPrim") {}

void DropItemPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_itemCarriedPtr->m_locationClass.location = htnWorldState.m_location;
	htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	htnWorldState.m_itemCarriedPtr = nullptr;
}

EActions DropItemPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return EActions::dropItem;
}

bool DropItemPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr; //TODO hook this into the actions code
}

bool DropItemPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return GetRaw(htnWorldState.m_itemCarriedPtr) == nullptr;
}

//***********************************************************
RequestItemPrim::RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType):
	HTNPrimitive("RequestItem"),
	m_requestedPlayer(requestedPlayer),
	m_itemType(itemType)
{}

void RequestItemPrim::Effect(HTNWorldState &htnWorldState)
{
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == m_requestedPlayer)
        {
            htnWorldState.m_itemCarriedPtr = item;
            break;
        }
    }
    htnWorldState.m_itemCarriedPtr->m_carryingPlayer = m_requestedPlayer;
}

EActions RequestItemPrim::Operate(UPlayerData* selfPlayer, USimWorld &world)
{
	selfPlayer->playerTargetPtr = m_requestedPlayer;
    return EActions::requestItem;
}

bool RequestItemPrim::Preconditions(HTNWorldState &htnWorldState)
{
    if (GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr)
    {
		pLog("GetRaw(htnWorldState.m_itemCarriedPtr) is not null", true);
        return false;
    }
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == m_requestedPlayer
			&& item->m_itemType == m_itemType
			&& htnWorldState.IsInTheRoom(item->m_carryingPlayer)
			&& !htnWorldState.m_ptrToSelf->IsRequestedRecently(m_requestedPlayer, m_itemType))
        {
            return true;
        }
    }
    return false; //TODO hook this into the actions code
}

bool RequestItemPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return (GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr) && (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}
