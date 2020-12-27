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

bool StudyPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return htnWorldState.m_location == ELocations::library;
}

std::shared_ptr<BaseAction> StudyPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
}

//***********************************************************
SleepPrim::SleepPrim() : HTNPrimitive("SleepPrim") {}

void SleepPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_health += 1;
	return;
}

bool SleepPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return htnWorldState.m_location == ELocations::bedroom;
}

std::shared_ptr<BaseAction> SleepPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
}

//***********************************************************
UseGymPrim::UseGymPrim() : HTNPrimitive("UseGymPrim") {}

void UseGymPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_strength += 1;
	return;
}

bool UseGymPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return htnWorldState.m_location == ELocations::gym;
}

std::shared_ptr<BaseAction> UseGymPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
}

//***********************************************************
RunCircuitsPrim::RunCircuitsPrim() : HTNPrimitive("RunCircuitsPrim") {}

void RunCircuitsPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_agility += 1;
	return;
}

bool RunCircuitsPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return htnWorldState.m_location == ELocations::circuitTrack;
}

std::shared_ptr<BaseAction> RunCircuitsPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
}

//***********************************************************
GoToGymPrim::GoToGymPrim() : HTNPrimitive("GoToGymPrim") {}

void GoToGymPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::gym;
	return;
}

bool GoToGymPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

std::shared_ptr<BaseAction> GoToGymPrim::Operate(AbstractPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToGym);
}

//***********************************************************
GoToLibraryPrim::GoToLibraryPrim() : HTNPrimitive("GoToLibraryPrim") {}

void GoToLibraryPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::library;
	return;
}

bool GoToLibraryPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

std::shared_ptr<BaseAction> GoToLibraryPrim::Operate(AbstractPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToLibrary);
}

//***********************************************************
GoToCircuitTrackPrim::GoToCircuitTrackPrim() : HTNPrimitive("GoToCircuitTrackPrim") {}

void GoToCircuitTrackPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::circuitTrack;
	return;
}

bool GoToCircuitTrackPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

std::shared_ptr<BaseAction> GoToCircuitTrackPrim::Operate(AbstractPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToCircuitTrack);
}

//***********************************************************
GoToBedroomPrim::GoToBedroomPrim() : HTNPrimitive("GoToBedroomPrim") {}

void GoToBedroomPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::bedroom;
	return;
}

bool GoToBedroomPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location == ELocations::mainHall;
}

std::shared_ptr<BaseAction> GoToBedroomPrim::Operate(AbstractPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToBedroom);
}

//***********************************************************
GoToMainHallPrim::GoToMainHallPrim() : HTNPrimitive("GoToMainHallPrim") {}

void GoToMainHallPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_location = ELocations::mainHall;
	return;
}

bool GoToMainHallPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return htnWorldState.m_location != ELocations::mainHall;
}

std::shared_ptr<BaseAction> GoToMainHallPrim::Operate(AbstractPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToMainHall);
}

//***********************************************************
DrinkPrim::DrinkPrim() : HTNPrimitive("DrinkPrim") {}

void DrinkPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_intelligence -= 1;
    return;
}

bool DrinkPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return true;
}

std::shared_ptr<BaseAction> DrinkPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::noAction);
}

//***********************************************************
PunchPrim::PunchPrim(AbstractPlayerData* opponent) : HTNPrimitive("PunchPrim"), m_targetPlayer(opponent) {}

void PunchPrim::Effect(HTNWorldState &htnWorldState)
{
}

bool PunchPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return true;
	//return htnWorldState.m_playerLocations[m_targetPlayer->m_key] == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location));
}

std::shared_ptr<BaseAction> PunchPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<AttackAction>(m_targetPlayer);
}

//***********************************************************
EvadePrim::EvadePrim() : HTNPrimitive("EvadePrim") {}

void EvadePrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_evading = 1;
}

bool EvadePrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return true;
}

std::shared_ptr<BaseAction> EvadePrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::evade);
}

//***********************************************************
PickUpItemByPtrPrim::PickUpItemByPtrPrim(SimItemPtr itemFocus) : HTNPrimitive("PickUpItemByPtrPrim"), m_itemFocus(itemFocus)
{
    check(itemFocus != nullptr);
}

void PickUpItemByPtrPrim::Effect(HTNWorldState &htnWorldState)
{
    m_itemFocus->m_carryingPlayer = htnWorldState.m_ptrToSelf;
    htnWorldState.m_itemCarriedPtr = m_itemFocus;
}

bool PickUpItemByPtrPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    SimItemPtr currentSimItem = nullptr; //if we are re-checking the preconditions, we need to find the simulated item in htnWorldState, rather than use the old simulated item m_itemFocus
    for (auto &simItem : htnWorldState.m_items)
    {
        if (simItem->m_realItem == m_itemFocus->m_realItem)
        {
            currentSimItem = simItem;
            break;
        }
    }
	if (GetRaw(currentSimItem) == nullptr) {
		ThrowException("Failed to find relevant SimItem in PickUpItemByPtrPrim::preconditions");
    }
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

std::shared_ptr<BaseAction> PickUpItemByPtrPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<PickUpItemByPtrAction>(m_itemFocus->m_realItem);
}

//***********************************************************
PickUpItemByTypePrim::PickUpItemByTypePrim(EItemType itemType) : HTNPrimitive("PickUpItemByTypePrim"), m_itemType(itemType) {}

void PickUpItemByTypePrim::Effect(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (GetRaw(htnWorldState.m_itemCarriedPtr) == nullptr
            && item->m_itemType == m_itemType
            && item->m_locationClass.location == htnWorldState.m_location
			&& item->m_carryingPlayer == nullptr)
		{
			item->m_carryingPlayer = htnWorldState.m_ptrToSelf;
			htnWorldState.m_itemCarriedPtr = item;
			return;
		}
	}
}

bool PickUpItemByTypePrim::Preconditions(HTNWorldState const& htnWorldState)
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

std::shared_ptr<BaseAction> PickUpItemByTypePrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<PickUpItemByTypeAction>(m_itemType);
}

//***********************************************************
DropItemPrim::DropItemPrim() : HTNPrimitive("DropItemPrim") {}

void DropItemPrim::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_itemCarriedPtr->m_locationClass.location = htnWorldState.m_location;
	htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
	htnWorldState.m_itemCarriedPtr = nullptr;
}

bool DropItemPrim::Preconditions(HTNWorldState const& htnWorldState)
{
	return GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr; //TODO hook this into the actions code
}

std::shared_ptr<BaseAction> DropItemPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::dropItem);
}

//***********************************************************
RequestItemPrim::RequestItemPrim(AbstractPlayerData* requestedPlayer, EItemType itemType):
	HTNPrimitive("RequestItemPrim"),
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

bool RequestItemPrim::Preconditions(HTNWorldState const& htnWorldState)
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
			&& htnWorldState.IsInTheRoom(*(item->m_carryingPlayer))
			//&& !htnWorldState.m_ptrToSelf->IsRequestedRecently(m_requestedPlayer, m_itemType)
            )
        {
            return true;
        }
    }
    return false; //TODO hook this into the actions code
}

std::shared_ptr<BaseAction> RequestItemPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<RequestItemAction>(m_requestedPlayer);
}
