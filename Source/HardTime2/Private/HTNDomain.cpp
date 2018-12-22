#include "HTNDomain.hpp"
#include "Locations.h"
#include "HTNPrimitives.hpp"
#include "pLog.hpp"

//***********************************************************
GoToLibraryMethod1::GoToLibraryMethod1(): HTNMethod("GoToLibraryMethod1")
{}

bool GoToLibraryMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToLibraryMethod1::GetTasks()
{
    AddTask(new GoToLibrary());
    return m_nodeList;
}

GoToLibraryMethod2::GoToLibraryMethod2(): HTNMethod("GoToLibraryMethod2")
{}

bool GoToLibraryMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToLibraryMethod2::GetTasks()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToLibrary());
    return m_nodeList;
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{
}

HTNMethodList& GoToLibraryCompound::GetMethods()
{
    AddMethod(new GoToLibraryMethod1());
    AddMethod(new GoToLibraryMethod2());
    return m_methods;
}

//***********************************************************
GoToGymMethod1::GoToGymMethod1(): HTNMethod("GoToGymMethod1")
{
}

bool GoToGymMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToGymMethod1::GetTasks()
{
    AddTask(new GoToGym());
    return m_nodeList;
}

GoToGymMethod2::GoToGymMethod2(): HTNMethod("GoToGymMethod2")
{
}

bool GoToGymMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToGymMethod2::GetTasks()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToGym());
    return m_nodeList;
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{
}

HTNMethodList& GoToGymCompound::GetMethods()
{
    AddMethod(new GoToGymMethod1());
    AddMethod(new GoToGymMethod2());
    return m_methods;
}

//***********************************************************
GoToCircuitTrackMethod1::GoToCircuitTrackMethod1(): HTNMethod("GoToCircuitTrackMethod1")
{
}

bool GoToCircuitTrackMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToCircuitTrackMethod1::GetTasks()
{
    AddTask(new GoToCircuitTrack());
    return m_nodeList;
}

GoToCircuitTrackMethod2::GoToCircuitTrackMethod2(): HTNMethod("GoToCircuitTrackMethod2")
{
}

bool GoToCircuitTrackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToCircuitTrackMethod2::GetTasks()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToCircuitTrack());
    return m_nodeList;
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{
}

HTNMethodList& GoToCircuitTrackCompound::GetMethods()
{
    AddMethod(new GoToCircuitTrackMethod1());
    AddMethod(new GoToCircuitTrackMethod2());
    return m_methods;
}

//***********************************************************
GoToBedroomMethod1::GoToBedroomMethod1(): HTNMethod("GoToBedroomMethod1")
{
}

bool GoToBedroomMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToBedroomMethod1::GetTasks()
{
    AddTask(new GoToBedroom());
    return m_nodeList;
}

GoToBedroomMethod2::GoToBedroomMethod2(): HTNMethod("GoToBedroomMethod2")
{
}

bool GoToBedroomMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& GoToBedroomMethod2::GetTasks()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToBedroom());
    return m_nodeList;
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{
}

HTNMethodList& GoToBedroomCompound::GetMethods()
{
    AddMethod(new GoToBedroomMethod1());
    AddMethod(new GoToBedroomMethod2());
    return m_methods;
}

//***********************************************************
IncreaseHealthMethod1::IncreaseHealthMethod1(): HTNMethod("IncreaseHealthMethod1")
{
}

bool IncreaseHealthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseHealthMethod1::GetTasks()
{
    AddTask(new Sleep());
    return m_nodeList;
}

IncreaseHealthMethod2::IncreaseHealthMethod2(): HTNMethod("IncreaseHealthMethod2")
{
}

