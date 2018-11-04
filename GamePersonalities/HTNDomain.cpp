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

//Start HTNPrimitives****************************************
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
    return htnWorldState.m_inTheRoom[m_targetPlayerIndex];
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
    htnWorldState.m_itemCarriedPtr = m_itemFocusPtr;
}

Actions PickUpItem::Operator(int playerIndex, Player player[], World &world)
{
    player[playerIndex].itemFocusPtr = m_itemFocusPtr;
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

void PickUpItem::PointToRealItems(HTNWorldState &htnWorldState)
{
    m_itemFocusPtr = &(dynamic_cast<SimItem*>(m_itemFocusPtr))->m_realItem;
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
            item->m_carryingPlayer = htnWorldState.m_ptrToSelf;
            htnWorldState.m_itemCarriedPtr = item;
            return;
        }
    }
}

Actions PickUpItem2::Operator(int playerIndex, Player player[], World &world)
{
    for (auto &item : world.items)
    {
        if (item->m_itemType == m_itemType && item->m_locationClass.location == player[playerIndex].locationClass.location)
        {
            player[playerIndex].itemFocusPtr = item;
            return Actions::pickUpItem;
        }
    }
    player[playerIndex].itemFocusPtr = nullptr;
    return Actions::pickUpItem;
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

//***********************************************************
DropItem::DropItem() : HTNPrimitive("DropItem") {}

void DropItem::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_itemCarriedPtr->m_locationClass.location = static_cast<Locations>(htnWorldState.m_v.at(WorldE::location));
    htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
    htnWorldState.m_itemCarriedPtr = nullptr;
}

Actions DropItem::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::dropItem;
}

bool DropItem::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_itemCarriedPtr != nullptr; //TODO hook this into the actions code
}

//***********************************************************
RequestItemPrim::RequestItemPrim(int playerIndex, Player* player, ItemType itemType) : HTNPrimitive("RequestItem"), m_playerIndex(playerIndex), m_player(player), m_itemType(itemType) {}

void RequestItemPrim::Effect(HTNWorldState &htnWorldState)
{
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == &(m_player[m_playerIndex]))
        {
            htnWorldState.m_itemCarriedPtr = item;
            break;
        }
    }
    htnWorldState.m_itemCarriedPtr->m_carryingPlayer = &(m_player[m_playerIndex]);
}

Actions RequestItemPrim::Operator(int playerIndex, Player player[], World &world)
{
    player[playerIndex].playerTarget = m_playerIndex;
    return Actions::requestItem;
}

bool RequestItemPrim::Preconditions(HTNWorldState &htnWorldState)
{
    if (htnWorldState.m_itemCarriedPtr != nullptr)
    {
        return false;
    }
    for (auto &item : htnWorldState.m_items)
    {
        if (item->m_carryingPlayer == &(m_player[m_playerIndex]) && item->m_itemType == m_itemType && htnWorldState.m_inTheRoom[m_playerIndex])
        {
            return true;
        }
    }
    return false; //TODO hook this into the actions code
}

//Start HTNCompounds*****************************************
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
GetItemMethod1::GetItemMethod1(ItemType itemType) : m_itemType(itemType)
{
    AddTask(HTNPrimitivePtr(new PickUpItem2(itemType)));
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
    AddTask(HTNPrimitivePtr(new RequestItemPrim(playerIndex, player, itemType)));
}

bool GetItemMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

GetItemCompound::GetItemCompound(ItemType itemType, Player player[]) : HTNCompound("GetItemCompound("+ItemTypeToString(itemType)+")")
{
    m_methods.push_back(HTNMethodPtr(new GetItemMethod1(itemType)));
    for (int i=0; i<c_playerCount; i++)
    {
        m_methods.push_back(HTNMethodPtr(new GetItemMethod2(i, player, itemType)));
    }
}

//***********************************************************
BringItemToLocationMethod1::BringItemToLocationMethod1(ItemType itemType, LocationClass &locationClass) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(HTNPrimitivePtr(new DropItem()));
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
            AddTask(HTNCompoundPtr(new GoToBedroomCompound()));
            break;
        case Locations::circuitTrack:
            AddTask(HTNCompoundPtr(new GoToCircuitTrackCompound()));
            break;
        case Locations::gym:
            AddTask(HTNCompoundPtr(new GoToGymCompound()));
            break;
        case Locations::library:
            AddTask(HTNCompoundPtr(new GoToLibraryCompound()));
            break;
        case Locations::mainHall:
            AddTask(HTNPrimitivePtr(new GoToMainHall()));
            break;
    }
    
    AddTask(HTNPrimitivePtr(new DropItem()));
}

