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

//Start HTNPrimitives****************************************
//***********************************************************
Study::Study() : HTNPrimitive("Study") {}

void Study::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::intelligence) += 1;
    return;
}

Actions Study::Operator(int playerIndex, Player player[], World &world)
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

Actions Sleep::Operator(int playerIndex, Player player[], World &world)
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

Actions UseGym::Operator(int playerIndex, Player player[], World &world)
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

Actions RunCircuits::Operator(int playerIndex, Player player[], World &world)
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

Actions GoToGym::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::goToGym;
}

bool GoToGym::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

//***********************************************************
GoToLibrary::GoToLibrary() : HTNPrimitive("GoToLibrary") {}

void GoToLibrary::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::library);
    return;
}

Actions GoToLibrary::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::goToLibrary;
}

bool GoToLibrary::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

//***********************************************************
GoToBedroom::GoToBedroom() : HTNPrimitive("GoToBedroom") {}

void GoToBedroom::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::bedroom);
    return;
}

Actions GoToBedroom::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::goToBedroom;
}

bool GoToBedroom::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

//***********************************************************
GoToCircuitTrack::GoToCircuitTrack() : HTNPrimitive("GoToCircuitTrack") {}

void GoToCircuitTrack::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::circuitTrack);
    return;
}

Actions GoToCircuitTrack::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::goToCircuitTrack;
}

bool GoToCircuitTrack::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

//***********************************************************
GoToMainHall::GoToMainHall() : HTNPrimitive("GoToMainHall") {}

void GoToMainHall::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::mainHall);
    return;
}

Actions GoToMainHall::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::goToMainHall;
}

bool GoToMainHall::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) != Locations::mainHall;
}

//***********************************************************
Drink::Drink() : HTNPrimitive("Drink") {}

void Drink::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::intelligence) -= 1;
    return;
}

Actions Drink::Operator(int playerIndex, Player player[], World &world)
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

Actions Punch::Operator(int playerIndex, Player player[], World &world)
{
    player[playerIndex].playerTarget = m_targetPlayerIndex;
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

Actions Evade::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::evade;
}

bool Evade::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
PickUpItem::PickUpItem(Item* itemFocusPtr) : HTNPrimitive("PickUpItem"), m_itemFocusPtr(itemFocusPtr) {}

void PickUpItem::Effect(HTNWorldState &htnWorldState)
{
    m_itemFocusPtr->m_carryingPlayer = htnWorldState.m_ptrToSelf;
}

Actions PickUpItem::Operator(int playerIndex, Player player[], World &world)
{
    player[playerIndex].itemFocusPtr = m_itemFocusPtr;
    return Actions::pickUpItem;
}

bool PickUpItem::Preconditions(HTNWorldState &htnWorldState)
{
    //TODO hook this into the actions code
    if (m_itemFocusPtr != nullptr)
    {
        if (static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == m_itemFocusPtr->m_locationClass.location)
        {
            if (m_itemFocusPtr->m_carryingPlayer == nullptr)
            {
                return true;
            }
        }
    }
    return false;
}

void PickUpItem::PointToRealItems()
{
    m_itemFocusPtr = &((static_cast<SimItem*>(m_itemFocusPtr))->m_realItem);
}

//***********************************************************
DropItem::DropItem(Item* itemFocusPtr) : HTNPrimitive("DropItem"), m_itemFocusPtr(itemFocusPtr) {}

void DropItem::Effect(HTNWorldState &htnWorldState)
{
    m_itemFocusPtr->m_locationClass.location = static_cast<Locations>(htnWorldState.m_v.at(WorldE::location));
    m_itemFocusPtr->m_carryingPlayer = nullptr;
}

Actions DropItem::Operator(int playerIndex, Player player[], World &world)
{
    player[playerIndex].itemFocusPtr = m_itemFocusPtr;
    return Actions::dropItem;
}

bool DropItem::Preconditions(HTNWorldState &htnWorldState)
{
    return m_itemFocusPtr != nullptr; //TODO hook this into the actions code
}

void DropItem::PointToRealItems()
{
    m_itemFocusPtr = &((static_cast<SimItem*>(m_itemFocusPtr))->m_realItem);
}

//Start HTNCompounds*****************************************
//***********************************************************
GoToLibraryMethod1::GoToLibraryMethod1()
{
    AddTask(HTNPrimitivePtr(new GoToLibrary()));
}

bool GoToLibraryMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToLibraryMethod2::GoToLibraryMethod2()
{
    AddTask(HTNPrimitivePtr(new GoToMainHall()));
    AddTask(HTNPrimitivePtr(new GoToLibrary()));
}

