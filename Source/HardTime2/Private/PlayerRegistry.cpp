#include "PlayerRegistry.hpp"
#include "PlayerData.h"

void PlayerRegistry::RegisterPlayer(UPlayerData* addPlayerData)
{
    //add to player registry
    int addKey = 0;
    do {
        addKey += 1;
    } while (Contains(m_playerMap, addKey));
    Add(m_playerMap, addKey, addPlayerData);
    addPlayerData->m_key = addKey;
    
    //add relationships
    for(auto &playerIter : m_playerMap)
    {
        int otherKey = GetKey(playerIter);
        UPlayerData* otherPlayerData = GetPlayer(playerIter);
        
        if (addKey != otherKey)
        {
            Add(addPlayerData->relMap, otherKey, NewObject<URelationship>(addPlayerData));
            Add(otherPlayerData->relMap, addKey, NewObject<URelationship>(otherPlayerData));
        }
    }
}

void PlayerRegistry::DeregisterPlayer(int removeKey)
{
    UPlayerData* removePlayerData = m_playerMap[removeKey];
    RelMap& removeRelMap = removePlayerData->relMap;
    
    //remove relationships
	for (auto relIter = removeRelMap.CreateIterator(); relIter; ++relIter)
    {
        int otherKey = GetKey(*relIter);
        UPlayerData* otherPlayerData = m_playerMap[otherKey];
        Remove(otherPlayerData->relMap, removeKey);
		RemoveCurrent(removeRelMap, relIter);
    }
    
    //remove from player registry
    Remove(m_playerMap, removeKey);
}
