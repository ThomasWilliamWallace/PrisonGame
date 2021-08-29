#pragma once

#include <vector>
#include <iostream>
#include "Locations.h"
#include "Constants.h"
#include "PlatformSpecific.h"
#include "AbstractItem.h"
#include "IHTNWorldState.h"

class MissionClass;

class HTNWorldState : public IHTNWorldState
{
public:
    UPlayerData* m_ptrToSelf;
    int m_health;
    int m_sanity;
    int m_strength;
    int m_agility;
    int m_intelligence;
    int m_evading;
    ELocations m_location;
    std::shared_ptr<MissionClass> m_missionClass;
    std::vector< std::shared_ptr<SimItem> > m_items;
    std::vector< std::shared_ptr<SimItem> > m_itemsToKeep; //items added to this list will not be surrendered if requested.
    std::shared_ptr<SimItem> m_itemCarriedPtr;
    UPlayerData* m_requester; // Pointer to the player who is requesting the currently carried item.
    std::vector<UPlayerData*> m_attackers;
    std::vector< UPlayerData* > m_playersInTheRoom;
    bool IsInTheRoom(UPlayerData const& playerPtr) const;
    HTNWorldState(HTNWorldState const& ws2);
    HTNWorldState(UPlayerData* playerPtr, PlayerMap& playerMap, std::vector<RealItemType*>& realItems,
                  UPlayerData* requester, std::vector<UPlayerData*> attackers, std::vector<UPlayerData*> playersInTheRoom,
                  float health, float sanity, float strength, float agility, float intelligence);
    HTNWorldState& operator=(HTNWorldState const& ws2);
    void Print() override;
    HTNWorldState* clone() const;
};
