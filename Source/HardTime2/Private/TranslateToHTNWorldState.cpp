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

    std::vector<AbstractPlayerData*> attackers;
    std::vector<AbstractPlayerData*> playersInTheRoom;
    for (const IntRelPair& pair : playerPtr->relMap)
    {
        int relIndex = pair.Key;
        URelationship* rel = pair.Value;
        if (rel != nullptr) {
            if (rel->getAggro() > 29)
            {
                attackers.push_back(&(playerMap[relIndex]->abstractPlayerData));
            }
            if (playerMap[relIndex]->abstractPlayerData.locationClass.location == playerPtr->abstractPlayerData.locationClass.location && playerMap[relIndex] != playerPtr)
            {
                playersInTheRoom.push_back(&(playerMap[relIndex]->abstractPlayerData));
            }
        }
    }

    AbstractPlayerData* requesterAbstractPlayerData = nullptr;
    if (requester != nullptr)
    {
        requesterAbstractPlayerData = &(requester->abstractPlayerData);
    }

    std::unique_ptr<HTNWorldState> temp = std::make_unique<HTNWorldState>(&(playerPtr->abstractPlayerData), playerMap, world_items, requesterAbstractPlayerData, attackers, playersInTheRoom);
    pLog("TEST TEST TEST");
    return temp;
}