#include "HTNWorldState.hpp"
#include <cmath>
#include "ActorItem.h"
#include "Player.hpp"
#include "World.hpp"
#include "HTNDomain.hpp"
#include "Engine/GameEngine.h"

//***********************************************************
HTNWorldState::HTNWorldState(Player* playerPtr, World &world):
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
	m_v.at(WorldE::punches) = 0;
	m_v.at(WorldE::evading) = m_ptrToSelf->lastAction == Actions::evade;
	m_v.at(WorldE::location) = static_cast<int>(m_ptrToSelf->locationClass.location);

	//TODO reflect players sensors rather than being hardwired to the world
	for (auto &item : world.items)
	{
		m_items.push_back(new SimActorItem(item, item->m_itemType, Locations::mainHall, item->m_carryingPlayer));

		if (GEngine) {
			UE_LOG(LogTemp, Warning, TEXT("item->m_carryingPlayer = %p"), item->m_carryingPlayer);
			UE_LOG(LogTemp, Warning, TEXT("m_items.back()->m_carryingPlayer = %p"), m_items.back()->m_carryingPlayer);
			UE_LOG(LogTemp, Warning, TEXT("m_ptrToSelf = %p"), m_ptrToSelf);
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("constructor #1a m_itemCarriedPtr = %p"), m_itemCarriedPtr));
		if ((m_items.back()->m_carryingPlayer) == m_ptrToSelf)
		{
			m_itemCarriedPtr = m_items.back();
			UE_LOG(LogTemp, Warning, TEXT("constructor #1b m_itemCarriedPtr = %p"), m_itemCarriedPtr);
		}
	}

	//for (int i = 0; i < c_playerCount; i++)
	//{
	//	m_attackers.push_back(aiCharacterC->rel[i].getAggro() > 29 ? true : false);
	//	m_playerLocations.push_back(player[i].locationClass.location);
	//}
}

HTNWorldState::HTNWorldState(HTNWorldState &ws2) :
	m_v(ws2.m_v),
	m_ptrToSelf(ws2.m_ptrToSelf),
    	m_itemCarriedPtr(nullptr),
	m_attackers(ws2.m_attackers),
	m_playerLocations(ws2.m_playerLocations),
	m_missionClass(ws2.m_missionClass)
{
		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Entering constructor #2")));
	m_itemCarriedPtr = nullptr;
	for (auto &item : ws2.m_items)
	{
		m_items.push_back(new SimActorItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("constructor #2a m_itemCarriedPtr = %p"), m_itemCarriedPtr));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("constructor #2b m_itemCarriedPtr = %p"), m_itemCarriedPtr));
		}
	}
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

    	m_items.clear();
	for (auto &item : ws2.m_items)
	{
		m_items.push_back(new SimActorItem(item->m_realItem, item->m_itemType, item->m_locationClass.location, item->m_carryingPlayer));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("copyfrom a m_itemCarriedPtr = %p"), m_itemCarriedPtr));
		if (ws2.m_itemCarriedPtr == item)
		{
			m_itemCarriedPtr = m_items.back();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("copyfrom b m_itemCarriedPtr = %p"), m_itemCarriedPtr));
		}
	}
	m_missionClass = ws2.m_missionClass;
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
	case WorldE::punches: return "punches";
	case WorldE::evading: return "evading";
	case WorldE::location: return "location";
	case WorldE::last: return "LAST";
	default: return "ERROR_NO_WORLDE_STRING_FOUND";
	}
}
