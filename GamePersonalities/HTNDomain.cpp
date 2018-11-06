//
//  HTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNDomain.hpp"
#include "Locations.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "HTNPrimitives.hpp"

//***********************************************************
PickUpItemMethod1::PickUpItemMethod1(SimItem* itemFocusPtr)
{
    AddTask(new PickUpItem(itemFocusPtr));
}

bool PickUpItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
DropItemMethod1::DropItemMethod1(bool keepItem)
{
    AddTask(new DropItem(keepItem));
}

bool DropItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

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
GetItemMethod1::GetItemMethod1(ItemType itemType) : m_itemType(itemType)
{
    AddTask(new PickUpItem2(itemType));
}

bool GetItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_itemType == m_itemType
          && item->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location))
          && (item->m_carryingPlayer == nullptr))
        {
            return true;
        }
    }
    return false;
}

GetItemMethod2::GetItemMethod2(int playerIndex, Player player[], ItemType itemType) : m_playerIndex(playerIndex), m_itemType(itemType)
{
    AddTask(new RequestItemPrim(playerIndex, player, itemType));
}

bool GetItemMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GetItemCompound::GetItemCompound(ItemType itemType, Player player[]) : HTNCompound("GetItemCompound("+ItemTypeToString(itemType)+")")
{
    AddMethod(new GetItemMethod1(itemType));
    for (int i=0; i<c_playerCount; i++)
    {
        AddMethod(new GetItemMethod2(i, player, itemType));
    }
}

//***********************************************************
BringItemToLocationMethod1::BringItemToLocationMethod1(ItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(new DropItem(true));
}

bool BringItemToLocationMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return (htnWorldState.m_itemCarriedPtr != nullptr) &&
        (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType) &&
        (static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == m_locationClass.location);
}

BringItemToLocationMethod2::BringItemToLocationMethod2(ItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
{
    switch(m_locationClass.location)
    {
        case Locations::bedroom:
            AddTask(new GoToBedroomCompound());
            break;
        case Locations::circuitTrack:
            AddTask(new GoToCircuitTrackCompound());
            break;
        case Locations::gym:
            AddTask(new GoToGymCompound());
            break;
        case Locations::library:
            AddTask(new GoToLibraryCompound());
            break;
        case Locations::mainHall:
            AddTask(new GoToMainHall());
            break;
    }
    
    AddTask(new DropItem(true));
}

bool BringItemToLocationMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return (htnWorldState.m_itemCarriedPtr != nullptr) &&
        (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

BringItemToLocationMethod3::BringItemToLocationMethod3(ItemType itemType, LocationClass &locationClass, Player player[]) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(new GetItemCompound(itemType, player));
    
    switch(m_locationClass.location)
    {
        case Locations::bedroom:
            AddTask(new GoToBedroomCompound());
            break;
        case Locations::circuitTrack:
            AddTask(new GoToCircuitTrackCompound());
            break;
        case Locations::gym:
            AddTask(new GoToGymCompound());
            break;
        case Locations::library:
            AddTask(new GoToLibraryCompound());
            break;
        case Locations::mainHall:
            AddTask(new GoToMainHall());
            break;
    }
    
    AddTask(new DropItem(true));
}

bool BringItemToLocationMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return true; 
}

BringItemToLocationCompound::BringItemToLocationCompound(ItemType itemType, LocationClass &locationClass, Player player[]) : HTNCompound("BringItemToLocationCompound")
{
    AddMethod(new BringItemToLocationMethod1(itemType, locationClass)); //TODO reuse some of the actions at higher level
    AddMethod(new BringItemToLocationMethod2(itemType, locationClass)); // TODO ie, right now, method 1 2 and 3 all overlap.
    AddMethod(new BringItemToLocationMethod3(itemType, locationClass, player));
}

//***********************************************************
AttackMethod1::AttackMethod1(SimItem* itemPtr, int opponentIndex)
{
    m_itemPtr = itemPtr;
    AddTask(new PickUpItem(m_itemPtr));
    AddTask(new Punch(opponentIndex));
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
    
    return htnWorldState.m_v.at(WorldE::inSameRoom)
        && (m_itemPtr->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)))
        && !carryingItemAlready;
}

AttackMethod2::AttackMethod2(int opponentIndex)
{
    AddTask(new Punch(opponentIndex));
}

bool AttackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_v.at(WorldE::inSameRoom);
}

AttackCompound::AttackCompound(HTNWorldState &htnWorldState, int opponentIndex) : HTNCompound("AttackCompound")
{
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)))
        {
            AddMethod(new AttackMethod1(item, opponentIndex));
        }
    }
    AddMethod(new AttackMethod2(opponentIndex));
}

AttackCompoundMethod::AttackCompoundMethod(HTNWorldState &htnWorldState, int opponentIndex)
{
    AddTask(new AttackCompound(htnWorldState, opponentIndex));
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
    return (htnWorldState.m_v.at(WorldE::health) < 67) && htnWorldState.m_v.at(WorldE::inSameRoom);
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, int opponentIndex) : HTNCompound("CombatCompound")
{
    AddMethod(new EvadeMethod());
    AddMethod(new AttackCompoundMethod(htnWorldState, opponentIndex));
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

DoMissionMethod4::DoMissionMethod4(HTNWorldState &htnWorldState, Player player[])
{
    AddTask(new BringItemToLocationCompound(htnWorldState.m_missionClass.m_itemType, htnWorldState.m_missionClass.m_locationClass, player));  //TODO make construction conditional on 'Preconditions'? Because right now, tasks are constructed regardless of whether their preconditions apply.
}

bool DoMissionMethod4::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission == Missions::bringItemToRoom;
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState, Player player[]) : HTNCompound("DoMissionCompound")
{
    AddMethod(new DoMissionMethod1());
    AddMethod(new DoMissionMethod2());
    AddMethod(new DoMissionMethod3());
    AddMethod(new DoMissionMethod4(htnWorldState, player));
}

//***********************************************************
PickUpUnneccessaryItemCompound::PickUpUnneccessaryItemCompound(HTNWorldState &htnWorldState) : HTNCompound("PickUpUnneccessaryItemCompound")
{
    for (auto &item : htnWorldState.m_items)
    {
        SimItem* simItem = dynamic_cast<SimItem*>(item);
        if (   simItem->m_locationClass.location == static_cast<Locations>(htnWorldState.m_v.at(WorldE::location))
            && simItem->m_carryingPlayer == nullptr
        )
            AddMethod(new PickUpItemMethod1(simItem));
    }
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, int opponentIndex)
{
    AddTask(new CombatCompound(htnWorldState, opponentIndex));
}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState, Player player[])
{
    AddTask(new DoMissionCompound(htnWorldState, player));
}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission != Missions::noMission;
}

PickUpUnneccessaryItemMethod::PickUpUnneccessaryItemMethod(HTNWorldState &htnWorldState)
{
    AddTask(new PickUpUnneccessaryItemCompound(htnWorldState));
}

bool PickUpUnneccessaryItemMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_itemCarriedPtr == nullptr;
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
PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState, Player player[]) : HTNCompound("PrisonerBehaviourCompound")
{
    for (int i = 0; i < c_playerCount; i++)
    {
        if (htnWorldState.m_attackers[i])
        {
            AddMethod(new CombatMethod(htnWorldState, i));
        }
    }
    AddMethod(new DoMissionMethod(htnWorldState, player));
    AddMethod(new PickUpUnneccessaryItemMethod(htnWorldState));
    AddMethod(new IncreaseIntelligenceMethod());
}