bool GoToLibraryMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToLibraryCompound::GoToLibraryCompound() : HTNCompound("GoToLibraryCompound")
{
    m_methods.push_back(HTNMethodPtr(new GoToLibraryMethod1()));
    m_methods.push_back(HTNMethodPtr(new GoToLibraryMethod2()));
}

//***********************************************************
GoToGymMethod1::GoToGymMethod1()
{
    AddTask(HTNPrimitivePtr(new GoToGym()));
}

bool GoToGymMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToGymMethod2::GoToGymMethod2()
{
    AddTask(HTNPrimitivePtr(new GoToMainHall()));
    AddTask(HTNPrimitivePtr(new GoToGym()));
}

bool GoToGymMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToGymCompound::GoToGymCompound() : HTNCompound("GoToGymCompound")
{
    m_methods.push_back(HTNMethodPtr(new GoToGymMethod1()));
    m_methods.push_back(HTNMethodPtr(new GoToGymMethod2()));
}

//***********************************************************
GoToCircuitTrackMethod1::GoToCircuitTrackMethod1()
{
    AddTask(HTNPrimitivePtr(new GoToCircuitTrack()));
}

bool GoToCircuitTrackMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToCircuitTrackMethod2::GoToCircuitTrackMethod2()
{
    AddTask(HTNPrimitivePtr(new GoToMainHall()));
    AddTask(HTNPrimitivePtr(new GoToCircuitTrack()));
}

bool GoToCircuitTrackMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToCircuitTrackCompound::GoToCircuitTrackCompound() : HTNCompound("GoToCircuitTrackCompound")
{
    m_methods.push_back(HTNMethodPtr(new GoToCircuitTrackMethod1()));
    m_methods.push_back(HTNMethodPtr(new GoToCircuitTrackMethod2()));
}

//***********************************************************
GoToBedroomMethod1::GoToBedroomMethod1()
{
    AddTask(HTNPrimitivePtr(new GoToBedroom()));
}

bool GoToBedroomMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToBedroomMethod2::GoToBedroomMethod2()
{
    AddTask(HTNPrimitivePtr(new GoToMainHall()));
    AddTask(HTNPrimitivePtr(new GoToBedroom()));
}

bool GoToBedroomMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GoToBedroomCompound::GoToBedroomCompound() : HTNCompound("GoToBedroomCompound")
{
    m_methods.push_back(HTNMethodPtr(new GoToBedroomMethod1()));
    m_methods.push_back(HTNMethodPtr(new GoToBedroomMethod2()));
}

//***********************************************************
IncreaseHealthMethod1::IncreaseHealthMethod1()
{
    AddTask(HTNPrimitivePtr(new Sleep()));
}

bool IncreaseHealthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseHealthMethod2::IncreaseHealthMethod2()
{
    AddTask(HTNCompoundPtr(new GoToBedroomCompound()));
    AddTask(HTNPrimitivePtr(new Sleep()));
}

bool IncreaseHealthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseHealthCompound::IncreaseHealthCompound() : HTNCompound("IncreaseHealthCompound")
{
    m_methods.push_back(HTNMethodPtr(new IncreaseHealthMethod1()));
    m_methods.push_back(HTNMethodPtr(new IncreaseHealthMethod2()));
}

//***********************************************************
IncreaseStrengthMethod1::IncreaseStrengthMethod1()
{
    AddTask(HTNPrimitivePtr(new UseGym()));
}

bool IncreaseStrengthMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseStrengthMethod2::IncreaseStrengthMethod2()
{
    AddTask(HTNCompoundPtr(new GoToGymCompound()));
    AddTask(HTNPrimitivePtr(new UseGym()));
}

bool IncreaseStrengthMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseStrengthCompound::IncreaseStrengthCompound() : HTNCompound("IncreaseStrengthCompound")
{
    m_methods.push_back(HTNMethodPtr(new IncreaseStrengthMethod1()));
    m_methods.push_back(HTNMethodPtr(new IncreaseStrengthMethod2()));
}

//***********************************************************
IncreaseAgilityMethod1::IncreaseAgilityMethod1()
{
    AddTask(HTNPrimitivePtr(new RunCircuits()));
}

bool IncreaseAgilityMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseAgilityMethod2::IncreaseAgilityMethod2()
{
    AddTask(HTNCompoundPtr(new GoToCircuitTrackCompound()));
    AddTask(HTNPrimitivePtr(new RunCircuits()));
}

bool IncreaseAgilityMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseAgilityCompound::IncreaseAgilityCompound() : HTNCompound("IncreaseAgilityCompound")
{
    m_methods.push_back(HTNMethodPtr(new IncreaseAgilityMethod1()));
    m_methods.push_back(HTNMethodPtr(new IncreaseAgilityMethod2()));
}

