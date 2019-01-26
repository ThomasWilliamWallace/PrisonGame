#include "SimWorld.h"
#include "ActorItem.h"
#include "HardTime2Character.h"
#include <sstream>
#include "pLog.hpp"

USimWorld::USimWorld()
{
    weightsOccupied  = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    bedOccupied      = nullptr;
}

void USimWorld::Clean()
{
    bedOccupied      = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    weightsOccupied  = nullptr;
}

void USimWorld::UpdateItemLocation(AActorItem* item, ELocations location)
{
	pLog("USimWorld::UpdateItemLocation");
	if (!IsValid(item))
	{
		pLog("ERROR: item IS NOT VALID DURING USimWorld::UpdateItemLocation", true);
		return;
	}
	item->m_locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss);
}

void USimWorld::AddItem(AActorItem* item)
{
	pLog("USimWorld::AddItem");
	if (!IsValid(item))
	{
		pLog("ERROR: item IS NOT VALID DURING USimWorld::AddItem", true);
		//return;
	}
	items.push_back(item);
	std::stringstream ss;
	ss << "item=" << item;
	pLog(ss);
}

void USimWorld::AddPlayer(UPlayerData* playerData)
{
	pLog("USimWorld::AddPlayer");
	if (!IsValid(playerData))
	{
		pLog("ERROR: playerData IS NOT VALID DURING USimWorld::AddPlayer", true);
		return;
	}
	m_playerRegistry.RegisterPlayer(playerData);
	std::stringstream ss;
	ss << "player=" << playerData;
	pLog(ss);
}

void USimWorld::RemoveItem(AActorItem* item)
{
	pLog("USimWorld::RemoveItem");
	if (!IsValid(item))
	{
		pLog("ERROR: item IS NOT VALID DURING USimWorld::RemoveItem", true);
		//return;
	}
	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		if (items.at(i) == item)
		{
			items.erase(items.begin() + i);
			return;
		}
	}
	pLog("ERROR: item was not found when trying to remove from world.items");
}

void USimWorld::RemovePlayer(UPlayerData* playerData)
{
	pLog("USimWorld::RemovePlayer");
	if (!IsValid(playerData))
	{
		pLog("ERROR: playerData IS NOT VALID DURING USimWorld::RemovePlayer", true);
		//return;
	}
	m_playerRegistry.DeregisterPlayer(playerData->m_key);
}

void USimWorld::UpdateCarriedItem(AActorItem* item, ACharacter* character)
{
	pLog("USimWorld::UpdateCarriedItemC");
	if (item != nullptr && !IsValid(item))
	{
		pLog("ERROR: item IS NOT VALID DURING USimWorld::UpdateCarriedItemC", true);
		return;
	}
	if (!IsValid(character))
	{
		pLog("ERROR: character IS NOT VALID DURING USimWorld::UpdateCarriedItemC", true);
		return;
	}
	std::stringstream ss;
	ss << "item=" << item << ", character=" << character;
	pLog(ss);

	if (character == nullptr)
	{
		if (item != nullptr)
		{
			item->m_carryingPlayer = nullptr;
		}
		return;
	}

	UPlayerData* playerData;
	AHardTime2Character* hardTime2Character = Cast<AHardTime2Character>(character);
	if (hardTime2Character == nullptr)
	{
		return;
	} else {
		playerData = hardTime2Character->m_player;
	}

	for (auto &p : m_playerRegistry.m_playerMap)
	{
		if (playerData == p.Value)
		{
			playerData->itemPtr = item;
		}
	}

	if (item == nullptr)
	{
		for (auto &m_item : items)
		{
			if (m_item->m_carryingPlayer == playerData)
			{
				m_item->m_carryingPlayer = nullptr;
				break;
			}
		}
	}
	else
	{
		item->m_carryingPlayer = playerData;
	}
}