#include "HTNWorldState.hpp"
#include <cmath>
#include "ActorItem.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.hpp"
#include "pLog.hpp"
#include <sstream>

//***********************************************************
HTNWorldState::HTNWorldState(UPlayerData* playerPtr, USimWorld &world):
	m_v(WorldE::last, 0),
	m_ptrToSelf(playerPtr),
    m_itemCarriedPtr(nullptr),
	m_missionClass(playerPtr->missionClass)
{
	{std::stringstream ss;
	ss << "PART 1 OF HTNWORLDSTATE CONSTRUCTOR, m_v.size=" << m_v.size() << "\n";
	for (int i = 0; i < static_cast<int>(m_v.size()); i++)
	{
		ss << WorldEToString(static_cast<WorldE>(i)) << ":" << m_v.at(i) << "\n";
	}
	ss << "playerPtr=" << playerPtr << ", world=" << &world << "\n";
	pLog(ss); }
	//m_v.at(WorldE::health) = round(m_ptrToSelf->pStats.getHealth());
	//m_v.at(WorldE::sanity) = round(m_ptrToSelf->pStats.getSanity());
	//m_v.at(WorldE::strength) = round(m_ptrToSelf->pStats.getStrength());
	//m_v.at(WorldE::agility) = round(m_ptrToSelf->pStats.getAgility());
	//m_v.at(WorldE::intelligence) = round(m_ptrToSelf->pStats.getIntelligence());
	//m_v.at(WorldE::evading) = m_ptrToSelf->lastAction == Actions::evade;
	m_v.at(WorldE::location) = static_cast<int>(m_ptrToSelf->locationClass.location);

	{std::stringstream ss;
	ss << "PART 2 OF HTNWORLDSTATE CONSTRUCTOR, m_v.size=" << m_v.size() << "\n";
	for (int i = 0; i < static_cast<int>(m_v.size()); i++)
	{
		ss << WorldEToString(static_cast<WorldE>(i)) << ":" << m_v.at(i) << "\n";
	}
	pLog(ss); }

	//TODO reflect players sensors rather than being hardwired to the world
	for (auto &item : world.items)
	{
		m_items.push_back(new SimActorItem(*item, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));

		if ((m_items.back()->m_carryingPlayer) == m_ptrToSelf)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}
    
	int i = 0;
    for (auto &p : world.m_players)
    {
		ELocations el = static_cast<ELocations>(m_v.at(WorldE::location));
		ELocations el2 = p->locationClass.location;
		{std::stringstream ss;
		ss << "e1=" << static_cast<int>(el) << "\n";
		ss << "el2=" << static_cast<int>(el2) << "\n";
		ss << "playerPtr=" << playerPtr << "\n";
		ss << "p=" << p << "\n";
		pLog(ss); }
        m_inTheRoom[i] = p->locationClass.location == static_cast<ELocations>(m_v.at(WorldE::location)) &&
							playerPtr != p;
		if (m_inTheRoom[i])
		{
			m_playersInTheRoom.push_back(p);
		}
		i++;
    }

	{std::stringstream ss;
	ss << "m_v.size=" << m_v.size() << "\n";
	pLog(ss); }
	pLog("HTNWorldState::default constructor:");
	Print();
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
    std::copy(std::begin(ws2.m_inTheRoom), std::end(ws2.m_inTheRoom), std::begin(m_inTheRoom));
	for (auto &item : ws2.m_items)
	{
		m_items.push_back(new SimActorItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}
	pLog("HTNWorldState::Copy constructor:");
	Print();
}

HTNWorldState::~HTNWorldState()
{
	for (SimActorItem* itemPtr : m_items)
	{
		delete itemPtr;
	}
}

void HTNWorldState::CopyFrom(HTNWorldState &ws2)
{
	m_v = ws2.m_v;
	m_ptrToSelf = ws2.m_ptrToSelf;
	m_itemCarriedPtr = nullptr;
	m_attackers = ws2.m_attackers;
	m_playerLocations = ws2.m_playerLocations;
	std::copy(std::begin(ws2.m_inTheRoom), std::end(ws2.m_inTheRoom), std::begin(m_inTheRoom));    
    m_playersInTheRoom = ws2.m_playersInTheRoom;

    m_items.clear();
	for (auto &item : ws2.m_items)
	{
		m_items.push_back(new SimActorItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
		}
	}
	m_missionClass = ws2.m_missionClass;
	pLog("HTNWorldState::CopyFrom:");
	Print();
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
	ss << "m_itemCarriedPtr:" << m_itemCarriedPtr << "\n";
	for (auto &simItem : m_items)
	{
		ss << "SimItem: " << simItem->ToString() << " carried by ";
		if (simItem->m_carryingPlayer != nullptr)
		{
			ss << simItem->m_carryingPlayer->m_playerName;
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
			ss << "PlayerData " << p->m_playerName << " is also the " << LocationToString(static_cast<ELocations>(m_v.at(WorldE::location))) << ".\n";
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
    return m_inTheRoom[playerPtr->m_playerIndex];
}
