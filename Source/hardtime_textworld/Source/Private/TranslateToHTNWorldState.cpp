#include "TranslateToHTNWorldState.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "PlayerRegistry.h"
#include "Item.h"
#include <vector>

HTNWorldState TranslateToHTNWorldState(UPlayerData* playerPtr, USimWorld& simworld, PlayerMap& playerMap, UPlayerData* requester) {
    //TODO reflect players sensors rather than being hardwired to the world
    
    std::vector<AbstractItem*> world_items;
//    std::cout << "simworld.items:\n";
    for (auto& itemPtr : simworld.items)
    {
//        std::cout << itemPtr << "\n";
        world_items.push_back(itemPtr);
    }
//    std::cout << "\n";
    
    AbstractItemPtr itemCarriedPtr = nullptr;
    
    std::vector<UPlayerData*> attackers;
    std::vector<UPlayerData*> playersInTheRoom;
    for (auto relIter = playerPtr->relMap.cbegin(); relIter != playerPtr->relMap.cend(); ++relIter)
    {
        int relIndex = relIter->first;
        URelationship* rel = relIter->second;
        if (rel != nullptr) {
            if (rel->getAggro()>29)
            {
                attackers.push_back(playerMap[relIndex]);
            }
            if (playerMap[relIndex]->locationClass.location == playerPtr->locationClass.location && playerMap[relIndex] != playerPtr)
            {
                playersInTheRoom.push_back(playerMap[relIndex]);
            }
        }
    }
    
    UPlayerData* requesterPlayerData = nullptr;
    if (requester != nullptr) {
        requesterPlayerData = requester;
    }
    
    return HTNWorldState(playerPtr, playerMap, world_items, requesterPlayerData, attackers, playersInTheRoom,
                        playerPtr->pStats.getHealth(), playerPtr->pStats.getSanity(),
                        playerPtr->pStats.getStrength(), playerPtr->pStats.getAgility(), playerPtr->pStats.getIntelligence()
                        );
}

