#include "HTNDomain.h"
#include "Locations.h"
#include "HTNPrimitives.h"
#include "pLog.h"
#include "PlatformSpecific.h"
#include "EMissions.h"
#include "Missions.h"
#include "ActorItem.h"
#include "HTNWorldState.h"

//***********************************************************
AlreadyInLibraryMethod::AlreadyInLibraryMethod(): HTNMethod("AlreadyInLibraryMethod")
{}

bool AlreadyInLibraryMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::library;
}

void AlreadyInLibraryMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{}

GoToNearbyLibraryMethod::GoToNearbyLibraryMethod(): HTNMethod("GoToNearbyLibraryMethod")
{}

bool GoToNearbyLibraryMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToNearbyLibraryMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToLibraryPrim());
}

GoToDistantLibraryMethod::GoToDistantLibraryMethod(): HTNMethod("GoToDistantLibraryMethod")
{}

bool GoToDistantLibraryMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToDistantLibraryMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToLibraryPrim());
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{}

void GoToLibraryCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new AlreadyInLibraryMethod());
    AddMethod(new GoToNearbyLibraryMethod());
    AddMethod(new GoToDistantLibraryMethod());
}

//***********************************************************
AlreadyInGymMethod::AlreadyInGymMethod(): HTNMethod("AlreadyInGymMethod")
{}

bool AlreadyInGymMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::gym;
}

void AlreadyInGymMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{}

GoToNearbyGymMethod::GoToNearbyGymMethod(): HTNMethod("GoToNearbyGymMethod")
{}

bool GoToNearbyGymMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToNearbyGymMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToGymPrim());
}

GoToDistantGymMethod::GoToDistantGymMethod(): HTNMethod("GoToDistantGymMethod")
{}

bool GoToDistantGymMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToDistantGymMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToGymPrim());
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{}

void GoToGymCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new AlreadyInGymMethod());
    AddMethod(new GoToNearbyGymMethod());
    AddMethod(new GoToDistantGymMethod());
}

//***********************************************************
AlreadyInCircuitTrackMethod::AlreadyInCircuitTrackMethod(): HTNMethod("AlreadyInCircuitTrackMethod")
{}

bool AlreadyInCircuitTrackMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::circuitTrack;
}

void AlreadyInCircuitTrackMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{}

GoToNearbyCircuitTrackMethod::GoToNearbyCircuitTrackMethod(): HTNMethod("GoToNearbyCircuitTrackMethod")
{}

bool GoToNearbyCircuitTrackMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToNearbyCircuitTrackMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToCircuitTrackPrim());
}

GoToDistantCircuitTrackMethod::GoToDistantCircuitTrackMethod(): HTNMethod("GoToDistantCircuitTrackMethod")
{}

bool GoToDistantCircuitTrackMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToDistantCircuitTrackMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToCircuitTrackPrim());
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{}

void GoToCircuitTrackCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new AlreadyInCircuitTrackMethod());
    AddMethod(new GoToNearbyCircuitTrackMethod());
    AddMethod(new GoToDistantCircuitTrackMethod());
}

//***********************************************************
AlreadyInBedroomMethod::AlreadyInBedroomMethod(): HTNMethod("AlreadyInBedroomMethod")
{}

bool AlreadyInBedroomMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_location == ELocations::bedroom;
}

void AlreadyInBedroomMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{}

GoToNearbyBedroomMethod::GoToNearbyBedroomMethod(): HTNMethod("GoToNearbyBedroomMethod")
{}

bool GoToNearbyBedroomMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToNearbyBedroomMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToBedroomPrim());
}

GoToDistantBedroomMethod::GoToDistantBedroomMethod(): HTNMethod("GoToDistantBedroomMethod")
{}

bool GoToDistantBedroomMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToDistantBedroomMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToBedroomPrim());
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{}

void GoToBedroomCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new AlreadyInBedroomMethod());
    AddMethod(new GoToNearbyBedroomMethod());
    AddMethod(new GoToDistantBedroomMethod());
}

