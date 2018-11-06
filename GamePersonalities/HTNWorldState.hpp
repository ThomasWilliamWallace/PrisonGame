//
//  HTNWorldState.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef HTNWorldState_hpp
#define HTNWorldState_hpp
#include <vector>
#include <iostream>
#include "Locations.hpp"
#include "Missions.hpp"

enum WorldE
{
    health,
    sanity,
    strength,
    agility,
    intelligence,
    
    punches,
    evading,
    
    location,
    inSameRoom,  //TODO adapt this to multiple players. not currently used.
    last
};

std::string WorldEToString(WorldE worldE);

class Player;
class SimItem;
class World;

class HTNWorldState
{
public:
    std::vector<int> m_v;
    std::vector< SimItem* > m_items;
    std::vector< Item* > m_itemsToKeep; //items added to this list will not be surrendered if requested.
    Player* m_ptrToSelf;
    Item* m_itemCarriedPtr;
    Player* m_requester; // Pointer to the player who is requesting the currently carried item.
    std::vector<bool> m_attackers;
    bool m_inTheRoom[c_playerCount];
    MissionClass m_missionClass;
    HTNWorldState(HTNWorldState &ws2);
    HTNWorldState(int playerIndex, Player player[], World &world, Player* requester);
    ~HTNWorldState();
    void CopyFrom(HTNWorldState &ws2);
    void Print();
};

#endif /* HTNWorldState_hpp */