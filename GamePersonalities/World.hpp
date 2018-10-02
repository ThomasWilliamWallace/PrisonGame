//
//  World.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include "Player.hpp"
#include "Item.hpp"

class World //represents the simulated world
{
public:
    int weightsOccupied;
    int circuitsOccupied;
    int studyOccupied;
    int bedOccupied;
    void WorldEffects(Player player[], int frame);
    void PrintWorld(Player player[]);
    void Clean();
    World();
    std::vector< Item* > items;
};

#endif /* World_hpp */