//***********************************************************
GoToAndIncreaseHealthMethod::GoToAndIncreaseHealthMethod(): HTNMethod("GoToAndIncreaseHealthMethod")
{}

bool GoToAndIncreaseHealthMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToAndIncreaseHealthMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToBedroomCompound());
    AddTask(new SleepPrim());
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{}

void IncreaseHealthCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new GoToAndIncreaseHealthMethod());
}

//***********************************************************
GoToAndIncreaseStrengthMethod::GoToAndIncreaseStrengthMethod(): HTNMethod("GoToAndIncreaseStrengthMethod")
{}

bool GoToAndIncreaseStrengthMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToAndIncreaseStrengthMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToGymCompound());
    AddTask(new UseGymPrim());
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{}

void IncreaseStrengthCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new GoToAndIncreaseStrengthMethod());
}

//***********************************************************
GoToAndIncreaseAgilityMethod::GoToAndIncreaseAgilityMethod(): HTNMethod("GoToAndIncreaseAgilityMethod")
{}

bool GoToAndIncreaseAgilityMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToAndIncreaseAgilityMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToCircuitTrackCompound());
    AddTask(new RunCircuitsPrim());
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{}

void IncreaseAgilityCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new GoToAndIncreaseAgilityMethod());
}

//***********************************************************
GoToAndIncreaseIntelligenceMethod::GoToAndIncreaseIntelligenceMethod(): HTNMethod("GoToAndIncreaseIntelligenceMethod")
{}

bool GoToAndIncreaseIntelligenceMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void GoToAndIncreaseIntelligenceMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GoToLibraryCompound());
    AddTask(new StudyPrim());
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{}

void IncreaseIntelligenceCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new GoToAndIncreaseIntelligenceMethod());
}

//***********************************************************
HaveItemMethod::HaveItemMethod(EItemType itemType): HTNMethod("HaveItemMethod"), m_itemType(itemType)
{}

bool HaveItemMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    if (GetRaw(state.m_itemCarriedPtr) != nullptr
        && state.m_itemCarriedPtr->m_itemType == m_itemType)
    {
        return true;
    } else {
        return false;
    }
}

void HaveItemMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{}

PickupItemMethod::PickupItemMethod(EItemType itemType): HTNMethod("PickupItemMethod"), m_itemType(itemType)
{}

bool PickupItemMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	for (auto &item : state.m_items)
	{
		if (item->m_itemType == m_itemType
          && item->m_locationClass.location == state.m_location
			&& (item->m_carryingPlayer == nullptr))
		{
			return true;
		}
	}
	return false;
}

void PickupItemMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    for (auto& item : state.m_items)
    {
        if (item->m_itemType == m_itemType
            && item->m_locationClass.location == state.m_location
            && (item->m_carryingPlayer == nullptr))
        {
            AddTask(new PickUpItemByPtrPrim(item));
        }
    }
}

RequestItemMethod::RequestItemMethod(UPlayerData* player, EItemType itemType): HTNMethod("RequestItemMethod"), m_player(player), m_itemType(itemType)
{}

bool RequestItemMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

void RequestItemMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new RequestItemPrim(m_player, m_itemType));
}

GetItemCompound::GetItemCompound(EItemType itemType):
    HTNCompound("GetItemCompound(" + ItemTypeToString(itemType) + ")"),
    m_itemType(itemType)
{}

void GetItemCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    AddMethod(new HaveItemMethod(m_itemType));
    AddMethod(new PickupItemMethod(m_itemType));
    for (auto &p : state.m_playersInTheRoom)
    {
        AddMethod(new RequestItemMethod(p, m_itemType));
    }
}

//***********************************************************
GetBringAndDropItemMethod::GetBringAndDropItemMethod(EItemType itemType, LocationClass &locationClass):
    HTNMethod("GetBringAndDropItemMethod"),
    m_itemType(itemType),
    m_locationClass(locationClass)
{}

bool GetBringAndDropItemMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true; 
}

void GetBringAndDropItemMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new GetItemCompound(m_itemType));

	switch (m_locationClass.location)
	{
	case ELocations::bedroom:
		AddTask(new GoToBedroomCompound());
		break;
	case ELocations::circuitTrack:
		AddTask(new GoToCircuitTrackCompound());
		break;
	case ELocations::gym:
		AddTask(new GoToGymCompound());
		break;
	case ELocations::library:
		AddTask(new GoToLibraryCompound());
		break;
	case ELocations::mainHall:
            AddTask(new GoToMainHallPrim());
		break;
	}

    AddTask(new DropItemPrim());
}

BringItemToLocationCompound::BringItemToLocationCompound(EItemType itemType, LocationClass &locationClass):
    HTNCompound("BringItemToLocationCompound"),
    m_itemType(itemType),
    m_locationClass(locationClass)
{}

void BringItemToLocationCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new GetBringAndDropItemMethod(m_itemType, m_locationClass));
}

//***********************************************************
PickupItemAndAttackMethod::PickupItemAndAttackMethod(SimItemPtr item, UPlayerData* opponent):
    HTNMethod("PickupItemAndAttackMethod"),
    m_item(item),
    m_opponent(opponent)
{}

bool PickupItemAndAttackMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	bool carryingItemAlready = false;
	for (auto &item : state.m_items)
	{
		if ((item->m_carryingPlayer) == state.m_ptrToSelf)
		{
			carryingItemAlready = true;
			break;
		}
	}

    return state.IsInTheRoom(*m_opponent)
        && (m_item->m_locationClass.location == state.m_location)
        && !carryingItemAlready;
}

void PickupItemAndAttackMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new PickUpItemByPtrPrim(m_item));
    AddTask(new PunchPrim(m_opponent));
}

AttackImmediateMethod::AttackImmediateMethod(UPlayerData* opponent):
    HTNMethod("AttackImmediateMethod"),
    m_opponent(opponent)
{}

bool AttackImmediateMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.IsInTheRoom(*m_opponent);
}

void AttackImmediateMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new PunchPrim(m_opponent));
}

AttackCompound::AttackCompound(UPlayerData* opponent):
    HTNCompound("AttackCompound"),
    m_opponent(opponent)
{}

void AttackCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    for (auto &item : state.m_items)
    {
        if (item->m_locationClass.location == state.m_location)
        {
            AddMethod(new PickupItemAndAttackMethod(item, m_opponent));
		}
	}
    AddMethod(new AttackImmediateMethod(m_opponent));
}

AttackMethod::AttackMethod(UPlayerData* opponent):
    HTNMethod("AttackMethod"),
    m_opponent(opponent)
{}

bool AttackMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void AttackMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new AttackCompound(m_opponent));
}

//***********************************************************
EvadeMethod::EvadeMethod(UPlayerData* opponent):
    HTNMethod("EvadeMethod"),
    m_opponent(opponent)
{}

bool EvadeMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    if (state.m_health < 69) {
        for (auto& attacker : state.m_attackers) {
            if (attacker == m_opponent) {
                return true;
            }
        }
    }
    return false;
}

void EvadeMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new EvadePrim(m_opponent));
}

CombatCompound::CombatCompound(UPlayerData* opponent):
    HTNCompound("CombatCompound"),
    m_opponent(opponent)
{}

void CombatCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new EvadeMethod(m_opponent));
    AddMethod(new AttackMethod(m_opponent));
}

//***********************************************************
IncreaseStrengthMissionMethod::IncreaseStrengthMissionMethod(): HTNMethod("IncreaseStrengthMissionMethod")
{}

bool IncreaseStrengthMissionMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_missionClass->m_mission == EMissions::increaseStrength;
}

void IncreaseStrengthMissionMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new IncreaseStrengthCompound());
}

IncreaseAgilityMissionMethod::IncreaseAgilityMissionMethod(): HTNMethod("IncreaseAgilityMissionMethod")
{}

bool IncreaseAgilityMissionMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_missionClass->m_mission == EMissions::increaseAgility;
}

void IncreaseAgilityMissionMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new IncreaseAgilityCompound());
}

IncreaseIntelligenceMissionMethod::IncreaseIntelligenceMissionMethod(): HTNMethod("IncreaseIntelligenceMissionMethod")
{}

bool IncreaseIntelligenceMissionMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_missionClass->m_mission == EMissions::increaseIntelligence;
}

void IncreaseIntelligenceMissionMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new IncreaseIntelligenceCompound());
}

BringItemToRoomMissionMethod::BringItemToRoomMissionMethod():
    HTNMethod("BringItemToRoomMissionMethod")
{}

bool BringItemToRoomMissionMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_missionClass->m_mission == EMissions::bringItemToRoom;
}

void BringItemToRoomMissionMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    AddTask(new BringItemToLocationCompound(state.m_missionClass->m_itemType, state.m_missionClass->m_locationClass));
}

DoMissionCompound::DoMissionCompound():
    HTNCompound("DoMissionCompound")
{}

void DoMissionCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new IncreaseStrengthMissionMethod());
    AddMethod(new IncreaseAgilityMissionMethod());
    AddMethod(new IncreaseIntelligenceMissionMethod());
    AddMethod(new BringItemToRoomMissionMethod());
}

//***********************************************************
PickUpUnneccessaryItemCompound::PickUpUnneccessaryItemCompound():
    HTNCompound("PickUpUnneccessaryItemCompound")
{}

void PickUpUnneccessaryItemCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    for (auto &simItem : state.m_items)
    {
        if (   simItem->m_locationClass.location == state.m_location
            && simItem->m_carryingPlayer == nullptr
        )
            AddMethod(new PickUpItemByPtrMethod(simItem));
    }
}

PickUpUnneccessaryItemMethod::PickUpUnneccessaryItemMethod():
    HTNMethod("PickUpUnneccessaryItemMethod")
{}

bool PickUpUnneccessaryItemMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    return state.m_itemCarriedPtr == nullptr;
}

void PickUpUnneccessaryItemMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new PickUpUnneccessaryItemCompound());
}

//***********************************************************
CombatMethod::CombatMethod(UPlayerData* opponent):
    HTNMethod("CombatMethod"),
    m_opponent(opponent)
{}

bool CombatMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void CombatMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new CombatCompound(m_opponent));
}

DoMissionMethod::DoMissionMethod():
    HTNMethod("DoMissionMethod")
{}

bool DoMissionMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
	return state.m_missionClass->m_mission != EMissions::noMission;
}

void DoMissionMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new DoMissionCompound());
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod(): HTNMethod("IncreaseIntelligenceMethod")
{}

bool IncreaseIntelligenceMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
	return true;
}

void IncreaseIntelligenceMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new IncreaseIntelligenceCompound());
}

//***********************************************************
PickUpItemByPtrMethod::PickUpItemByPtrMethod(SimItemPtr itemFocusPtr):
    HTNMethod("PickUpItemByPtrMethod"),
    m_itemFocusPtr(itemFocusPtr)
{}

bool PickUpItemByPtrMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

void PickUpItemByPtrMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new PickUpItemByPtrPrim(m_itemFocusPtr));
}

//***********************************************************
DropAnyItemImmediateMethod::DropAnyItemImmediateMethod():
    HTNMethod("DropAnyItemImmediateMethod")
{}

bool DropAnyItemImmediateMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

void DropAnyItemImmediateMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new DropItemPrim());
}

//***********************************************************
PrisonerBehaviourCompound::PrisonerBehaviourCompound():
    HTNCompound("PrisonerBehaviourCompound")
{}

void PrisonerBehaviourCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    for (auto &attacker : state.m_attackers)
    {
        AddMethod(new CombatMethod(attacker));
    }
    AddMethod(new DoMissionMethod());
    AddMethod(new PickUpUnneccessaryItemMethod());
	AddMethod(new IncreaseIntelligenceMethod());
}
