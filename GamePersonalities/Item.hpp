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

enum class ItemType
{
    hammer,
    knife,
    brick,
    plank,
    mirror,
    pistol,
    ball,
    bat,
    rock,
    assaultRifle,
    scissors,
    dynamite,
    extinguisher,
    syringe,
    cigarette,
    bottle,
    cleaver,
    poolCue,
    dumbbell,
    broom,
    sword
};

class Item
{
public:
    ItemType m_itemE;
    LocationClass m_locationClass;
    Player* m_carryingPlayer;
    Item(ItemType itemE, Locations location, Player* carryingPlayer=nullptr): m_itemE(itemE), m_locationClass(location), m_carryingPlayer(carryingPlayer) {};
    std::string ToString();
};

class SimItem : public Item
{
public:
    Item& m_realItem;
    SimItem(Item &realItem, ItemType itemE, Locations location, Player* carryingPlayer=nullptr):
        Item(itemE, location, carryingPlayer), m_realItem(realItem)
    {};
};

#endif /* Item_hpp */