bool IncreaseHealthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseHealthMethod2::GetTasks()
{
    AddTask(new GoToBedroomCompound());
    AddTask(new Sleep());
    return m_nodeList;
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{
}

HTNMethodList& IncreaseHealthCompound::GetMethods()
{
    AddMethod(new IncreaseHealthMethod1());
    AddMethod(new IncreaseHealthMethod2());
    return m_methods;
}

//***********************************************************
IncreaseStrengthMethod1::IncreaseStrengthMethod1(): HTNMethod("IncreaseStrengthMethod1")
{
}

bool IncreaseStrengthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseStrengthMethod1::GetTasks()
{
    AddTask(new UseGym());
    return m_nodeList;
}

IncreaseStrengthMethod2::IncreaseStrengthMethod2(): HTNMethod("IncreaseStrengthMethod2")
{
}

bool IncreaseStrengthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseStrengthMethod2::GetTasks()
{
    AddTask(new GoToGymCompound());
    AddTask(new UseGym());
    return m_nodeList;
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{
}

HTNMethodList& IncreaseStrengthCompound::GetMethods()
{
    AddMethod(new IncreaseStrengthMethod1());
    AddMethod(new IncreaseStrengthMethod2());
    return m_methods;
}

//***********************************************************
IncreaseAgilityMethod1::IncreaseAgilityMethod1(): HTNMethod("IncreaseAgilityMethod1")
{
}

bool IncreaseAgilityMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseAgilityMethod1::GetTasks()
{
    AddTask(new RunCircuits());
    return m_nodeList;
}

IncreaseAgilityMethod2::IncreaseAgilityMethod2(): HTNMethod("IncreaseAgilityMethod2")
{
}

bool IncreaseAgilityMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseAgilityMethod2::GetTasks()
{
    AddTask(new GoToCircuitTrackCompound());
    AddTask(new RunCircuits());
    return m_nodeList;
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{
}

HTNMethodList& IncreaseAgilityCompound::GetMethods()
{
    AddMethod(new IncreaseAgilityMethod1());
    AddMethod(new IncreaseAgilityMethod2());
    return m_methods;
}

//***********************************************************
IncreaseIntelligenceMethod1::IncreaseIntelligenceMethod1(): HTNMethod("IncreaseIntelligenceMethod1")
{
}

bool IncreaseIntelligenceMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseIntelligenceMethod1::GetTasks()
{
    AddTask(new Study());
    return m_nodeList;
}

IncreaseIntelligenceMethod2::IncreaseIntelligenceMethod2(): HTNMethod("IncreaseIntelligenceMethod2")
{
}

bool IncreaseIntelligenceMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseIntelligenceMethod2::GetTasks()
{
    AddTask(new GoToLibraryCompound());
    AddTask(new Study());
    return m_nodeList;
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{
}

HTNMethodList& IncreaseIntelligenceCompound::GetMethods()
{
    AddMethod(new IncreaseIntelligenceMethod1());
    AddMethod(new IncreaseIntelligenceMethod2());
    return m_methods;
}

//***********************************************************
GetItemMethod1::GetItemMethod1(EItemType itemType): HTNMethod("GetItemMethod1"), m_itemType(itemType)
{
}

bool GetItemMethod1::Preconditions(HTNWorldState &htnWorldState)
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

HTNNodeList& GetItemMethod1::GetTasks()
{
    AddTask(new PickUpItem2(m_itemType));
    return m_nodeList;
}

GetItemMethod2::GetItemMethod2(UPlayerData* player, EItemType itemType): HTNMethod("GetItemMethod2"), m_player(player), m_itemType(itemType)
{
}

bool GetItemMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& GetItemMethod2::GetTasks()
{
    AddTask(new RequestItemPrim(m_player, m_itemType));
    return m_nodeList;
}

GetItemCompound::GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType):
    HTNCompound("GetItemCompound(" + ItemTypeToString(itemType) + ")"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType)
{
}

HTNMethodList& GetItemCompound::GetMethods()
{
    AddMethod(new GetItemMethod1(m_itemType));
    //for (auto &p : m_htnWorldState.m_playersInTheRoom)
    //{
        //AddMethod(new GetItemMethod2(p, m_itemType));
    //}
    return m_methods;
}

//***********************************************************
BringItemToLocationMethod1::BringItemToLocationMethod1(EItemType itemType, LocationClass &locationClass):
    HTNMethod("BringItemToLocationMethod1"),
    m_itemType(itemType),
    m_locationClass(locationClass)
{
}

bool BringItemToLocationMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr.Get() != nullptr) &&
		(htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType) &&
		(static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == m_locationClass.location);
}

HTNNodeList& BringItemToLocationMethod1::GetTasks()
{
    AddTask(new DropItem());
    return m_nodeList;
}

BringItemToLocationMethod2::BringItemToLocationMethod2(EItemType itemType, LocationClass &locationClass):
    HTNMethod("BringItemToLocationMethod2"),
    m_itemType(itemType),
    m_locationClass(locationClass)
{
}

bool BringItemToLocationMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return (htnWorldState.m_itemCarriedPtr.Get() != nullptr) &&
        (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

HTNNodeList& BringItemToLocationMethod2::GetTasks()
{
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
		AddTask(new GoToMainHall());
		break;
	}

    AddTask(new DropItem());

    return m_nodeList;
}

BringItemToLocationMethod3::BringItemToLocationMethod3(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass):
    HTNMethod("BringItemToLocationMethod3"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType),
    m_locationClass(locationClass)
{
}

bool BringItemToLocationMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return true; 
}

