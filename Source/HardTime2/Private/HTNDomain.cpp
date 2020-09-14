#include "HTNDomain.h"
#include "Locations.h"
#include "HTNPrimitives.h"
#include "pLog.h"
#include "PlatformSpecific.h"
#include "ActorItem.h"

//***********************************************************
AlreadyInLibraryMethod::AlreadyInLibraryMethod(): HTNMethod("AlreadyInLibraryMethod")
{}

bool AlreadyInLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_location == ELocations::library;
}

void AlreadyInLibraryMethod::CreateTasks(HTNWorldState const& htnWorldState)
{}

GoToNearbyLibraryMethod::GoToNearbyLibraryMethod(): HTNMethod("GoToNearbyLibraryMethod")
{}

bool GoToNearbyLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyLibraryMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToLibraryPrim());
}

GoToDistantLibraryMethod::GoToDistantLibraryMethod(): HTNMethod("GoToDistantLibraryMethod")
{}

bool GoToDistantLibraryMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantLibraryMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToLibraryPrim());
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{}

void GoToLibraryCompound::CreateMethods(HTNWorldState const& htnWorldState)
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
    return htnWorldState.m_location == ELocations::gym;
}

void AlreadyInGymMethod::CreateTasks(HTNWorldState const& htnWorldState)
{}

GoToNearbyGymMethod::GoToNearbyGymMethod(): HTNMethod("GoToNearbyGymMethod")
{}

bool GoToNearbyGymMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyGymMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToGymPrim());
}

GoToDistantGymMethod::GoToDistantGymMethod(): HTNMethod("GoToDistantGymMethod")
{}

bool GoToDistantGymMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantGymMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToGymPrim());
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{}

void GoToGymCompound::CreateMethods(HTNWorldState const& htnWorldState)
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
    return htnWorldState.m_location == ELocations::circuitTrack;
}

void AlreadyInCircuitTrackMethod::CreateTasks(HTNWorldState const& htnWorldState)
{}

GoToNearbyCircuitTrackMethod::GoToNearbyCircuitTrackMethod(): HTNMethod("GoToNearbyCircuitTrackMethod")
{}

bool GoToNearbyCircuitTrackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyCircuitTrackMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToCircuitTrackPrim());
}

GoToDistantCircuitTrackMethod::GoToDistantCircuitTrackMethod(): HTNMethod("GoToDistantCircuitTrackMethod")
{}

bool GoToDistantCircuitTrackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantCircuitTrackMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToCircuitTrackPrim());
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{}

void GoToCircuitTrackCompound::CreateMethods(HTNWorldState const& htnWorldState)
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
    return htnWorldState.m_location == ELocations::bedroom;
}

void AlreadyInBedroomMethod::CreateTasks(HTNWorldState const& htnWorldState)
{}

GoToNearbyBedroomMethod::GoToNearbyBedroomMethod(): HTNMethod("GoToNearbyBedroomMethod")
{}

bool GoToNearbyBedroomMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToNearbyBedroomMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToBedroomPrim());
}

GoToDistantBedroomMethod::GoToDistantBedroomMethod(): HTNMethod("GoToDistantBedroomMethod")
{}

bool GoToDistantBedroomMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void GoToDistantBedroomMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToMainHallPrim());
    AddTask(new GoToBedroomPrim());
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{}

void GoToBedroomCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void GoToAndIncreaseHealthMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToBedroomCompound());
    AddTask(new SleepPrim());
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{}

void IncreaseHealthCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void GoToAndIncreaseStrengthMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToGymCompound());
    AddTask(new UseGymPrim());
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{}

void IncreaseStrengthCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void GoToAndIncreaseAgilityMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToCircuitTrackCompound());
    AddTask(new RunCircuitsPrim());
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{}

void IncreaseAgilityCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void GoToAndIncreaseIntelligenceMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new GoToLibraryCompound());
    AddTask(new StudyPrim());
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{}

void IncreaseIntelligenceCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void HaveItemMethod::CreateTasks(HTNWorldState const& htnWorldState)
{}

PickupItemMethod::PickupItemMethod(EItemType itemType): HTNMethod("PickupItemMethod"), m_itemType(itemType)
{}

bool PickupItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_itemType == m_itemType
          && item->m_locationClass.location == htnWorldState.m_location
			&& (item->m_carryingPlayer == nullptr))
		{
			return true;
		}
	}
	return false;
}

void PickupItemMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    for (auto& item : htnWorldState.m_items)
    {
        if (item->m_itemType == m_itemType
            && item->m_locationClass.location == htnWorldState.m_location
            && (item->m_carryingPlayer == nullptr))
        {
            AddTask(new PickUpItemByPtrPrim(item));
        }
    }
}

RequestItemMethod::RequestItemMethod(AbstractPlayerData* player, EItemType itemType): HTNMethod("RequestItemMethod"), m_player(player), m_itemType(itemType)
{}

bool RequestItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void RequestItemMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new RequestItemPrim(m_player, m_itemType));
}

GetItemCompound::GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType):
    HTNCompound("GetItemCompound(" + ItemTypeToString(itemType) + ")"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType)
{}

void GetItemCompound::CreateMethods(HTNWorldState const& htnWorldState)
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

void GetBringAndDropItemMethod::CreateTasks(HTNWorldState const& htnWorldState)
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

void BringItemToLocationCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    AddMethod(new GetBringAndDropItemMethod(m_htnWorldState, m_itemType, m_locationClass));
}

