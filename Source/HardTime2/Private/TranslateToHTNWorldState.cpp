#include "TranslateToHTNWorldState.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "PlayerRegistry.h"
#include "ActorItem.h"
#include "pLog.h"
#include <vector>

std::unique_ptr<HTNWorldState> TranslateToHTNWorldState(UPlayerData* playerPtr, USimWorld& simworld, PlayerMap& playerMap, UPlayerData* requester) {
    //TODO reflect players sensors rather than being hardwired to the world

    std::vector<RealItemType*> world_items;
    //    std::cout << "simworld.items:\n";
    for (auto& itemPtr : simworld.items)
    {
        //        std::cout << itemPtr << "\n";
        world_items.push_back(itemPtr);
    }
    //    std::cout << "\n";

    std::vector<UPlayerData*> attackers;
    std::vector<UPlayerData*> playersInTheRoom;
    for (const IntRelPair& pair : playerPtr->relMap)
    {
        int relIndex = pair.Key;
        URelationship* rel = pair.Value;
        if (rel != nullptr) {
            if (rel->getAggro() > 29)
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

    return std::make_unique<HTNWorldState>(playerPtr, playerMap, world_items, requesterPlayerData, attackers, playersInTheRoom,
                        playerPtr->pStats->getHealth(), playerPtr->pStats->getSanity(),
                        playerPtr->pStats->getStrength(), playerPtr->pStats->getAgility(), playerPtr->pStats->getIntelligence()
                        );
}