HTNNodeList& BringItemToLocationMethod3::GetTasks()
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
		AddTask(new GoToMainHall());
		break;
	}

    AddTask(new DropItem());

    return m_nodeList;
}

BringItemToLocationCompound::BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass):
    HTNCompound("BringItemToLocationCompound"),
    m_htnWorldState(htnWorldState),
    m_itemType(itemType),
    m_locationClass(locationClass)
{
}

HTNMethodList& BringItemToLocationCompound::GetMethods()
{
    AddMethod(new BringItemToLocationMethod1(m_itemType, m_locationClass)); //TODO reuse some of the actions at higher level
    AddMethod(new BringItemToLocationMethod2(m_itemType, m_locationClass)); // TODO ie, right now, method 1 2 and 3 all overlap.
    AddMethod(new BringItemToLocationMethod3(m_htnWorldState, m_itemType, m_locationClass));
    return m_methods;
}

//***********************************************************
AttackMethod1::AttackMethod1(SimActorItemPtr item, UPlayerData* opponent):
    HTNMethod("AttackMethod1"),
    m_item(item),
    m_opponent(opponent)
{
}

bool AttackMethod1::Preconditions(HTNWorldState &htnWorldState)
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

HTNNodeList& AttackMethod1::GetTasks()
{
    AddTask(new PickUpItem(m_item));
    AddTask(new Punch(m_opponent));
    return m_nodeList;
}

AttackMethod2::AttackMethod2(UPlayerData* opponent):
    HTNMethod("AttackMethod2"),
    m_opponent(opponent)
{
}

bool AttackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.IsInTheRoom(m_opponent);
}

HTNNodeList& AttackMethod2::GetTasks()
{
    AddTask(new Punch(m_opponent));
    return m_nodeList;
}

AttackCompound::AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNCompound("AttackCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
	{
}

HTNMethodList& AttackCompound::GetMethods()
		{
    for (auto &item : m_htnWorldState.m_items)
    {
        if (item->m_locationClass.location == static_cast<ELocations>(m_htnWorldState.m_v.at(WorldE::location)))
        {
            AddMethod(new AttackMethod1(item, m_opponent));
		}
	}
    AddMethod(new AttackMethod2(m_opponent));
    return m_methods;
}

AttackCompoundMethod::AttackCompoundMethod(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNMethod("AttackCompoundMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{
}

bool AttackCompoundMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& AttackCompoundMethod::GetTasks()
{
    AddTask(new AttackCompound(m_htnWorldState, m_opponent));
    return m_nodeList;
}

//***********************************************************
EvadeMethod::EvadeMethod(): HTNMethod("EvadeMethod")
{
}

bool EvadeMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_v.at(WorldE::health) < 67);
}

