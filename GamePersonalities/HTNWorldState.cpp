//
//  HTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNWorldState.hpp"
#include "Locations.hpp"

//***********************************************************
HTNWorldState::HTNWorldState(): m_v(WorldE::last, 0)
{
    m_v.at(WorldE::health) = 70;
    m_v.at(WorldE::sanity) = 70;
    m_v.at(WorldE::strength) = 70;
    m_v.at(WorldE::agility) = 70;
    m_v.at(WorldE::intelligence) = 70;
    m_v.at(WorldE::punches) = 0;
    m_v.at(WorldE::location) = static_cast<int>(Locations::bedroom);
}

HTNWorldState::HTNWorldState(HTNWorldState &ws2): m_v(ws2.m_v) {}

void HTNWorldState::Print()
{
    for (int i = 0; i < static_cast<int>(m_v.size()); i++)
    {
        std::cout << WorldEToString(static_cast<WorldE>(i)) << ":" << m_v.at(i) << "\n";
    }
}

void HTNWorldState::CopyFrom(HTNWorldState &ws2)
{
    m_v = ws2.m_v;
}

std::string WorldEToString(WorldE worldE)
{
    switch(worldE)
    {
        case WorldE::health: return "health";
        case WorldE::sanity: return "sanity";
        case WorldE::strength: return "strength";
        case WorldE::agility: return "agility";
        case WorldE::intelligence: return "intelligence";
        case WorldE::punches: return "punches";
        case WorldE::location: return "location";
        case WorldE::last: return "LAST";
        default: return "ERROR_NO_WORLDE_STRING_FOUND";
    }
}