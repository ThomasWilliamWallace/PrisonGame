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
    Player* m_ptrToSelf;
    Item* m_itemCarriedPtr;
    std::vector<bool> m_attackers;
    std::vector<Locations> m_playerLocations;
    MissionClass m_missionClass;
    HTNWorldState(HTNWorldState &ws2);
    HTNWorldState(int playerIndex, Player player[], World &world);
    ~HTNWorldState();
    void CopyFrom(HTNWorldState &ws2);
    void Print();
};

#endif /* HTNWorldState_hpp */