//***********************************************************
IncreaseIntelligenceMethod1::IncreaseIntelligenceMethod1()
{
    AddTask(HTNPrimitivePtr(new Study()));
}

bool IncreaseIntelligenceMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseIntelligenceMethod2::IncreaseIntelligenceMethod2()
{
    AddTask(HTNCompoundPtr(new GoToLibraryCompound()));
    AddTask(HTNPrimitivePtr(new Study()));
}

bool IncreaseIntelligenceMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

IncreaseIntelligenceCompound::IncreaseIntelligenceCompound() : HTNCompound("IncreaseIntelligenceCompound")
{
    m_methods.push_back(HTNMethodPtr(new IncreaseIntelligenceMethod1()));
    m_methods.push_back(HTNMethodPtr(new IncreaseIntelligenceMethod2()));
}

//***********************************************************
AttackMethod1::AttackMethod1(Item* itemPtr, int opponentIndex)
{
    m_itemPtr = itemPtr;
    AddTask(HTNPrimitivePtr(new PickUpItem(m_itemPtr)));
    AddTask(HTNPrimitivePtr(new Punch(opponentIndex)));
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
    AddTask(HTNPrimitivePtr(new Punch(opponentIndex)));
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
            m_methods.push_back(HTNMethodPtr(new AttackMethod1(item, opponentIndex)));
        }
    }
    m_methods.push_back(HTNMethodPtr(new AttackMethod2(opponentIndex)));
}

AttackCompoundMethod::AttackCompoundMethod(HTNWorldState &htnWorldState, int opponentIndex)
{
    AddTask(HTNCompoundPtr(new AttackCompound(htnWorldState, opponentIndex)));
}

bool AttackCompoundMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
EvadeMethod::EvadeMethod()
{
    AddTask(HTNPrimitivePtr(new Evade()));
}

bool EvadeMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return (htnWorldState.m_v.at(WorldE::health) < 67) && htnWorldState.m_v.at(WorldE::inSameRoom);
}

CombatCompound::CombatCompound(HTNWorldState &htnWorldState, int opponentIndex) : HTNCompound("CombatCompound")
{
    m_methods.push_back(HTNMethodPtr(new EvadeMethod()));
    m_methods.push_back(HTNMethodPtr(new AttackCompoundMethod(htnWorldState, opponentIndex)));
}

//***********************************************************
DoMissionMethod1::DoMissionMethod1()
{
    AddTask(HTNCompoundPtr(new IncreaseStrengthCompound()));
}

bool DoMissionMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_v.at(WorldE::mission) == static_cast<int>(Missions::increaseStrength);
}

DoMissionMethod2::DoMissionMethod2()
{
    AddTask(HTNCompoundPtr(new IncreaseAgilityCompound()));
}

bool DoMissionMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_v.at(WorldE::mission) == static_cast<int>(Missions::increaseAgility);
}

DoMissionMethod3::DoMissionMethod3()
{
    AddTask(HTNCompoundPtr(new IncreaseIntelligenceCompound()));
}

bool DoMissionMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_v.at(WorldE::mission) == static_cast<int>(Missions::increaseIntelligence);
}

DoMissionCompound::DoMissionCompound() : HTNCompound("DoMissionCompound")
{
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod1()));
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod2()));
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod3()));
}

//***********************************************************
CombatMethod::CombatMethod(HTNWorldState &htnWorldState, int opponentIndex)
{
    AddTask(HTNCompoundPtr(new CombatCompound(htnWorldState, opponentIndex)));
}

bool CombatMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

DoMissionMethod::DoMissionMethod()
{
    AddTask(HTNCompoundPtr(new DoMissionCompound()));
}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_v.at(WorldE::mission) != static_cast<int>(Missions::noMission);
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod()
{
    AddTask(HTNCompoundPtr(new IncreaseIntelligenceCompound()));
}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

PrisonerBehaviourCompound::PrisonerBehaviourCompound(HTNWorldState &htnWorldState) : HTNCompound("PrisonerBehaviourCompound")
{
    for (int i = 0; i < c_playerCount; i++)
    {
        if (htnWorldState.m_attackers[i])
        {
            m_methods.push_back(HTNMethodPtr(new CombatMethod(htnWorldState, i)));
        }
    }
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod()));
    m_methods.push_back(HTNMethodPtr(new IncreaseIntelligenceMethod()));
}

//***********************************************************
PickUpItemMethod1::PickUpItemMethod1(Item* itemFocusPtr)
{
    AddTask(HTNPrimitivePtr(new PickUpItem(itemFocusPtr)));
}

bool PickUpItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
DropItemMethod1::DropItemMethod1(Item* itemFocusPtr)
{
    AddTask(HTNPrimitivePtr(new DropItem(itemFocusPtr)));
}

bool DropItemMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}