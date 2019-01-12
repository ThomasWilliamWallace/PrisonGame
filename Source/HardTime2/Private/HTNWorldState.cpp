#include "HTNWorldState.hpp"
#include <cmath>
#include "ActorItem.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "pLog.hpp"
#include <sstream>

//***********************************************************
HTNWorldState::HTNWorldState(UPlayerData* playerPtr, USimWorld &world):
	m_v(WorldE::last, 0),
	m_ptrToSelf(playerPtr),
    m_itemCarriedPtr(nullptr),
	m_missionClass(playerPtr->missionClass)
{
	m_v.at(WorldE::health) = round(m_ptrToSelf->pStats.getHealth());
	m_v.at(WorldE::sanity) = round(m_ptrToSelf->pStats.getSanity());
	m_v.at(WorldE::strength) = round(m_ptrToSelf->pStats.getStrength());
	m_v.at(WorldE::agility) = round(m_ptrToSelf->pStats.getAgility());
	m_v.at(WorldE::intelligence) = round(m_ptrToSelf->pStats.getIntelligence());
	m_v.at(WorldE::evading) = m_ptrToSelf->lastAction == Actions::evade;
	m_v.at(WorldE::location) = static_cast<int>(m_ptrToSelf->locationClass.location);

	//TODO reflect players sensors rather than being hardwired to the world
	for (auto &item : world.items)
	{
        m_items.push_back(MakeSharedSimActorItemPtr(*item, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if ((m_items.back()->m_carryingPlayer) == m_ptrToSelf)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}

    for (auto &p : world.m_players)
    {
		if (p->locationClass.location == static_cast<ELocations>(m_v.at(WorldE::location)) &&
			playerPtr != p)
		{
			m_playersInTheRoom.push_back(p);
		}
    }
}

HTNWorldState::HTNWorldState(HTNWorldState &ws2) :
	m_v(ws2.m_v),
	m_ptrToSelf(ws2.m_ptrToSelf),
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
	m_v = ws2.m_v;
	m_ptrToSelf = ws2.m_ptrToSelf;
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
	ss << "m_v.size=" << m_v.size() << "\n";
	for (int i = 0; i < static_cast<int>(m_v.size()); i++)
	{
		ss << WorldEToString(static_cast<WorldE>(i)) << ":" << m_v.at(i) << "\n";
	}
	ss << "m_ptrToSelf:" << m_ptrToSelf << "\n";
	ss << "m_itemCarriedPtr:" << GetRaw(m_itemCarriedPtr) << "\n";
	for (auto &simItem : m_items)
	{
		ss << "SimItem: " << simItem->ToString() << " carried by ";
		if (simItem->m_carryingPlayer != nullptr)
		{
		}
		else
		{
			ss << "NULLPTR";
		}
		ss << " in the " << simItem->m_locationClass.ToString() << " with a link to real item " << &(simItem->m_realItem) << "\n";
	}
	ss << "m_v.size=" << m_v.size() << "\n";

    for (auto &p : m_playersInTheRoom)
    {
		if (p != nullptr)
			ss << "PlayerData " << " is also in the " << LocationToString(static_cast<ELocations>(m_v.at(WorldE::location))) << ".\n";
		else
			ss << "ERROR NULL PLAYERDATA VALUE\n";
    }
	ss << "m_missionClass:" << m_missionClass.MissionName() << "\n";
	pLog(ss);
}

std::string WorldEToString(WorldE worldE)
{
	switch (worldE)
	{
	case WorldE::health: return "health";
	case WorldE::sanity: return "sanity";
	case WorldE::strength: return "strength";
	case WorldE::agility: return "agility";
	case WorldE::intelligence: return "intelligence";
	case WorldE::evading: return "evading";
	case WorldE::location: return "location";
	case WorldE::last: return "LAST";
	default: return "ERROR_NO_WORLDE_STRING_FOUND";
	}
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
