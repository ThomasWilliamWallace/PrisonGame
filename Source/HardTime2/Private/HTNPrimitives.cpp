#include "HTNPrimitives.hpp"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include <stdexcept>

//***********************************************************
Study::Study() : HTNPrimitive("Study") {}

void Study::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) += 1;
	return;
}

Actions Study::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool Study::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::library;
}

//***********************************************************
Sleep::Sleep() : HTNPrimitive("Sleep") {}

void Sleep::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::health) += 1;
	return;
}

Actions Sleep::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool Sleep::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::bedroom;
}

//***********************************************************
UseGym::UseGym() : HTNPrimitive("UseGym") {}

void UseGym::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::strength) += 1;
	return;
}

Actions UseGym::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool UseGym::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::gym;
}

//***********************************************************
RunCircuits::RunCircuits() : HTNPrimitive("RunCircuits") {}

void RunCircuits::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::agility) += 1;
	return;
}

Actions RunCircuits::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::useRoom;
}

bool RunCircuits::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::circuitTrack;
}

//***********************************************************
GoToGym::GoToGym() : HTNPrimitive("GoToGym") {}

void GoToGym::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::gym);
	return;
}

Actions GoToGym::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToGym;
}

bool GoToGym::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToGym::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::gym;
}

//***********************************************************
GoToLibrary::GoToLibrary() : HTNPrimitive("GoToLibrary") {}

void GoToLibrary::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::library);
	return;
}

Actions GoToLibrary::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToLibrary;
}

bool GoToLibrary::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToLibrary::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::library;
}

//***********************************************************
GoToBedroom::GoToBedroom() : HTNPrimitive("GoToBedroom") {}

void GoToBedroom::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::bedroom);
	return;
}

Actions GoToBedroom::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToBedroom;
}

bool GoToBedroom::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToBedroom::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::bedroom;
}

//***********************************************************
GoToCircuitTrack::GoToCircuitTrack() : HTNPrimitive("GoToCircuitTrack") {}

void GoToCircuitTrack::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::circuitTrack);
	return;
}

Actions GoToCircuitTrack::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToCircuitTrack;
}

bool GoToCircuitTrack::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

bool GoToCircuitTrack::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::circuitTrack;
}

//***********************************************************
GoToMainHall::GoToMainHall() : HTNPrimitive("GoToMainHall") {}

void GoToMainHall::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(ELocations::mainHall);
	return;
}

Actions GoToMainHall::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::goToMainHall;
}

bool GoToMainHall::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) != ELocations::mainHall;
}

bool GoToMainHall::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::mainHall;
}

//***********************************************************
Drink::Drink() : HTNPrimitive("Drink") {}

void Drink::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) -= 1;
	return;
}

Actions Drink::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::noAction;
}

bool Drink::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
Punch::Punch(UPlayerData* opponent) : HTNPrimitive("Punch"), m_targetPlayer(opponent) {}

void Punch::Effect(HTNWorldState &htnWorldState)
{
}

Actions Punch::Operate(UPlayerData* playerData, USimWorld &world)
{
	playerData->playerTargetPtr = m_targetPlayer;
	return Actions::attack;
}

bool Punch::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_playerLocations[m_targetPlayer->m_playerIndex] == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
}

//***********************************************************
Evade::Evade() : HTNPrimitive("Evade") {}

void Evade::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::evading) = 1;
}

Actions Evade::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::evade;
}

bool Evade::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
PickUpItem::PickUpItem(SimActorItemPtr itemFocus) : HTNPrimitive("PickUpItem"), m_itemFocus(itemFocus) {}

void PickUpItem::Effect(HTNWorldState &htnWorldState)
{
    m_itemFocus->m_carryingPlayer = htnWorldState.m_ptrToSelf;
    htnWorldState.m_itemCarriedPtr = m_itemFocus;
}

Actions PickUpItem::Operate(UPlayerData* playerData, USimWorld &world)
{
    playerData->itemFocusPtr = &(m_itemFocus->m_realItem);
    return Actions::pickUpItem;
}

bool PickUpItem::Preconditions(HTNWorldState &htnWorldState)
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
	if (currentSimItem.Get() == nullptr)
		throw std::runtime_error("Failed to find relevant SimItem in PickUpItem::preconditions");
    //TODO hook this into the actions code
    if (htnWorldState.m_itemCarriedPtr.Get() == nullptr
      && currentSimItem.Get() != nullptr
      && static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == currentSimItem->m_locationClass.location
      && currentSimItem->m_carryingPlayer == nullptr)
    {
        return true;
    }
    return false;
}

bool PickUpItem::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr == m_itemFocus);
}

//***********************************************************
PickUpItem2::PickUpItem2(EItemType itemType) : HTNPrimitive("PickUpItem2"), m_itemType(itemType) {}

void PickUpItem2::Effect(HTNWorldState &htnWorldState)
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

Actions PickUpItem2::Operate(UPlayerData* playerData, USimWorld &world)
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

bool PickUpItem2::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
        if (htnWorldState.m_itemCarriedPtr.Get() == nullptr
            		&& item->m_itemType == m_itemType
			&& item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location))
			&& item->m_carryingPlayer == nullptr)
		{
			return true;
		}
	}
	return false;
}

bool PickUpItem2::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr.Get() != nullptr) && (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

//***********************************************************
DropItem::DropItem() : HTNPrimitive("DropItem") {}

void DropItem::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_itemCarriedPtr->m_locationClass.location = static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
	htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	htnWorldState.m_itemCarriedPtr = nullptr;
}

Actions DropItem::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::dropItem;
}

bool DropItem::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_itemCarriedPtr.Get() != nullptr; //TODO hook this into the actions code
}

bool DropItem::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_itemCarriedPtr.Get() == nullptr;
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
    if (htnWorldState.m_itemCarriedPtr.Get() != nullptr)
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
