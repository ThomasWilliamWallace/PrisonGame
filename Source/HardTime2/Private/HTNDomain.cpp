#include "HTNDomain.hpp"
#include "Locations.h"
#include "HTNPrimitives.hpp"
#include "pLog.hpp"
#include "PlatformSpecific.hpp"

//***********************************************************
AlreadyInLibraryMethod::AlreadyInLibraryMethod(): HTNMethod("AlreadyInLibraryMethod")
{}

bool AlreadyInLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::library;
}

void AlreadyInLibraryMethod::CreateTasks()
{}

GoToNearbyLibraryMethod::GoToNearbyLibraryMethod(): HTNMethod("GoToNearbyLibraryMethod")
{}

bool GoToNearbyLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyLibraryMethod::CreateTasks()
{
    AddTask(new GoToLibraryPrim());
}

GoToDistantLibraryMethod::GoToDistantLibraryMethod(): HTNMethod("GoToDistantLibraryMethod")
{}

bool GoToDistantLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantLibraryMethod::CreateTasks()
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToLibraryPrim());
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{}

void GoToLibraryCompound::CreateMethods()
{
    AddMethod(new AlreadyInLibraryMethod());
    AddMethod(new GoToNearbyLibraryMethod());
    AddMethod(new GoToDistantLibraryMethod());
}

//***********************************************************
AlreadyInGymMethod::AlreadyInGymMethod(): HTNMethod("AlreadyInGymMethod")
{}

bool AlreadyInGymMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::gym;
}

void AlreadyInGymMethod::CreateTasks()
{}

GoToNearbyGymMethod::GoToNearbyGymMethod(): HTNMethod("GoToNearbyGymMethod")
{}

bool GoToNearbyGymMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyGymMethod::CreateTasks()
{
    AddTask(new GoToGymPrim());
}

GoToDistantGymMethod::GoToDistantGymMethod(): HTNMethod("GoToDistantGymMethod")
{}

bool GoToDistantGymMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantGymMethod::CreateTasks()
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToGymPrim());
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{}

void GoToGymCompound::CreateMethods()
{
    AddMethod(new AlreadyInGymMethod());
    AddMethod(new GoToNearbyGymMethod());
    AddMethod(new GoToDistantGymMethod());
}

//***********************************************************
AlreadyInCircuitTrackMethod::AlreadyInCircuitTrackMethod(): HTNMethod("AlreadyInCircuitTrackMethod")
{}

bool AlreadyInCircuitTrackMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::circuitTrack;
}

void AlreadyInCircuitTrackMethod::CreateTasks()
{}

GoToNearbyCircuitTrackMethod::GoToNearbyCircuitTrackMethod(): HTNMethod("GoToNearbyCircuitTrackMethod")
{}

bool GoToNearbyCircuitTrackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyCircuitTrackMethod::CreateTasks()
{
    AddTask(new GoToCircuitTrackPrim());
}

GoToDistantCircuitTrackMethod::GoToDistantCircuitTrackMethod(): HTNMethod("GoToDistantCircuitTrackMethod")
{}

bool GoToDistantCircuitTrackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantCircuitTrackMethod::CreateTasks()
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToCircuitTrackPrim());
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{}

void GoToCircuitTrackCompound::CreateMethods()
{
    AddMethod(new AlreadyInCircuitTrackMethod());
    AddMethod(new GoToNearbyCircuitTrackMethod());
    AddMethod(new GoToDistantCircuitTrackMethod());
}

//***********************************************************
AlreadyInBedroomMethod::AlreadyInBedroomMethod(): HTNMethod("AlreadyInBedroomMethod")
{}

bool AlreadyInBedroomMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == ELocations::bedroom;
}

void AlreadyInBedroomMethod::CreateTasks()
{}

GoToNearbyBedroomMethod::GoToNearbyBedroomMethod(): HTNMethod("GoToNearbyBedroomMethod")
{}

bool GoToNearbyBedroomMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyBedroomMethod::CreateTasks()
{
    AddTask(new GoToBedroomPrim());
}

GoToDistantBedroomMethod::GoToDistantBedroomMethod(): HTNMethod("GoToDistantBedroomMethod")
{}

bool GoToDistantBedroomMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantBedroomMethod::CreateTasks()
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToBedroomPrim());
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{}

void GoToBedroomCompound::CreateMethods()
{
    AddMethod(new AlreadyInBedroomMethod());
    AddMethod(new GoToNearbyBedroomMethod());
    AddMethod(new GoToDistantBedroomMethod());
}

//***********************************************************
GoToAndIncreaseHealthMethod::GoToAndIncreaseHealthMethod(): HTNMethod("GoToAndIncreaseHealthMethod")
{}

bool GoToAndIncreaseHealthMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToAndIncreaseHealthMethod::CreateTasks()
{
    AddTask(new GoToBedroomCompound());
    AddTask(new SleepPrim());
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{}

void IncreaseHealthCompound::CreateMethods()
{
    AddMethod(new GoToAndIncreaseHealthMethod());
}

//***********************************************************
GoToAndIncreaseStrengthMethod::GoToAndIncreaseStrengthMethod(): HTNMethod("GoToAndIncreaseStrengthMethod")
{}

bool GoToAndIncreaseStrengthMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToAndIncreaseStrengthMethod::CreateTasks()
{
    AddTask(new GoToGymCompound());
    AddTask(new UseGymPrim());
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{}

void IncreaseStrengthCompound::CreateMethods()
{
    AddMethod(new GoToAndIncreaseStrengthMethod());
}

//***********************************************************
GoToAndIncreaseAgilityMethod::GoToAndIncreaseAgilityMethod(): HTNMethod("GoToAndIncreaseAgilityMethod")
{}

bool GoToAndIncreaseAgilityMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToAndIncreaseAgilityMethod::CreateTasks()
{
    AddTask(new GoToCircuitTrackCompound());
    AddTask(new RunCircuitsPrim());
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{}

void IncreaseAgilityCompound::CreateMethods()
{
    AddMethod(new GoToAndIncreaseAgilityMethod());
}

//***********************************************************
GoToAndIncreaseIntelligenceMethod::GoToAndIncreaseIntelligenceMethod(): HTNMethod("GoToAndIncreaseIntelligenceMethod")
{}

bool GoToAndIncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToAndIncreaseIntelligenceMethod::CreateTasks()
{
    AddTask(new GoToLibraryCompound());
    AddTask(new StudyPrim());
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{}

void IncreaseIntelligenceCompound::CreateMethods()
{
    AddMethod(new GoToAndIncreaseIntelligenceMethod());
}

//***********************************************************
HaveItemMethod::HaveItemMethod(EItemType itemType): HTNMethod("HaveItemMethod"), m_itemType(itemType)
{}

bool HaveItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
    if (GetRaw(htnWorldState.m_itemCarriedPtr) != nullptr
        && htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType)
    {
        return true;
    } else {
        return false;
    }
}

void HaveItemMethod::CreateTasks()
{}

PickupItemMethod::PickupItemMethod(EItemType itemType): HTNMethod("PickupItemMethod"), m_itemType(itemType)
{}

bool PickupItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_itemType == m_itemType
			&& item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location))
			&& (item->m_carryingPlayer == nullptr))
		{
			return true;
		}
	}
	return false;
}

void PickupItemMethod::CreateTasks()
{
    AddTask(new PickUpItemByTypePrim(m_itemType));
}

RequestItemMethod::RequestItemMethod(UPlayerData* player, EItemType itemType): HTNMethod("RequestItemMethod"), m_player(player), m_itemType(itemType)
{}

bool RequestItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void RequestItemMethod::CreateTasks()
{
    AddTask(new RequestItemPrim(m_player, m_itemType));
}

GetItemCompound::GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType):
    HTNCompound("GetItemCompound(" + ItemTypeToString(itemType) + ")"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType)
{}

void GetItemCompound::CreateMethods()
{
    AddMethod(new HaveItemMethod(m_itemType));
    AddMethod(new PickupItemMethod(m_itemType));
    for (auto &p : m_htnWorldState.m_playersInTheRoom)
    {
        AddMethod(new RequestItemMethod(p, m_itemType));
    }
}

//***********************************************************
GetBringAndDropItemMethod::GetBringAndDropItemMethod(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass):
    HTNMethod("GetBringAndDropItemMethod"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType),
    m_locationClass(locationClass)
{}

bool GetBringAndDropItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true; 
}

void GetBringAndDropItemMethod::CreateTasks()
{
    AddTask(new GetItemCompound(m_htnWorldState, m_itemType));

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

BringItemToLocationCompound::BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass):
    HTNCompound("BringItemToLocationCompound"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType),
    m_locationClass(locationClass)
{}

void BringItemToLocationCompound::CreateMethods()
{
    AddMethod(new GetBringAndDropItemMethod(m_htnWorldState, m_itemType, m_locationClass));
}

//***********************************************************
PickupItemAndAttackMethod::PickupItemAndAttackMethod(SimActorItemPtr item, UPlayerData* opponent):
    HTNMethod("PickupItemAndAttackMethod"),
    m_item(item),
    m_opponent(opponent)
{}

bool PickupItemAndAttackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	bool carryingItemAlready = false;
	for (auto &item : htnWorldState.m_items)
	{
		if ((item->m_carryingPlayer) == htnWorldState.m_ptrToSelf)
		{
			carryingItemAlready = true;
			break;
		}
	}

    return htnWorldState.IsInTheRoom(m_opponent)
        && (m_item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)))
        && !carryingItemAlready;
}

void PickupItemAndAttackMethod::CreateTasks()
{
    AddTask(new PickUpItemByPtrPrim(m_item));
    AddTask(new PunchPrim(m_opponent));
}

AttackImmediateMethod::AttackImmediateMethod(UPlayerData* opponent):
    HTNMethod("AttackImmediateMethod"),
    m_opponent(opponent)
{}

bool AttackImmediateMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.IsInTheRoom(m_opponent);
}

void AttackImmediateMethod::CreateTasks()
{
    AddTask(new PunchPrim(m_opponent));
}

