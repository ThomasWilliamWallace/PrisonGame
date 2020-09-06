#include "PlayerRegistry.h"
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
            Add(addPlayerData->relMap, otherKey, NewObject<URelationship>(addPlayerData, URelationship::StaticClass(), FName(*(FString::Printf(TEXT("Rel_%d_%d"), otherKey, addKey))), RF_MarkAsRootSet));
            Add(otherPlayerData->relMap, addKey, NewObject<URelationship>(otherPlayerData, URelationship::StaticClass(), FName(*(FString::Printf(TEXT("Rel_%d_%d"), addKey, otherKey))), RF_MarkAsRootSet));
        }
    }
}

void PlayerRegistry::DeregisterPlayer(int removeKey)
{
    UPlayerData* removePlayerData = m_playerMap[removeKey];
    RelMap& removeRelMap = removePlayerData->relMap;

	URelationship* rel1;
	URelationship* rel2;
    
    //remove relationships
	for (auto relIter = removeRelMap.CreateIterator(); relIter; ++relIter)
    {
        int otherKey = GetKey(*relIter);
        UPlayerData* otherPlayerData = m_playerMap[otherKey];

		rel1 = *(otherPlayerData->relMap.Find(removeKey));
        Remove(otherPlayerData->relMap, removeKey);

		rel2 = relIter->Value;
		RemoveCurrent(removeRelMap, relIter);

		delete rel1;
		delete rel2;
    }
    
    //remove from player registry
    Remove(m_playerMap, removeKey);

	//TODO delete removed playerData in Console build. PlayerData is memory managed by Unreal in the Unreal build.
}
