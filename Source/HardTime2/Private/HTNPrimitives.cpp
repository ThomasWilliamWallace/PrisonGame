#include "HTNPrimitives.hpp"
#include "Locations.hpp"
#include "AICharacterC.h"
#include "Engine/GameEngine.h"

constexpr int c_playerCount = 2; //Other declaration in HTNWorldState.cpp

//***********************************************************
Study::Study() : HTNPrimitive("Study") {}

void Study::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) += 1;
	return;
}

Actions Study::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::useRoom;
}


bool Study::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::library;
}

//***********************************************************
Sleep::Sleep() : HTNPrimitive("Sleep") {}

void Sleep::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::health) += 1;
	return;
}

Actions Sleep::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::useRoom;
}

bool Sleep::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::bedroom;
}

//***********************************************************
UseGym::UseGym() : HTNPrimitive("UseGym") {}

void UseGym::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::strength) += 1;
	return;
}

Actions UseGym::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::useRoom;
}

bool UseGym::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::gym;
}

//***********************************************************
RunCircuits::RunCircuits() : HTNPrimitive("RunCircuits") {}

void RunCircuits::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::agility) += 1;
	return;
}

Actions RunCircuits::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::useRoom;
}

bool RunCircuits::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::circuitTrack;
}

//***********************************************************
GoToGym::GoToGym() : HTNPrimitive("GoToGym") {}

void GoToGym::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::gym);
	return;
}

Actions GoToGym::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::goToGym;
}

bool GoToGym::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

bool GoToGym::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::gym;
}

//***********************************************************
GoToLibrary::GoToLibrary() : HTNPrimitive("GoToLibrary") {}

void GoToLibrary::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::library);
	return;
}

Actions GoToLibrary::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::goToLibrary;
}

bool GoToLibrary::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

bool GoToLibrary::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::library;
}

//***********************************************************
GoToBedroom::GoToBedroom() : HTNPrimitive("GoToBedroom") {}

void GoToBedroom::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::bedroom);
	return;
}

Actions GoToBedroom::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::goToBedroom;
}

bool GoToBedroom::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

bool GoToBedroom::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::bedroom;
}

//***********************************************************
GoToCircuitTrack::GoToCircuitTrack() : HTNPrimitive("GoToCircuitTrack") {}

void GoToCircuitTrack::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::circuitTrack);
	return;
}

Actions GoToCircuitTrack::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::goToCircuitTrack;
}

bool GoToCircuitTrack::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

bool GoToCircuitTrack::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::circuitTrack;
}

//***********************************************************
GoToMainHall::GoToMainHall() : HTNPrimitive("GoToMainHall") {}

void GoToMainHall::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::mainHall);
	return;
}

Actions GoToMainHall::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::goToMainHall;
}

bool GoToMainHall::Preconditions(HTNWorldState &htnWorldState)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) != Locations::mainHall;
}

bool GoToMainHall::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

//***********************************************************
Drink::Drink() : HTNPrimitive("Drink") {}

void Drink::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::intelligence) -= 1;
	return;
}

Actions Drink::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::noAction;
}

bool Drink::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
Punch::Punch(int playerIndex) : HTNPrimitive("Punch"), m_targetPlayerIndex(playerIndex) {}

void Punch::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::punches) += 1;
}

Actions Punch::Operate(AAICharacterC* aiCharacterC)
{
	//player[playerIndex].playerTarget = m_targetPlayerIndex;
	return Actions::attack;
}

bool Punch::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_playerLocations[m_targetPlayerIndex] == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location));
}

//***********************************************************
Evade::Evade() : HTNPrimitive("Evade") {}

void Evade::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_v.at(WorldE::evading) = 1;
}

Actions Evade::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::evade;
}

bool Evade::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
PickUpItem::PickUpItem(SimActorItem* itemFocusPtr) : HTNPrimitive("PickUpItem"), m_itemFocusPtr(itemFocusPtr) {}

void PickUpItem::Effect(HTNWorldState &htnWorldState)
{
	m_itemFocusPtr->m_carryingPlayer = htnWorldState.m_ptrToSelf;
	htnWorldState.m_itemCarriedPtr = m_itemFocusPtr;
}

Actions PickUpItem::Operate(AAICharacterC* aiCharacterC)
{
	//player[playerIndex].itemFocusPtr = m_itemFocusPtr;
	return Actions::pickUpItem;
}

bool PickUpItem::Preconditions(HTNWorldState &htnWorldState)
{
	//TODO hook this into the actions code
	if (m_itemFocusPtr != nullptr
		&& static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == m_itemFocusPtr->m_locationClass.location
		&& m_itemFocusPtr->m_carryingPlayer == nullptr)
	{
		return true;
	}
	return false;
}

//***********************************************************
PickUpItem2::PickUpItem2(ItemType itemType) : HTNPrimitive("PickUpItem2"), m_itemType(itemType) {}

void PickUpItem2::Effect(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_itemType == m_itemType
			&& item->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location))
			&& item->m_carryingPlayer == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PickUpItem2::Effect item = %p"), item));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PickUpItem2::Effect htnWorldState.m_ptrToSelf = %p"), htnWorldState.m_ptrToSelf));
			item->m_carryingPlayer = htnWorldState.m_ptrToSelf;
			htnWorldState.m_itemCarriedPtr = item;
			return;
		}
	}
}

Actions PickUpItem2::Operate(AAICharacterC* aiCharacterC)
{
	for (auto &item : aiCharacterC->m_items)
	{
		if (item->m_itemType == m_itemType && item->m_locationClass.location == aiCharacterC->locationClass.location)
		{
			aiCharacterC->m_itemFocusPtr = item->m_unrealItem;
			return Actions::pickUpItem;
		}
	}
	aiCharacterC->m_itemFocusPtr = nullptr;
	return Actions::noAction;
}

bool PickUpItem2::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_itemType == m_itemType
			&& item->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location))
			&& item->m_carryingPlayer == nullptr)
		{
			return true;
		}
	}
	return false;
}

bool PickUpItem2::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) && (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

//***********************************************************
DropItem::DropItem() : HTNPrimitive("DropItem") {}

void DropItem::Effect(HTNWorldState &htnWorldState)
{
	htnWorldState.m_itemCarriedPtr->m_locationClass.location = static_cast<Locations>(htnWorldState.m_v.at(WorldE::location));
	htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	htnWorldState.m_itemCarriedPtr = nullptr;
}

Actions DropItem::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::dropItem;
}

bool DropItem::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_itemCarriedPtr != nullptr; //TODO hook this into the actions code
}

bool DropItem::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return htnWorldState.m_itemCarriedPtr == nullptr;
}