//***********************************************************
PickupItemAndAttackMethod::PickupItemAndAttackMethod(SimItemPtr item, AbstractPlayerData* opponent):
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

    return htnWorldState.IsInTheRoom(*m_opponent)
        && (m_item->m_locationClass.location == htnWorldState.m_location)
        && !carryingItemAlready;
}

void PickupItemAndAttackMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new PickUpItemByPtrPrim(m_item));
    AddTask(new PunchPrim(m_opponent));
}

AttackImmediateMethod::AttackImmediateMethod(AbstractPlayerData* opponent):
    HTNMethod("AttackImmediateMethod"),
    m_opponent(opponent)
{}

bool AttackImmediateMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.IsInTheRoom(*m_opponent);
}

void AttackImmediateMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new PunchPrim(m_opponent));
}

AttackCompound::AttackCompound(HTNWorldState &htnWorldState, AbstractPlayerData* opponent):
    HTNCompound("AttackCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

void AttackCompound::CreateMethods(HTNWorldState const& htnWorldState)
		{
    for (auto &item : m_htnWorldState.m_items)
    {
        if (item->m_locationClass.location == m_htnWorldState.m_location)
        {
            AddMethod(new PickupItemAndAttackMethod(item, m_opponent));
		}
	}
    AddMethod(new AttackImmediateMethod(m_opponent));
}

AttackMethod::AttackMethod(HTNWorldState &htnWorldState, AbstractPlayerData* opponent):
    HTNMethod("AttackMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

bool AttackMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void AttackMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new AttackCompound(m_htnWorldState, m_opponent));
}

//***********************************************************
EvadeMethod::EvadeMethod(): HTNMethod("EvadeMethod")
{}

bool EvadeMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_health < 67;
}

void EvadeMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new EvadePrim());
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, AbstractPlayerData* opponent):
    HTNCompound("CombatCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

void CombatCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    AddMethod(new EvadeMethod());
    AddMethod(new AttackMethod(m_htnWorldState, m_opponent));
}

//***********************************************************
IncreaseStrengthMissionMethod::IncreaseStrengthMissionMethod(): HTNMethod("IncreaseStrengthMissionMethod")
{}

bool IncreaseStrengthMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass->m_mission == EMissions::increaseStrength;
}

void IncreaseStrengthMissionMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new IncreaseStrengthCompound());
}

IncreaseAgilityMissionMethod::IncreaseAgilityMissionMethod(): HTNMethod("IncreaseAgilityMissionMethod")
{}

bool IncreaseAgilityMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass->m_mission == EMissions::increaseAgility;
}

void IncreaseAgilityMissionMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new IncreaseAgilityCompound());
}

IncreaseIntelligenceMissionMethod::IncreaseIntelligenceMissionMethod(): HTNMethod("IncreaseIntelligenceMissionMethod")
{}

bool IncreaseIntelligenceMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass->m_mission == EMissions::increaseIntelligence;
}

void IncreaseIntelligenceMissionMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new IncreaseIntelligenceCompound());
}

BringItemToRoomMissionMethod::BringItemToRoomMissionMethod(HTNWorldState &htnWorldState):
    HTNMethod("BringItemToRoomMissionMethod"),
    m_htnWorldState(htnWorldState)
{}

bool BringItemToRoomMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass->m_mission == EMissions::bringItemToRoom;
}

void BringItemToRoomMissionMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new BringItemToLocationCompound(m_htnWorldState, m_htnWorldState.m_missionClass->m_itemType, m_htnWorldState.m_missionClass->m_locationClass));
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState):
    HTNCompound("DoMissionCompound"),
    m_htnWorldState(htnWorldState)
{}

void DoMissionCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    AddMethod(new IncreaseStrengthMissionMethod());
    AddMethod(new IncreaseAgilityMissionMethod());
    AddMethod(new IncreaseIntelligenceMissionMethod());
    AddMethod(new BringItemToRoomMissionMethod(m_htnWorldState));
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, AbstractPlayerData* opponent):
    HTNMethod("CombatMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void CombatMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new CombatCompound(m_htnWorldState, m_opponent));
}

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState):
    HTNMethod("DoMissionMethod"),
    m_htnWorldState(htnWorldState)
{}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass->m_mission != EMissions::noMission;
}

void DoMissionMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new DoMissionCompound(m_htnWorldState));
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod(): HTNMethod("IncreaseIntelligenceMethod")
{}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void IncreaseIntelligenceMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new IncreaseIntelligenceCompound());
}

//***********************************************************
PickUpItemByPtrMethod::PickUpItemByPtrMethod(SimItemPtr itemFocusPtr):
    HTNMethod("PickUpItemByPtrMethod"),
    m_itemFocusPtr(itemFocusPtr)
{}

bool PickUpItemByPtrMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void PickUpItemByPtrMethod::CreateTasks(HTNWorldState const& htnWorldState)
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

void DropAnyItemImmediateMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new DropItemPrim());
}

//***********************************************************
PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState):
    HTNCompound("PrisonerBehaviourCompound"),
    m_htnWorldState(htnWorldState)
{}

void PrisonerBehaviourCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    for (auto &attacker : m_htnWorldState.m_attackers)
    {
        AddMethod(new CombatMethod(m_htnWorldState, attacker));
    }
    AddMethod(new DoMissionMethod(m_htnWorldState));
	AddMethod(new IncreaseIntelligenceMethod());
}
