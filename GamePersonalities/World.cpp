//
//  World.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "World.hpp"
#include "Constants.hpp"

World::World()
{
    weightsOccupied = c_empty;
    circuitsOccupied = c_empty;
    studyOccupied = c_empty;
    bedOccupied = c_empty;
    items.push_back(new Item("Broom", Locations::mainHall));
    items.push_back(new Item("Brick", Locations::circuitTrack));
    items.push_back(new Item("Mirror", Locations::bedroom));
}

void World::Clean()
{
    bedOccupied = c_empty;
    circuitsOccupied = c_empty;
    studyOccupied = c_empty;
    weightsOccupied = c_empty;
}

void World::WorldEffects(Player player[], int frame)
{
    if (bedOccupied != c_empty)
    {
        player[bedOccupied].stats.deltaHealth(1);
        player[bedOccupied].narrative = "sleep; health = " + FormatDouble(player[bedOccupied].stats.getHealth());
    }
    if (circuitsOccupied != c_empty)
    {
        player[circuitsOccupied].stats.deltaAgility(1);
        player[circuitsOccupied].narrative = "circuits; agility = " + FormatDouble(player[circuitsOccupied].stats.getAgility());
    }
    if (studyOccupied != c_empty)
    {
        player[studyOccupied].stats.deltaIntelligence(1);
        player[studyOccupied].narrative = "study; intelligence = " + FormatDouble(player[studyOccupied].stats.getIntelligence());
    }
    if (weightsOccupied != c_empty)
    {
        player[weightsOccupied].stats.deltaStrength(1);
        player[weightsOccupied].narrative = "weightlift; strength = " + FormatDouble(player[weightsOccupied].stats.getStrength());
    }
}

void World::PrintWorld(Player player[])
{
    std::cout << "*** WORLD DATA ***\n";
    std::cout << "weightsOccupied=" << CharacterName(player, 1) << "\n";
    std::cout << "circuitsOccupied=" << CharacterName(player, circuitsOccupied) << "\n";
    std::cout << "studyOccupied=" << CharacterName(player, studyOccupied) << "\n";
    std::cout << "bedOccupied=" << CharacterName(player, bedOccupied) << "\n";
    std::cout << "\n";
    for (auto &item : items)
    {
        std::cout << item->m_name << " is in the " << item->m_locationClass.ToString() << ".\n";
    }
    std::cout << "\n";
}