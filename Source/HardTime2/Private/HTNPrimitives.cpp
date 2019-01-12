#include "HTNPrimitives.hpp"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include <stdexcept>
#include "pLog.hpp"
#include "PlatformSpecific.hpp"

//***********************************************************
StudyPrim::StudyPrim() : HTNPrimitive("StudyPrim") {}

void StudyPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) += 1;
	return;
}

Actions StudyPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool StudyPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::library;
}

//***********************************************************
SleepPrim::SleepPrim() : HTNPrimitive("SleepPrim") {}

void SleepPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::health) += 1;
	return;
}

Actions SleepPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool SleepPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::bedroom;
}

//***********************************************************
UseGymPrim::UseGymPrim() : HTNPrimitive("UseGymPrim") {}

void UseGymPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::strength) += 1;
	return;
}

Actions UseGymPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool UseGymPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::gym;
}

//***********************************************************
RunCircuitsPrim::RunCircuitsPrim() : HTNPrimitive("RunCircuitsPrim") {}

void RunCircuitsPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::agility) += 1;
	return;
}

Actions RunCircuitsPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool RunCircuitsPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::circuitTrack;
}

//***********************************************************
GoToGymPrim::GoToGymPrim() : HTNPrimitive("GoToGymPrim") {}

void GoToGymPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::gym);
	return;
}

Actions GoToGymPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToGym;
}

bool GoToGymPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToGymPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::gym;
}

//***********************************************************
GoToLibraryPrim::GoToLibraryPrim() : HTNPrimitive("GoToLibraryPrim") {}

void GoToLibraryPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::library);
	return;
}

Actions GoToLibraryPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToLibrary;
}

bool GoToLibraryPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToLibraryPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::library;
}

//***********************************************************
GoToCircuitTrackPrim::GoToCircuitTrackPrim() : HTNPrimitive("GoToCircuitTrackPrim") {}

void GoToCircuitTrackPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::circuitTrack);
	return;
}

Actions GoToCircuitTrackPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToCircuitTrack;
}

bool GoToCircuitTrackPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToCircuitTrackPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::circuitTrack;
}

//***********************************************************
GoToBedroomPrim::GoToBedroomPrim() : HTNPrimitive("GoToBedroomPrim") {}

void GoToBedroomPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::bedroom);
	return;
}

Actions GoToBedroomPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToBedroom;
}

bool GoToBedroomPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToBedroomPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::bedroom;
}

//***********************************************************
GoToMainHallPrim::GoToMainHallPrim() : HTNPrimitive("GoToMainHallPrim") {}

void GoToMainHallPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::mainHall);
	return;
}

Actions GoToMainHallPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToMainHall;
}

bool GoToMainHallPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) != ELocations::mainHall;
}

bool GoToMainHallPrim::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

//***********************************************************
DrinkPrim::DrinkPrim() : HTNPrimitive("DrinkPrim") {}

void DrinkPrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) -= 1;
	return;
}

Actions DrinkPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::noAction;
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

Actions PunchPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	playerData->playerTargetPtr = m_targetPlayer;
	return Actions::attack;
}

bool PunchPrim::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
	//return htnWorldState.m_playerLocations[m_targetPlayer->m_playerIndex] == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
}

//***********************************************************
EvadePrim::EvadePrim() : HTNPrimitive("EvadePrim") {}

void EvadePrim::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::evading) = 1;
}

Actions EvadePrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::evade;
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

Actions PickUpItemByPtrPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
    playerData->itemFocusPtr = &(m_itemFocus->m_realItem);
    return Actions::pickUpItem;
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
      && static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == currentSimItem->m_locationClass.location
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
			&& item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location))
			&& item->m_carryingPlayer == nullptr)
		{
			item->m_carryingPlayer = htnWorldState.m_ptrToSelf;
			htnWorldState.m_itemCarriedPtr = item;
			return;
		}
	}
}

Actions PickUpItemByTypePrim::Operate(UPlayerData* playerData, USimWorld &world)
{
    for (auto &item : world.items)
	{
		if (item->m_itemType == m_itemType &&
			item->m_locationClass.location == playerData->locationClass.location &&
			item->m_carryingPlayer == nullptr)
		{
			playerData->itemFocusPtr = item;
			return Actions::pickUpItem;
		}
	}
	playerData->itemFocusPtr = nullptr;
	return Actions::noAction;
}

bool PickUpItemByTypePrim::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
        if (GetRaw(htnWorldState.m_itemCarriedPtr) == nullptr
            		&& item->m_itemType == m_itemType
			&& item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location))
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
	htnWorldState.m_itemCarriedPtr->m_locationClass.location = static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
	htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	htnWorldState.m_itemCarriedPtr = nullptr;
}

Actions DropItemPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::dropItem;
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
RequestItemPrim::RequestItemPrim(UPlayerData* player, EItemType itemType) : HTNPrimitive("RequestItem"), m_player(player), m_itemType(itemType) {}

void RequestItemPrim::Effect(HTNWorldState &htnWorldState)
{
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == m_player)
        {
            htnWorldState.m_itemCarriedPtr = item;
            break;
        }
    }
    htnWorldState.m_itemCarriedPtr->m_carryingPlayer = m_player;
}

Actions RequestItemPrim::Operate(UPlayerData* playerData, USimWorld &world)
{
	playerData->playerTargetPtr = m_player;
    return Actions::requestItem;
}

bool RequestItemPrim::Preconditions(HTNWorldState &htnWorldState)
{
    if (GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr)
    {
        return false;
    }
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == m_player && item->m_itemType == m_itemType && htnWorldState.IsInTheRoom(item->m_carryingPlayer))
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
