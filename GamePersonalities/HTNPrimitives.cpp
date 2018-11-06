//
//  HTNPrimitives.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNPrimitives.hpp"
#include "Locations.hpp"
#include "Player.hpp"
#include "World.hpp"

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
    if (htnWorldState.m_itemCarriedPtr != nullptr)
    {
        htnWorldState.m_itemsToKeep.push_back(htnWorldState.m_itemCarriedPtr);
    }
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
    SimItem* itemFocusSimItem = dynamic_cast<SimItem*>(m_itemFocusPtr);
    for (auto &item : htnWorldState.m_items)
    {
        SimItem* simItem = dynamic_cast<SimItem*>(item);
        if (&(simItem->m_realItem) == &(itemFocusSimItem->m_realItem))
        {
            m_itemFocusPtr->m_carryingPlayer = htnWorldState.m_ptrToSelf;
        }
    }
    htnWorldState.m_itemCarriedPtr = &(itemFocusSimItem->m_realItem);
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

//void PickUpItem::PointToRealItems(HTNWorldState &htnWorldState)
//{
//    m_itemFocusPtr = &(dynamic_cast<SimItem*>(m_itemFocusPtr))->m_realItem;
//}

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
DropItem::DropItem(bool keepItem) : HTNPrimitive("DropItem"), m_keepItem(keepItem) {}

void DropItem::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_itemCarriedPtr->m_locationClass.location = static_cast<Locations>(htnWorldState.m_v.at(WorldE::location));
    htnWorldState.m_itemCarriedPtr->m_carryingPlayer = nullptr;
    if (m_keepItem)
    {
        SimItem* simItem = dynamic_cast<SimItem*>(htnWorldState.m_itemCarriedPtr);
//        if (simItem == nullptr)
//        {
//            std::cout << "ERROR cast to SimItem failed.\n";
//            exit(0);
//        }
//        std::cout << "saving from dropItem=" << &(simItem->m_realItem) << "\n"; //TODO this is probably a simItem, and we are treating it as an Item.
        htnWorldState.m_itemsToKeep.push_back(&(simItem->m_realItem));
    }
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