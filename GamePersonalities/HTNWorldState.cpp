//
//  HTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNWorldState.hpp"
#include "Player.hpp"
#include <cmath>
#include "World.hpp"

//***********************************************************
HTNWorldState::HTNWorldState(int playerIndex, Player player[], World &world, int requesterIndex):
    m_v(WorldE::last, 0),
    m_ptrToSelf(&(player[playerIndex])),
    m_itemCarriedPtr(nullptr),
    m_requesterIndex(requesterIndex),
    m_missionClass(player[playerIndex].missionClass)
{
    m_v.at(WorldE::health) = round(player[playerIndex].stats.getHealth());
    m_v.at(WorldE::sanity) = round(player[playerIndex].stats.getSanity());
    m_v.at(WorldE::strength) = round(player[playerIndex].stats.getStrength());
    m_v.at(WorldE::agility) = round(player[playerIndex].stats.getAgility());
    m_v.at(WorldE::intelligence) = round(player[playerIndex].stats.getIntelligence());
    m_v.at(WorldE::punches) = 0;
    m_v.at(WorldE::evading) = player[playerIndex].lastAction == Actions::evade;
    m_v.at(WorldE::location) = static_cast<int>(player[playerIndex].locationClass.location);
    m_v.at(WorldE::inSameRoom) = player[playerIndex].locationClass.location == player[0].locationClass.location;
    
    //TODO reflect players sensors rather than being hardwired to the world
    for (auto &item : world.items)
    {
        m_items.push_back(new SimItem(*item, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
        if (&*(m_items.back()->m_carryingPlayer) == &player[playerIndex])
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
    
    for (int i = 0; i < c_playerCount; i++)
    {
        m_attackers.push_back(player[playerIndex].rel[i].getAggro()>29 ? true : false);
        m_inTheRoom[i] = player[i].locationClass.location == player[playerIndex].locationClass.location && i != playerIndex;
    }
}

HTNWorldState::HTNWorldState(HTNWorldState &ws2):
    m_v(ws2.m_v),
    m_ptrToSelf(ws2.m_ptrToSelf),
    m_itemCarriedPtr(nullptr),
    m_requesterIndex(ws2.m_requesterIndex),
    m_attackers(ws2.m_attackers),
    m_missionClass(ws2.m_missionClass)
{
    std::copy(std::begin(ws2.m_inTheRoom), std::end(ws2.m_inTheRoom), std::begin(m_inTheRoom));
    for (auto &item : ws2.m_items)
    {
        m_items.push_back(new SimItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
        if (ws2.m_itemCarriedPtr == item)
            
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
}

HTNWorldState::~HTNWorldState()
{
    for (SimItem* itemPtr : m_items)
    {
        delete itemPtr;
    }
}

void HTNWorldState::CopyFrom(HTNWorldState &ws2)
{
    m_v = ws2.m_v;
    m_ptrToSelf = ws2.m_ptrToSelf;
    m_itemCarriedPtr = nullptr;
    m_requesterIndex = ws2.m_requesterIndex;
    m_attackers = ws2.m_attackers;
    std::copy(std::begin(ws2.m_inTheRoom), std::end(ws2.m_inTheRoom), std::begin(m_inTheRoom));
    
    m_items.clear();
    for (auto &item : ws2.m_items)
    {
        m_items.push_back(new SimItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
        if (ws2.m_itemCarriedPtr == item)
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
    m_missionClass = ws2.m_missionClass;
}

void HTNWorldState::Print()
{
    for (int i = 0; i < static_cast<int>(m_v.size()); i++)
    {
        std::cout << WorldEToString(static_cast<WorldE>(i)) << ":" << m_v.at(i) << "\n";
    }
    std::cout << "m_ptrToSelf:" << m_ptrToSelf << "\n";
    std::cout << "m_itemCarriedPtr:" << m_itemCarriedPtr << "\n";
    std::cout << "m_requesterIndex:" << m_requesterIndex << "\n";
    for (auto &simItem : m_items)
    {
        std::cout << "SimItem: " << simItem->ToString() << " carried by " << simItem->m_carryingPlayer->name << " in the " << simItem->m_locationClass.ToString() << " with a link to real item " << &(simItem->m_realItem) << "\n";
    }
    for (int i = 0; i < c_playerCount; i++)
    {
        std::cout << "Status of player " << i << " = " << (m_attackers.at(i) ? "fighting" : "peaceful") << " in the " << LocationToString(static_cast<Locations>(m_v.at(WorldE::location))) << ".\n";
    }
}

std::string WorldEToString(WorldE worldE)
{
    switch(worldE)
    {
        case WorldE::health: return "health";
        case WorldE::sanity: return "sanity";
        case WorldE::strength: return "strength";
        case WorldE::agility: return "agility";
        case WorldE::intelligence: return "intelligence";
        case WorldE::punches: return "punches";
        case WorldE::evading: return "evading";
        case WorldE::location: return "location";
        case WorldE::inSameRoom: return "inSameRoom";
        case WorldE::last: return "LAST";
        default: return "ERROR_NO_WORLDE_STRING_FOUND";
    }
}