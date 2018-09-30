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
    mission,
    inSameRoom,  //TODO adapt this to multiple players
    last
};

std::string WorldEToString(WorldE worldE);

class Player;

class HTNWorldState
{
public:
    std::vector<int> m_v;
    HTNWorldState();
    HTNWorldState(HTNWorldState &ws2);
    HTNWorldState(int playerIndex, Player player[]);
    void Print();
    void CopyFrom(HTNWorldState &ws2);
};

#endif /* HTNWorldState_hpp */