bool BringItemToLocationMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return (htnWorldState.m_itemCarriedPtr != nullptr) &&
        (htnWorldState.m_itemCarriedPtr->m_itemType == m_itemType);
}

BringItemToLocationMethod3::BringItemToLocationMethod3(ItemType itemType, LocationClass &locationClass, Player player[]) : m_itemType(itemType), m_locationClass(locationClass)
{
    AddTask(HTNCompoundPtr(new GetItemCompound(itemType, player)));
    
    switch(m_locationClass.location)
    {
        case Locations::bedroom:
            AddTask(HTNCompoundPtr(new GoToBedroomCompound()));
            break;
        case Locations::circuitTrack:
            AddTask(HTNCompoundPtr(new GoToCircuitTrackCompound()));
            break;
        case Locations::gym:
            AddTask(HTNCompoundPtr(new GoToGymCompound()));
            break;
        case Locations::library:
            AddTask(HTNCompoundPtr(new GoToLibraryCompound()));
            break;
        case Locations::mainHall:
            AddTask(HTNPrimitivePtr(new GoToMainHall()));
            break;
    }
    
    AddTask(HTNPrimitivePtr(new DropItem()));
}

bool BringItemToLocationMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return true; 
}

BringItemToLocationCompound::BringItemToLocationCompound(ItemType itemType, LocationClass &locationClass, Player player[]) : HTNCompound("BringItemToLocationCompound")
{
    m_methods.push_back(HTNMethodPtr(new BringItemToLocationMethod1(itemType, locationClass))); //TODO reuse some of the actions at higher level
    m_methods.push_back(HTNMethodPtr(new BringItemToLocationMethod2(itemType, locationClass)));  // TODO ie, right now, method 1 2 and 3 all overlap.
    m_methods.push_back(HTNMethodPtr(new BringItemToLocationMethod3(itemType, locationClass, player)));
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
    return htnWorldState.m_missionClass.m_mission == Missions::increaseStrength;
}

DoMissionMethod2::DoMissionMethod2()
{
    AddTask(HTNCompoundPtr(new IncreaseAgilityCompound()));
}

bool DoMissionMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission == Missions::increaseAgility;
}

DoMissionMethod3::DoMissionMethod3()
{
    AddTask(HTNCompoundPtr(new IncreaseIntelligenceCompound()));
}

bool DoMissionMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission == Missions::increaseIntelligence;
}

DoMissionMethod4::DoMissionMethod4(HTNWorldState &htnWorldState, Player player[])
{
    AddTask(HTNCompoundPtr(new BringItemToLocationCompound(htnWorldState.m_missionClass.m_itemType, htnWorldState.m_missionClass.m_locationClass, player)));  //TODO make construction conditional on 'Preconditions'? Because right now, tasks are constructed regardless of whether their preconditions apply.
}

bool DoMissionMethod4::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission == Missions::bringItemToRoom;
}

DoMissionCompound::DoMissionCompound(HTNWorldState &htnWorldState, Player player[]) : HTNCompound("DoMissionCompound")
{
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod1()));
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod2()));
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod3()));
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod4(htnWorldState, player)));
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

DoMissionMethod::DoMissionMethod(HTNWorldState &htnWorldState, Player player[])
{
    AddTask(HTNCompoundPtr(new DoMissionCompound(htnWorldState, player)));
}

bool DoMissionMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return htnWorldState.m_missionClass.m_mission != Missions::noMission;
}

IncreaseIntelligenceMethod::IncreaseIntelligenceMethod()
{
    AddTask(HTNCompoundPtr(new IncreaseIntelligenceCompound()));
}

bool IncreaseIntelligenceMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
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
DropItemMethod1::DropItemMethod1()
{
    AddTask(HTNPrimitivePtr(new DropItem()));
}

bool DropItemMethod1::Preconditions(HTNWorldState &htnWorldState)
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
            m_methods.push_back(HTNMethodPtr(new CombatMethod(htnWorldState, i)));
        }
    }
    m_methods.push_back(HTNMethodPtr(new DoMissionMethod(htnWorldState, player)));
    m_methods.push_back(HTNMethodPtr(new IncreaseIntelligenceMethod()));
}