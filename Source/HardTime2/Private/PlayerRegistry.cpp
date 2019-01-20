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
    addPlayerData->m_key = addKey;
    
    //add relationships
	/*
    for(auto playerIter = m_playerMap.cbegin(); playerIter != m_playerMap.cend(); ++playerIter)
    {
        int otherKey = playerIter->first;
        UPlayerData* otherPlayerData = playerIter->second;
        
        if (addKey != otherKey)
        {
            addPlayerData->relMap.Add(otherKey, new Relationship());
            otherPlayerData->relMap.Add(addKey, new Relationship());
        }
    }
	*/
}

void PlayerRegistry::DeregisterPlayer(int removeKey)
{
    UPlayerData* removePlayerData = m_playerMap[removeKey];
    //RelMap& removeRelMap = removePlayerData->relMap;
    
    //remove relationships
    //for(auto relIter = removeRelMap.cbegin(); relIter != removeRelMap.cend(); /* no increment */)
		/*
    {
        int otherKey = relIter->first;
        UPlayerData* otherPlayerData = m_playerMap[otherKey];
        otherPlayerData->relMap.erase(removeKey);
        relIter = removeRelMap.erase(relIter);
    }
	*/
    
    //remove from player registry
    m_playerMap.Remove(removeKey);
}