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
    
    location,
    last
};

std::string WorldEToString(WorldE worldE);

class HTNWorldState
{
public:
    std::vector<int> m_v;
    HTNWorldState();
    HTNWorldState(HTNWorldState &ws2);
    void Print();
    void CopyFrom(HTNWorldState &ws2);
};

#endif /* HTNWorldState_hpp */