AttackCompound::AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNCompound("AttackCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

void AttackCompound::CreateMethods()
		{
    for (auto &item : m_htnWorldState.m_items)
    {
        if (item->m_locationClass.location == static_cast<ELocations>(m_htnWorldState.m_v.at(WorldE::location)))
        {
            AddMethod(new PickupItemAndAttackMethod(item, m_opponent));
		}
	}
    AddMethod(new AttackImmediateMethod(m_opponent));
}

AttackMethod::AttackMethod(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNMethod("AttackMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

bool AttackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void AttackMethod::CreateTasks()
{
    AddTask(new AttackCompound(m_htnWorldState, m_opponent));
}

//***********************************************************
EvadeMethod::EvadeMethod(): HTNMethod("EvadeMethod")
{}

bool EvadeMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_v.at(WorldE::health) < 67);
}

void EvadeMethod::CreateTasks()
{
    AddTask(new EvadePrim());
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNCompound("CombatCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

void CombatCompound::CreateMethods()
{
    AddMethod(new EvadeMethod());
    AddMethod(new AttackMethod(m_htnWorldState, m_opponent));
}

//***********************************************************
IncreaseStrengthMissionMethod::IncreaseStrengthMissionMethod(): HTNMethod("IncreaseStrengthMissionMethod")
{}

bool IncreaseStrengthMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseStrength;
}

void IncreaseStrengthMissionMethod::CreateTasks()
{
    AddTask(new IncreaseStrengthCompound());
}

IncreaseAgilityMissionMethod::IncreaseAgilityMissionMethod(): HTNMethod("IncreaseAgilityMissionMethod")
{}

bool IncreaseAgilityMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseAgility;
}

void IncreaseAgilityMissionMethod::CreateTasks()
{
    AddTask(new IncreaseAgilityCompound());
}

IncreaseIntelligenceMissionMethod::IncreaseIntelligenceMissionMethod(): HTNMethod("IncreaseIntelligenceMissionMethod")
{}

bool IncreaseIntelligenceMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseIntelligence;
}

void IncreaseIntelligenceMissionMethod::CreateTasks()
{
    AddTask(new IncreaseIntelligenceCompound());
}

BringItemToRoomMissionMethod::BringItemToRoomMissionMethod(HTNWorldState &htnWorldState):
    HTNMethod("BringItemToRoomMissionMethod"),
    m_htnWorldState(htnWorldState)
{}

bool BringItemToRoomMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::bringItemToRoom;
}

void BringItemToRoomMissionMethod::CreateTasks()
{
    AddTask(new BringItemToLocationCompound(m_htnWorldState, m_htnWorldState.m_missionClass.m_itemType, m_htnWorldState.m_missionClass.m_locationClass));
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState):
    HTNCompound("DoMissionCompound"),
    m_htnWorldState(htnWorldState)
{}

void DoMissionCompound::CreateMethods()
{
    AddMethod(new IncreaseStrengthMissionMethod());
    AddMethod(new IncreaseAgilityMissionMethod());
    AddMethod(new IncreaseIntelligenceMissionMethod());
    AddMethod(new BringItemToRoomMissionMethod(m_htnWorldState));
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNMethod("CombatMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void CombatMethod::CreateTasks()
{
    AddTask(new CombatCompound(m_htnWorldState, m_opponent));
}

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState):
    HTNMethod("DoMissionMethod"),
    m_htnWorldState(htnWorldState)
{}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission != Missions::noMission;
}

void DoMissionMethod::CreateTasks()
{
    AddTask(new DoMissionCompound(m_htnWorldState));
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod(): HTNMethod("IncreaseIntelligenceMethod")
{}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void IncreaseIntelligenceMethod::CreateTasks()
{
    AddTask(new IncreaseIntelligenceCompound());
}

//***********************************************************
PickUpItemByPtrMethod::PickUpItemByPtrMethod(SimActorItemPtr itemFocusPtr):
    HTNMethod("PickUpItemByPtrMethod"),
    m_itemFocusPtr(itemFocusPtr)
{}

bool PickUpItemByPtrMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void PickUpItemByPtrMethod::CreateTasks()
{
    AddTask(new PickUpItemByPtrPrim(m_itemFocusPtr));
}

//***********************************************************
DropAnyItemImmediateMethod::DropAnyItemImmediateMethod():
    HTNMethod("DropAnyItemImmediateMethod")
{}

bool DropAnyItemImmediateMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void DropAnyItemImmediateMethod::CreateTasks()
{
    AddTask(new DropItemPrim());
}

//***********************************************************
PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState):
    HTNCompound("PrisonerBehaviourCompound"),
    m_htnWorldState(htnWorldState)
{}

void PrisonerBehaviourCompound::CreateMethods()
{
/*
    for (auto &attacker : m_htnWorldState.m_attackers)
    {
        AddMethod(new CombatMethod(m_htnWorldState, attacker));
    }
*/
    AddMethod(new DoMissionMethod(m_htnWorldState));
	AddMethod(new IncreaseIntelligenceMethod());
}
