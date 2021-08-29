#include "HTNPrimitives.h"
#include "Locations.h"
#include "PlayerData.h"
#include <stdexcept>
#include "pLog.h"
#include "PlatformSpecific.h"
#include "HTNWorldState.h"

//***********************************************************
StudyPrim::StudyPrim() : HTNPrimitive("StudyPrim") {}

void StudyPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState & state = static_cast<HTNWorldState &>(iHTNWorldState);
    state.m_intelligence += 1;
    return;
}

bool StudyPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::library;
}

std::shared_ptr<BaseAction> StudyPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
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

std::shared_ptr<BaseAction> SleepPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
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

std::shared_ptr<BaseAction> UseGymPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
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

std::shared_ptr<BaseAction> RunCircuitsPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::useRoom);
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

std::shared_ptr<BaseAction> GoToGymPrim::Operate(UPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToGym);
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

std::shared_ptr<BaseAction> GoToLibraryPrim::Operate(UPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToLibrary);
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

std::shared_ptr<BaseAction> GoToCircuitTrackPrim::Operate(UPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToCircuitTrack);
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

std::shared_ptr<BaseAction> GoToBedroomPrim::Operate(UPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToBedroom);
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

std::shared_ptr<BaseAction> GoToMainHallPrim::Operate(UPlayerData* playerData)
{
	return std::make_shared<BaseAction>(EActions::goToMainHall);
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

std::shared_ptr<BaseAction> DrinkPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::noAction);
}

//***********************************************************
PunchPrim::PunchPrim(UPlayerData* opponent) : HTNPrimitive("PunchPrim"), m_targetPlayer(opponent) {}

void PunchPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    if (state.m_itemCarriedPtr != nullptr)
    {
        state.m_itemsToKeep.push_back(state.m_itemCarriedPtr);
    }
}

bool PunchPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.IsInTheRoom(*m_targetPlayer);
}

std::shared_ptr<BaseAction> PunchPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<AttackAction>(m_targetPlayer);
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

std::shared_ptr<BaseAction> EvadePrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<EvadeAction>(m_evadePlayer);
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
	if (GetRaw(currentSimItem) == nullptr) {
		ThrowException("Failed to find relevant SimItem in PickUpItemByPtrPrim::preconditions");
    }
    //TODO hook this into the actions code
    //bool is_already_carrying_an_item = GetRaw(state.m_itemCarriedPtr) == nullptr;
    check(GetRaw(currentSimItem) != nullptr);
    bool item_is_in_the_same_room = state.m_location == currentSimItem->m_locationClass.location;
    bool item_is_already_being_carried = currentSimItem->m_carryingPlayer == nullptr;
//    if (GetRaw(state.m_itemCarriedPtr) == nullptr
//      && GetRaw(currentSimItem) != nullptr
//      && state.m_location == currentSimItem->m_locationClass.location
//      && currentSimItem->m_carryingPlayer == nullptr)
    if (item_is_in_the_same_room && item_is_already_being_carried)
    {
        return true;
    }
    return false;
}

std::shared_ptr<BaseAction> PickUpItemByPtrPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<PickUpItemByPtrAction>(m_itemFocus->m_realItem);
}

//***********************************************************
PickUpItemByTypePrim::PickUpItemByTypePrim(EItemType itemType) : HTNPrimitive("PickUpItemByTypePrim"), m_itemType(itemType) {}

void PickUpItemByTypePrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    for (auto &item : state.m_items)
    {
		if (GetRaw(state.m_itemCarriedPtr) == nullptr
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
        if (GetRaw(state.m_itemCarriedPtr) == nullptr
            && item->m_itemType == m_itemType
            && item->m_locationClass.location == state.m_location
            && item->m_carryingPlayer == nullptr)
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr<BaseAction> PickUpItemByTypePrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<PickUpItemByTypeAction>(m_itemType);
}

//***********************************************************
DropItemPrim::DropItemPrim(bool keepItem) : HTNPrimitive("DropItemPrim"), m_keepItem(keepItem) {}

void DropItemPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
    state.m_itemCarriedPtr->m_locationClass.location = state.m_location;
    state.m_itemCarriedPtr->m_carryingPlayer = nullptr;
    if (m_keepItem)
    {
        state.m_itemsToKeep.push_back(state.m_itemCarriedPtr);
    }
    state.m_itemCarriedPtr = nullptr;
}

bool DropItemPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return GetRaw(state.m_itemCarriedPtr) != nullptr; //TODO hook this into the actions code
}

std::shared_ptr<BaseAction> DropItemPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::dropItem);
}

//***********************************************************
RequestItemPrim::RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType):
	HTNPrimitive("RequestItemPrim"),
    m_requestedPlayer(requestedPlayer),
    m_itemType(itemType)
{
    assert(m_requestedPlayer != nullptr);
}

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
    if (GetRaw(state.m_itemCarriedPtr) != nullptr)
    {
        return false;
    }
    for (auto &item : state.m_items)
    {
        if (item->m_carryingPlayer == m_requestedPlayer && item->m_itemType == m_itemType && state.IsInTheRoom(*(item->m_carryingPlayer)))
        {
            return true;
        }
    }
    return false; //TODO hook this into the actions code
}

std::shared_ptr<BaseAction> RequestItemPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<RequestItemAction>(m_requestedPlayer, m_itemType);
}
