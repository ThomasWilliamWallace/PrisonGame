#include "SimWorld.h"
#include "ActorItem.h"
#include "AICharacterC.h"
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

void USimWorld::WorldEffects(UPlayerData player[], int frame)
{
    if (bedOccupied != nullptr)
    {
        bedOccupied->pStats.deltaHealth(1);
    }
    if (circuitsOccupied != nullptr)
    {
        circuitsOccupied->pStats.deltaAgility(1);
    }
    if (studyOccupied != nullptr)
    {
        studyOccupied->pStats.deltaIntelligence(1);
    }
    if (weightsOccupied != nullptr)
    {
        weightsOccupied->pStats.deltaStrength(1);
        weightsOccupied->narrative = "weightlift; strength = " + FormatDouble(weightsOccupied->pStats.getStrength());
    }
}

void USimWorld::PrintWorld(UPlayerData player[])
{
	/*
	std::sstringstream ss;
    ss << "*** WORLD DATA ***\n";
    ss << "weightsOccupied=" << CharacterName(weightsOccupied) << "\n";
    ss << "circuitsOccupied=" << CharacterName(circuitsOccupied) << "\n";
    ss << "studyOccupied=" << CharacterName(studyOccupied) << "\n";
    ss << "bedOccupied=" << CharacterName(bedOccupied) << "\n";
    ss << "\n";
    for (auto &item : items)
    {
        ss << item->ToString() << " is in the " << item->m_locationClass.ToString() << ".\n";
    }
    ss << "\n";
	pLog(ss);
	*/
}

void USimWorld::FullDisplay(UPlayerData player[])
{
	/*
    PrintWorld(player);
    
    for (int playerIndex = 0; playerIndex < c_playerCount; playerIndex++)
    {
        player[playerIndex].PrintPlayer(player);
    }
	*/
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

int USimWorld::AddPlayer(UPlayerData* playerData)
{
	pLog("USimWorld::AddPlayer");
	if (!IsValid(playerData))
	{
		pLog("ERROR: playerData IS NOT VALID DURING USimWorld::AddPlayer", true);
		return -1;
	}
	m_players.push_back(playerData);
	std::stringstream ss;
	ss << "player=" << playerData;
	pLog(ss);
	return static_cast<int>(m_players.size());
}

void USimWorld::UpdateCarriedItemC(AActorItem* item, ACharacter* character)
{
	pLog("USimWorld::UpdateCarriedItemC");
	if (!IsValid(item))
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

	AAICharacterC* aiCharacterC = Cast<AAICharacterC>(character);
	UPlayerData* playerData;
	
	if (aiCharacterC == nullptr)
	{
		AHardTime2Character* hardTime2Character = Cast<AHardTime2Character>(character);
		if (hardTime2Character == nullptr)
		{
			return;
		} else {
			playerData = hardTime2Character->m_player;
		}
	} else {
		playerData = aiCharacterC->m_player;
	}

	for (auto &p : m_players)
	{
		if (playerData == p)
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