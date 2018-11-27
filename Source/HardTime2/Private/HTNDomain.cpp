#include "HTNDomain.hpp"
#include "Locations.h"
#include "HTNPrimitives.hpp"
#include "pLog.hpp"
#include <sstream>
#include "Constants.hpp"

//***********************************************************
GoToLibraryMethod1::GoToLibraryMethod1()
{
    AddTask(new GoToLibrary());
}

bool GoToLibraryMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToLibraryMethod2::GoToLibraryMethod2()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToLibrary());
}

bool GoToLibraryMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{
    AddMethod(new GoToLibraryMethod1());
    AddMethod(new GoToLibraryMethod2());
}

//***********************************************************
GoToGymMethod1::GoToGymMethod1()
{
    AddTask(new GoToGym());
}

bool GoToGymMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToGymMethod2::GoToGymMethod2()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToGym());
}

bool GoToGymMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{
    AddMethod(new GoToGymMethod1());
    AddMethod(new GoToGymMethod2());
}

//***********************************************************
GoToCircuitTrackMethod1::GoToCircuitTrackMethod1()
{
    AddTask(new GoToCircuitTrack());
}

bool GoToCircuitTrackMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToCircuitTrackMethod2::GoToCircuitTrackMethod2()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToCircuitTrack());
}

bool GoToCircuitTrackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{
    AddMethod(new GoToCircuitTrackMethod1());
    AddMethod(new GoToCircuitTrackMethod2());
}

//***********************************************************
GoToBedroomMethod1::GoToBedroomMethod1()
{
    AddTask(new GoToBedroom());
}

bool GoToBedroomMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToBedroomMethod2::GoToBedroomMethod2()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToBedroom());
}

bool GoToBedroomMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{
    AddMethod(new GoToBedroomMethod1());
    AddMethod(new GoToBedroomMethod2());
}

//***********************************************************
IncreaseHealthMethod1::IncreaseHealthMethod1()
{
    AddTask(new Sleep());
}

bool IncreaseHealthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseHealthMethod2::IncreaseHealthMethod2()
{
    AddTask(new GoToBedroomCompound());
    AddTask(new Sleep());
}

bool IncreaseHealthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{
    AddMethod(new IncreaseHealthMethod1());
    AddMethod(new IncreaseHealthMethod2());
}

//***********************************************************
IncreaseStrengthMethod1::IncreaseStrengthMethod1()
{
    AddTask(new UseGym());
}

bool IncreaseStrengthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseStrengthMethod2::IncreaseStrengthMethod2()
{
    AddTask(new GoToGymCompound());
    AddTask(new UseGym());
}

bool IncreaseStrengthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{
    AddMethod(new IncreaseStrengthMethod1());
    AddMethod(new IncreaseStrengthMethod2());
}

//***********************************************************
IncreaseAgilityMethod1::IncreaseAgilityMethod1()
{
    AddTask(new RunCircuits());
}

bool IncreaseAgilityMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseAgilityMethod2::IncreaseAgilityMethod2()
{
    AddTask(new GoToCircuitTrackCompound());
    AddTask(new RunCircuits());
}

bool IncreaseAgilityMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{
    AddMethod(new IncreaseAgilityMethod1());
    AddMethod(new IncreaseAgilityMethod2());
}

//***********************************************************
IncreaseIntelligenceMethod1::IncreaseIntelligenceMethod1()
{
    AddTask(new Study());
}

bool IncreaseIntelligenceMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseIntelligenceMethod2::IncreaseIntelligenceMethod2()
{
    AddTask(new GoToLibraryCompound());
    AddTask(new Study());
}

bool IncreaseIntelligenceMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{
    AddMethod(new IncreaseIntelligenceMethod1());
    AddMethod(new IncreaseIntelligenceMethod2());
}

//***********************************************************
GetItemMethod1::GetItemMethod1(EItemType itemType) : m_itemType(itemType)
{
    AddTask(new PickUpItem2(itemType));
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

GetItemMethod2::GetItemMethod2(UPlayerData* player, EItemType itemType) : m_player(player), m_itemType(itemType)
{
    AddTask(new RequestItemPrim(player, itemType));
}

bool GetItemMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GetItemCompound::GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType) : HTNCompound("GetItemCompound(" + ItemTypeToString(itemType) + ")")
{
	AddMethod(new GetItemMethod1(itemType));
    for (auto &p : htnWorldState.m_playersInTheRoom)
    {
        AddMethod(new GetItemMethod2(p, itemType));
    }
}

//***********************************************************
BringItemToLocationMethod1::BringItemToLocationMethod1(EItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(new DropItem());
}