HTNNodeList& EvadeMethod::GetTasks()
{
    AddTask(new Evade());
    return m_nodeList;
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNCompound("CombatCompound"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{
}

HTNMethodList& CombatCompound::GetMethods()
{
    AddMethod(new EvadeMethod());
    AddMethod(new AttackCompoundMethod(m_htnWorldState, m_opponent));
    return m_methods;
}

//***********************************************************
DoMissionMethod1::DoMissionMethod1(): HTNMethod("DoMissionMethod1")
{
}

bool DoMissionMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseStrength;
}

HTNNodeList& DoMissionMethod1::GetTasks()
{
    AddTask(new IncreaseStrengthCompound());
    return m_nodeList;
}

DoMissionMethod2::DoMissionMethod2(): HTNMethod("DoMissionMethod2")
{
}

bool DoMissionMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseAgility;
}

HTNNodeList& DoMissionMethod2::GetTasks()
{
    AddTask(new IncreaseAgilityCompound());
    return m_nodeList;
}

DoMissionMethod3::DoMissionMethod3(): HTNMethod("DoMissionMethod3")
{
}

bool DoMissionMethod3::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseIntelligence;
}

HTNNodeList& DoMissionMethod3::GetTasks()
{
    AddTask(new IncreaseIntelligenceCompound());
    return m_nodeList;
}

DoMissionMethod4::DoMissionMethod4(HTNWorldState &htnWorldState):
    HTNMethod("DoMissionMethod4"),
    m_htnWorldState(htnWorldState)
{
}

bool DoMissionMethod4::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::bringItemToRoom;
}

HTNNodeList& DoMissionMethod4::GetTasks()
{
    AddTask(new BringItemToLocationCompound(m_htnWorldState, m_htnWorldState.m_missionClass.m_itemType, m_htnWorldState.m_missionClass.m_locationClass));
    return m_nodeList;
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState):
    HTNCompound("DoMissionCompound"),
    m_htnWorldState(htnWorldState)
{
}

HTNMethodList& DoMissionCompound::GetMethods()
{
    AddMethod(new DoMissionMethod1());
    AddMethod(new DoMissionMethod2());
    AddMethod(new DoMissionMethod3());
    AddMethod(new DoMissionMethod4(m_htnWorldState));
    return m_methods;
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent):
    HTNMethod("CombatMethod"),
    m_htnWorldState(htnWorldState),
    m_opponent(opponent)
{
}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& CombatMethod::GetTasks()
{
    AddTask(new CombatCompound(m_htnWorldState, m_opponent));
    return m_nodeList;
}

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState):
    HTNMethod("DoMissionMethod"),
    m_htnWorldState(htnWorldState)
{
}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission != Missions::noMission;
}

HTNNodeList& DoMissionMethod::GetTasks()
{
    AddTask(new DoMissionCompound(m_htnWorldState));
    return m_nodeList;
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod(): HTNMethod("IncreaseIntelligenceMethod")
{
}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

HTNNodeList& IncreaseIntelligenceMethod::GetTasks()
{
    AddTask(new IncreaseIntelligenceCompound());
    return m_nodeList;
}

//***********************************************************
PickUpItemMethod1::PickUpItemMethod1(SimActorItemPtr itemFocusPtr):
    HTNMethod("PickUpItemMethod1"),
    m_itemFocusPtr(itemFocusPtr)
{
}

bool PickUpItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& PickUpItemMethod1::GetTasks()
{
    AddTask(new PickUpItem(m_itemFocusPtr));
    return m_nodeList;
}

//***********************************************************
DropItemMethod1::DropItemMethod1():
    HTNMethod("DropItemMethod1")
{
}

bool DropItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& DropItemMethod1::GetTasks()
{
    AddTask(new DropItem());
    return m_nodeList;
}

//***********************************************************
PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState):
    HTNCompound("PrisonerBehaviourCompound"),
    m_htnWorldState(htnWorldState)
{
}

HTNMethodList& PrisonerBehaviourCompound::GetMethods()
{
/*
    for (auto &attacker : m_htnWorldState.m_attackers)
    {
        AddMethod(new CombatMethod(m_htnWorldState, attacker));
    }
*/
    AddMethod(new DoMissionMethod(m_htnWorldState));
	AddMethod(new IncreaseIntelligenceMethod());
    return m_methods;
}
