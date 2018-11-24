#include "SimWorld.h"
#include "ActorItem.h"
#include "AICharacterC.h"
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
	pLog("USimWorld::UpdateItemLocation", true);
	item->m_locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss, true);
}

void USimWorld::AddItem(AActorItem* item)
{
	pLog("USimWorld::AddItem", true);
	items.push_back(item);
	std::stringstream ss;
	ss << "item=" << item;
	pLog(ss, true);
}

void USimWorld::AddPlayer(AAICharacterC* aiCharacterC)
{
	pLog("USimWorld::AddPlayer", true);
	m_players.push_back(aiCharacterC->m_player);
	std::stringstream ss;
	ss << "player=" << &(aiCharacterC->m_player);
	pLog(ss, true);
}

void USimWorld::UpdateCarriedItemC(AActorItem* item, ACharacter* character)
{
	pLog("USimWorld::UpdateCarriedItemC", true);
	std::stringstream ss;
	ss << "item=" << item << ", character=" << character;
	pLog(ss, true);

	if (character == nullptr)
	{
		if (item != nullptr)
		{
			item->m_carryingPlayer = nullptr;
		}
		return;
	}

	AAICharacterC* aiCharacterC = Cast<AAICharacterC>(character);
	if (aiCharacterC == nullptr)
	{
		return;
	}

	for (auto &p : m_players)
	{
		if (aiCharacterC->m_player == p)
		{
			aiCharacterC->m_player->itemPtr = item;
		}
	}

	if (item == nullptr)
	{
		for (auto &m_item : items)
		{
			if (m_item->m_carryingPlayer == aiCharacterC->m_player)
			{
				m_item->m_carryingPlayer = nullptr;
				break;
			}
		}
	}
	else
	{
		item->m_carryingPlayer = aiCharacterC->m_player;
	}
}