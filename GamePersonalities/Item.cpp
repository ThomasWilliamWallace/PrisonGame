//
//  Item.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Item.hpp"

std::string Item::ToString()
{
    switch(m_itemE)
    {
        case ItemType::assaultRifle:
            return "Assault Rifle";
        case ItemType::ball:
            return "Ball";
        case ItemType::bat:
            return "Bat";
        case ItemType::bottle:
            return "Bottle";
        case ItemType::brick:
            return "Brick";
        case ItemType::broom:
            return "Broom";
        case ItemType::cigarette:
            return "Cigarette";
        case ItemType::cleaver:
            return "Cleaver";
        case ItemType::dumbbell:
            return "Dumbbell";
        case ItemType::dynamite:
            return "Dynamite";
        case ItemType::extinguisher:
            return "Extinguisher";
        case ItemType::hammer:
            return "Hammer";
        case ItemType::knife:
            return "Knife";
        case ItemType::mirror:
            return "Mirror";
        case ItemType::pistol:
            return "Pistol";
        case ItemType::plank:
            return "Plank";
        case ItemType::poolCue:
            return "Pool Cue";
        case ItemType::rock:
            return "Rock";
        case ItemType::scissors:
            return "Scissors";
        case ItemType::sword:
            return "Sword";
        case ItemType::syringe:
            return "Syringe";
    }
    return "ERROR: NO ITEM NAME";
}