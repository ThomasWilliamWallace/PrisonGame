#include "HTNWorldState.h"
#include <cmath>
#include "PlayerData.h"
#include "AbstractItem.h"
#include "pLog.h"
#include <sstream>
#include "Missions.h"

//***********************************************************
HTNWorldState::HTNWorldState(UPlayerData* playerPtr, PlayerMap& playerMap, std::vector<RealItemType*>& realItems,
              UPlayerData* requester, std::vector<UPlayerData*> attackers, std::vector<UPlayerData*> playersInTheRoom,
              float health, float sanity, float strength, float agility, float intelligence):
    m_ptrToSelf(playerPtr),
    m_health(health),
    m_sanity(sanity),
    m_strength(strength),
    m_agility(agility),
    m_intelligence(intelligence),
    m_evading(m_ptrToSelf->lastAction->m_action == EActions::evade),
    m_location(m_ptrToSelf->locationClass.location),
    m_missionClass(playerPtr->missionClass),
    m_requester(requester),
    m_attackers(attackers),
    m_playersInTheRoom(playersInTheRoom)
{
    for (auto &item : realItems)
    {
        m_items.push_back(std::make_shared<SimItem>(CreateSimFromRealItem::CreateSimFromRealItem, item));
        if ((m_items.back()->m_carryingPlayer) == m_ptrToSelf)
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
//    std::cout << "constructed HTNWorldState.m_items:\n";
//    for (auto& itemPtr : m_items)
//    {
//        std::cout << itemPtr << "; realItem=" << itemPtr->m_realItem << "\n";
//    }
//    std::cout << "\n";
}

HTNWorldState::HTNWorldState(HTNWorldState const& ws2):
    m_ptrToSelf(ws2.m_ptrToSelf),
    m_health(ws2.m_health),
    m_sanity(ws2.m_sanity),
    m_strength(ws2.m_strength),
    m_agility(ws2.m_agility),
    m_intelligence(ws2.m_intelligence),
    m_evading(ws2.m_evading),
    m_location(ws2.m_location),
    m_missionClass(ws2.m_missionClass),
    m_itemCarriedPtr(nullptr),
    m_requester(ws2.m_requester),
    m_attackers(ws2.m_attackers),
    m_playersInTheRoom(ws2.m_playersInTheRoom)
{
    for (auto &item : ws2.m_items)
    {
        m_items.emplace_back(std::make_shared<SimItem>(*(item.get())));
        m_items.back()->m_realItem = item->m_realItem;
        if (ws2.m_itemCarriedPtr != nullptr && ws2.m_itemCarriedPtr->m_realItem == item->m_realItem)
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
//    std::cout << "COPY constructed HTNWorldState.m_items:\n";
//    for (auto& itemPtr : m_items)
//    {
//        std::cout << itemPtr << "; realItem=" << itemPtr->m_realItem << "\n";
//    }
//    std::cout << "\n";
}

HTNWorldState& HTNWorldState::operator=(HTNWorldState const& ws2)
{
    m_ptrToSelf = ws2.m_ptrToSelf;
    m_health = ws2.m_health;
    m_sanity = ws2.m_sanity;
    m_strength = ws2.m_strength;
    m_agility = ws2.m_agility;
    m_intelligence = ws2.m_intelligence;
    m_evading = ws2.m_evading;
    m_location = ws2.m_location;
    m_itemCarriedPtr = nullptr;
    m_requester = ws2.m_requester;
    m_attackers = ws2.m_attackers;
    m_playersInTheRoom = ws2.m_playersInTheRoom;
    
    m_items.clear();
    for (auto &item : ws2.m_items)
    {
        m_items.emplace_back(std::make_shared<SimItem>(*(item.get())));
        m_items.back()->m_realItem = item->m_realItem;
        if (ws2.m_itemCarriedPtr == item)
        {
            m_itemCarriedPtr = m_items.back();
        }
    }
//    std::cout << "ASSIGNMENT constructed HTNWorldState.m_items:\n";
//    for (auto& itemPtr : m_items)
//    {
//        std::cout << itemPtr << "; realItem=" << itemPtr->m_realItem << "\n";
//    }
//    std::cout << "\n";
    m_missionClass = ws2.m_missionClass;
    return *this;
}

void HTNWorldState::Print()
{
	std::stringstream ss;
	ss << "HTNWorldState::Print\n";
    ss << "m_health:" << m_health << "\n";
    ss << "m_sanity:" << m_sanity << "\n";
    ss << "m_strength:" << m_strength << "\n";
    ss << "m_agility:" << m_agility << "\n";
    ss << "m_intelligence:" << m_intelligence << "\n";
    ss << "m_evading:" << m_evading << "\n";
    ss << "m_location:" << static_cast<int>(m_location) << "\n";
    ss << "m_ptrToSelf:" << m_ptrToSelf << "\n";
    ss << "m_itemCarriedPtr:" << GetRaw(m_itemCarriedPtr) << "\n";
    ss << "m_requester:" << m_requester << "\n";
    for (auto &simItem : m_items)
    {
		ss << "SimItem: " << simItem->ToString() << " carried by ";
		if (simItem->m_carryingPlayer != nullptr)
		{
			ss << simItem->m_carryingPlayer->CharacterName();
		}
		else
		{
			ss << "NULLPTR";
		}
		ss << " in the " << simItem->m_locationClass.ToString() << " with a link to real item " << simItem << "\n";
    }

    for (auto &p : m_attackers)
    {
        ss << "Being attacked by player " << p->CharacterName() << " in the " << LocationToString(m_location) << ".\n";
    }
    for (auto &p : m_playersInTheRoom)
    {
		if (p != nullptr)
			ss << "PlayerData " << p->CharacterName() << " is also in the " << LocationToString(m_location) << ".\n";
		else
            ThrowException("ERROR NULL PLAYERDATA VALUE");
    }
    ss << "]\n";
//    ss << "m_missionClass:" << m_missionClass->MissionName() << "\n";
    pLog(ss);
}

bool HTNWorldState::IsInTheRoom(UPlayerData const& playerPtr) const
{
    for (auto &p : m_playersInTheRoom)
    {
        if (p == &playerPtr)
        {
            return true;
        }
    }
    return false;
}
