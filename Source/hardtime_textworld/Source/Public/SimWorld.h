#pragma once

#include <stdio.h>
#include "AbstractPlayerData.h"
#include "PlayerRegistry.h"
#include "Item.h"

class USimWorld //represents the simulated world
{
public:
    UPlayerData* weightsOccupied;
    UPlayerData* circuitsOccupied;
    UPlayerData* studyOccupied;
    UPlayerData* bedOccupied;
    void WorldEffects();
    void PrintWorld();
    void FullDisplay();
    void Clean();
    USimWorld();
    std::vector< Item* > items;
    UPlayerRegistry playerRegistry;
};
