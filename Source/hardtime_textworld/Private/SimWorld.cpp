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
        bedOccupied->pStats.deltaHealth(1);
        bedOccupied->narrative = "sleep; health = " + FormatDouble(bedOccupied->pStats.getHealth());
    }
    if (circuitsOccupied != nullptr)
    {
        circuitsOccupied->pStats.deltaAgility(1);
        circuitsOccupied->narrative = "circuits; agility = " + FormatDouble(circuitsOccupied->pStats.getAgility());
    }
    if (studyOccupied != nullptr)
    {
        studyOccupied->pStats.deltaIntelligence(1);
        studyOccupied->narrative = "study; intelligence = " + FormatDouble(studyOccupied->pStats.getIntelligence());
    }
    if (weightsOccupied != nullptr)
    {
        weightsOccupied->pStats.deltaStrength(1);
        weightsOccupied->narrative = "weightlift; strength = " + FormatDouble(weightsOccupied->pStats.getStrength());
    }
}

void USimWorld::PrintWorld()
{
    std::cout << "*** WORLD DATA ***\n";
    std::cout << "weightsOccupied=";
    if (weightsOccupied != nullptr) {
        std::cout << weightsOccupied->m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (circuitsOccupied != nullptr) {
        std::cout << circuitsOccupied->m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (studyOccupied != nullptr) {
        std::cout << studyOccupied->m_playerName << "\n";
    } else {
        std::cout << "empty" << "\n";
    }
    if (bedOccupied != nullptr) {
        std::cout << bedOccupied->m_playerName << "\n";
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
//                playerMap[i]->relMap[j].PrintRel(playerMap[i]->UPlayerData.m_playerName, playerMap[j]->UPlayerData.m_playerName);
            }
        }
    }
}
