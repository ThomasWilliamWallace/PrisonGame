#include "SimWorld.h"
#include "Constants.h"
#include <sstream>
#include "pLog.h"

USimWorld::USimWorld()
{
    Clean();
}

void USimWorld::Clean()
{
    bedOccupied      = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    weightsOccupied  = nullptr;
}

void USimWorld::WorldEffects()
{
    if (bedOccupied != nullptr)
    {
        bedOccupied->abstractPlayerData.pStats.deltaHealth(1);
        bedOccupied->abstractPlayerData.narrative = "sleep; health = " + FormatDouble(bedOccupied->abstractPlayerData.pStats.getHealth());
    }
    if (circuitsOccupied != nullptr)
    {
        circuitsOccupied->abstractPlayerData.pStats.deltaAgility(1);
        circuitsOccupied->abstractPlayerData.narrative = "circuits; agility = " + FormatDouble(circuitsOccupied->abstractPlayerData.pStats.getAgility());
    }
    if (studyOccupied != nullptr)
    {
        studyOccupied->abstractPlayerData.pStats.deltaIntelligence(1);
        studyOccupied->abstractPlayerData.narrative = "study; intelligence = " + FormatDouble(studyOccupied->abstractPlayerData.pStats.getIntelligence());
    }
    if (weightsOccupied != nullptr)
    {
        weightsOccupied->abstractPlayerData.pStats.deltaStrength(1);
        weightsOccupied->abstractPlayerData.narrative = "weightlift; strength = " + FormatDouble(weightsOccupied->abstractPlayerData.pStats.getStrength());
    }
}

void USimWorld::PrintWorld()
{
    std::cout << "*** WORLD DATA ***\n";
    std::cout << "weightsOccupied=";
    if (weightsOccupied != nullptr) {
        std::cout << weightsOccupied->abstractPlayerData.m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (circuitsOccupied != nullptr) {
        std::cout << circuitsOccupied->abstractPlayerData.m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (studyOccupied != nullptr) {
        std::cout << studyOccupied->abstractPlayerData.m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (bedOccupied != nullptr) {
        std::cout << bedOccupied->abstractPlayerData.m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    std::cout << "\n";
    for (auto &item : items)
    {
        std::cout << item->ToString() << " is in the " << item->m_locationClass.ToString() << ".\n";
    }
    std::cout << "\n";
}

void USimWorld::FullDisplay()
{
    std::cout << "\n";
    PrintWorld();
    
    int playerCount = playerRegistry.m_playerMap.size();
    PlayerMap& playerMap = playerRegistry.m_playerMap;
    
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
    {
        playerMap[playerIndex]->PrintPlayer();
    }
    
    //display rels
    for (int i=0; i < playerCount; i++)
    {
        for (int j=0; j < playerCount; j++)
        {
            if (i!=j)
            {
//                playerMap[i]->relMap[j].PrintRel(playerMap[i]->abstractPlayerData.m_playerName, playerMap[j]->abstractPlayerData.m_playerName);
            }
        }
    }
}