bool BringItemToLocationMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) &&
		(htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType) &&
		(static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)) == m_locationClass.location);
}

BringItemToLocationMethod2::BringItemToLocationMethod2(EItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
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
}

bool BringItemToLocationMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_itemCarriedPtr != nullptr) &&
		(htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

BringItemToLocationMethod3::BringItemToLocationMethod3(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(new GetItemCompound(htnWorldState, itemType));

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
}

bool BringItemToLocationMethod3::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

BringItemToLocationCompound::BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass) : HTNCompound("BringItemToLocationCompound")
{
    AddMethod(new BringItemToLocationMethod1(itemType, locationClass)); //TODO reuse some of the actions at higher level
    AddMethod(new BringItemToLocationMethod2(itemType, locationClass)); // TODO ie, right now, method 1 2 and 3 all overlap.
    AddMethod(new BringItemToLocationMethod3(htnWorldState, itemType, locationClass));
}

//***********************************************************
AttackMethod1::AttackMethod1(SimActorItem* item, UPlayerData* opponent) : m_item(item), m_opponent(opponent)
{
	m_item = item;
	AddTask(new PickUpItem(m_item));
	AddTask(new Punch(m_opponent));
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

AttackMethod2::AttackMethod2(UPlayerData* opponent) : m_opponent(opponent)
{
    AddTask(new Punch(m_opponent));
}

bool AttackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.IsInTheRoom(m_opponent);
}

AttackCompound::AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent) : HTNCompound("AttackCompound")
{
	for (auto &item : htnWorldState.m_items)
	{
		if (item->m_locationClass.location == static_cast<ELocations>(htnWorldState.m_v.at(WorldE::location)))
		{
			AddMethod(new AttackMethod1(item, opponent));
		}
	}
	AddMethod(new AttackMethod2(opponent));
}

AttackCompoundMethod::AttackCompoundMethod(HTNWorldState &htnWorldState, UPlayerData* opponent)
{
	AddTask(new AttackCompound(htnWorldState, opponent));
}

bool AttackCompoundMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
EvadeMethod::EvadeMethod()
{
	AddTask(new Evade());
}

bool EvadeMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return (htnWorldState.m_v.at(WorldE::health) < 67);
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent) : HTNCompound("CombatCompound")
{
    AddMethod(new EvadeMethod());
    AddMethod(new AttackCompoundMethod(htnWorldState, opponent));
}

//***********************************************************
DoMissionMethod1::DoMissionMethod1()
{
	AddTask(new IncreaseStrengthCompound());
}

bool DoMissionMethod1::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseStrength;
}

DoMissionMethod2::DoMissionMethod2()
{
	AddTask(new IncreaseAgilityCompound());
}

bool DoMissionMethod2::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseAgility;
}

DoMissionMethod3::DoMissionMethod3()
{
	AddTask(new IncreaseIntelligenceCompound());
}

bool DoMissionMethod3::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::increaseIntelligence;
}

DoMissionMethod4::DoMissionMethod4(HTNWorldState &htnWorldState)
{
	AddTask(new BringItemToLocationCompound(htnWorldState, htnWorldState.m_missionClass.m_itemType, htnWorldState.m_missionClass.m_locationClass));  //TODO make construction conditional on 'Preconditions'? Because right now, tasks are constructed regardless of whether their preconditions apply.
}

bool DoMissionMethod4::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission == Missions::bringItemToRoom;
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState) : HTNCompound("DoMissionCompound")
{
    AddMethod(new DoMissionMethod1());
    AddMethod(new DoMissionMethod2());
    AddMethod(new DoMissionMethod3());
    AddMethod(new DoMissionMethod4(htnWorldState));
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent)
{
	AddTask(new CombatCompound(htnWorldState, opponent));
}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState)
{
	AddTask(new DoMissionCompound(htnWorldState));
}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return htnWorldState.m_missionClass.m_mission != Missions::noMission;
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod()
{
	AddTask(new IncreaseIntelligenceCompound());
}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

//***********************************************************
PickUpItemMethod1::PickUpItemMethod1(SimActorItem* itemFocusPtr)
{
    AddTask(new PickUpItem(itemFocusPtr));
}

bool PickUpItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
DropItemMethod1::DropItemMethod1()
{
    AddTask(new DropItem());
}

bool DropItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState) : HTNCompound("PrisonerBehaviourCompound")
{
	/*
	for (int i = 0; i < c_playerCount; i++)
	{
		if (htnWorldState.m_attackers[i])
		{
            		AddMethod(new CombatMethod(htnWorldState, i));
		}
	}*/
	AddMethod(new DoMissionMethod(htnWorldState));
	AddMethod(new IncreaseIntelligenceMethod());
}
