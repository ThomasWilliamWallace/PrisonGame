#include "HTNWorldState.h"
#include <cmath>
#include "ActorItem.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "pLog.h"
#include <sstream>

//***********************************************************
HTNWorldState::HTNWorldState(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world):
	m_ptrToSelf(playerPtr),
    m_health(round(m_ptrToSelf->pStats.getHealth())),
    m_sanity(round(m_ptrToSelf->pStats.getSanity())),
    m_strength(round(m_ptrToSelf->pStats.getStrength())),
    m_agility(round(m_ptrToSelf->pStats.getAgility())),
    m_intelligence(round(m_ptrToSelf->pStats.getIntelligence())),
    m_evading(m_ptrToSelf->lastAction == EActions::evade),
    m_location(m_ptrToSelf->locationClass.location),
    m_itemCarriedPtr(nullptr),
	m_missionClass(playerPtr->missionClass)
{
	//std::stringstream ss;
	//ss << "CONSTRUCTING HTNWorldState " << static_cast<int>(m_ptrToSelf->locationClass.location) << "\n";
	//pLog(ss, true);
	//TODO reflect players sensors rather than being hardwired to the world
	for (auto &item : world.items)
	{
        m_items.push_back(MakeSharedSimActorItemPtr(*item, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if ((m_items.back()->m_carryingPlayer) == m_ptrToSelf)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}

    for (auto &p : playerMap)
    {
		if (p.Value->locationClass.location == m_location &&
			playerPtr != p.Value)
		{
			m_playersInTheRoom.push_back(p.Value);
			if (m_health < 65)
			{
				m_attackers.push_back(p.Value);
			}
		}
    }
}

HTNWorldState::HTNWorldState(HTNWorldState &ws2) :
	m_ptrToSelf(ws2.m_ptrToSelf),
    m_health(ws2.m_health),
    m_sanity(ws2.m_sanity),
    m_strength(ws2.m_strength),
    m_agility(ws2.m_agility),
    m_intelligence(ws2.m_intelligence),
    m_evading(ws2.m_evading),
    m_location(ws2.m_location),
    m_itemCarriedPtr(nullptr),
	m_attackers(ws2.m_attackers),
	m_playerLocations(ws2.m_playerLocations),
    m_playersInTheRoom(ws2.m_playersInTheRoom),
	m_missionClass(ws2.m_missionClass)
{
	for (auto &item : ws2.m_items)
	{
        m_items.push_back(MakeSharedSimActorItemPtr(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}
}

HTNWorldState& HTNWorldState::operator=(const HTNWorldState& ws2)
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
	m_attackers = ws2.m_attackers;
	m_playerLocations = ws2.m_playerLocations;
    m_playersInTheRoom = ws2.m_playersInTheRoom;

    m_items.clear();
	for (auto &item : ws2.m_items)
	{
        m_items.push_back(MakeSharedSimActorItemPtr(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}
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
	for (auto &simItem : m_items)
	{
		ss << "SimItem: " << simItem->ToString() << " carried by ";
		if (simItem->m_carryingPlayer != nullptr)
		{
			ss << std::string(TCHAR_TO_UTF8(*(simItem->m_carryingPlayer->m_playerName.ToString())));
		}
		else
		{
			ss << "NULLPTR";
		}
		ss << " in the " << simItem->m_locationClass.ToString() << " with a link to real item " << &(simItem->m_realItem) << "\n";
	}

    for (auto &p : m_playersInTheRoom)
    {
		if (p != nullptr)
		{
			ss << std::string(TCHAR_TO_UTF8(*(p->m_playerName.ToString())));
			ss << " is also in the " << LocationToString(m_location) << ".\n";
		}
		else
			ss << "ERROR NULL PLAYERDATA VALUE\n";
    }

	for (auto &p : m_attackers)
	{
		if (p != nullptr)
		{
			ss << std::string(TCHAR_TO_UTF8(*(p->m_playerName.ToString())));
			ss << " is attacking.\n";
		}
		else
			ss << "ERROR NULL PLAYERDATA VALUE\n";
	}
	ss << "m_missionClass:" << m_missionClass.MissionName() << "\n";
	pLog(ss);
}

bool HTNWorldState::IsInTheRoom(UPlayerData* playerPtr)
{
	for (auto &p : m_playersInTheRoom)
	{
		if (p == playerPtr)
		{
			return true;
		}
	}
	return false;
}
