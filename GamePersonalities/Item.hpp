//
//  Item.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include "Locations.hpp"
#include <iostream>

class Player;

class Item
{
public:
    std::string m_name;
    LocationClass m_locationClass;
    Player* m_carryingPlayer;
    Item(std::string name, Locations location, Player* carryingPlayer=nullptr): m_name(name), m_locationClass(location), m_carryingPlayer(carryingPlayer){};
    std::string ToString();
};

#endif /* Item_hpp */
