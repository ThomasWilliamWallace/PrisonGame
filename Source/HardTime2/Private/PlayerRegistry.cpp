#include "PlayerRegistry.hpp"
#include "PlayerData.h"

void PlayerRegistry::RegisterPlayer(UPlayerData* addPlayerData)
{
    //add to player registry
    int addKey = 0;
    do {
        addKey += 1;
    } while (m_playerMap.Contains(addKey));
    m_playerMap.Add(addKey, addPlayerData);
    addPlayerData->m_newKey = addKey;
    
    //add relationships
    for(auto &playerIter : m_playerMap)
    {
        int otherKey = playerIter.Key;
        UPlayerData* otherPlayerData = playerIter.Value;
        
        if (addKey != otherKey)
        {
            addPlayerData->relMap.Add(otherKey, new Relationship());
            otherPlayerData->relMap.Add(addKey, new Relationship());
        }
    }
}

void PlayerRegistry::DeregisterPlayer(int removeKey)
{
    UPlayerData* removePlayerData = m_playerMap[removeKey];
    RelMap& removeRelMap = removePlayerData->relMap;
    
    //remove relationships
    //for(auto relIter = removeRelMap.cbegin(); relIter != removeRelMap.cend(); /* no increment */)
    for(auto &relIter : removeRelMap)

    {
        int otherKey = relIter.Key;
        UPlayerData* otherPlayerData = m_playerMap[otherKey];
        otherPlayerData->relMap.Remove(removeKey);
        removeRelMap.Remove(otherKey);
		//NOT SAFE TO CONTINUE ITERATING. IF YOU NEED TO CONTINUE ITERATING, USE ITERATOR.REMOVECURRENT().
		break;
    }
    
    //remove from player registry
    m_playerMap.Remove(removeKey);
}