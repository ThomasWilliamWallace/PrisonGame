#include "PlayerRegistry.h"
#include "AbstractPlayerData.h"

void UPlayerRegistry::RegisterPlayer(UPlayerData* addPlayerData)
{
    //add to player registry
    int addKey = 0;
    while (Contains(m_playerMap, addKey)) {
        addKey += 1;
    }
    Add(m_playerMap, addKey, addPlayerData);
    addPlayerData->abstractPlayerData.m_key = addKey;
    
    //add relationships
    for(auto &playerIter : m_playerMap)
    {
        int otherKey = GetKey(playerIter);
        UPlayerData* otherPlayerData = GetPlayer(playerIter);
        
        if (addKey != otherKey)
        {
            Add(addPlayerData->relMap, otherKey, new URelationship());  //TODO memory management
            Add(otherPlayerData->relMap, addKey, new URelationship());
        }
    }
}

void UPlayerRegistry::DeregisterPlayer(int removeKey)
{
    UPlayerData* removePlayerData = m_playerMap[removeKey];
    RelMap& removeRelMap = removePlayerData->relMap;
    
    //remove relationships
    for (auto const& relIter : removeRelMap)
    {
        int otherKey = relIter.first;
        UPlayerData* otherPlayerData = m_playerMap[otherKey];

        Remove(otherPlayerData->relMap, removeKey);
    }
    
    //remove from player registry
    Remove(m_playerMap, removeKey);

	//TODO delete removed playerData in Console build. PlayerData is memory managed by Unreal in the Unreal build.
}
