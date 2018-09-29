//
//  Constants.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include <stdio.h>
#include "Constants.hpp"

std::string FormatDouble(double input)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << input;
    return ss.str();
}

int RandPercent()
{
    return rand() % 100;
}

bool playerIndexOutOfBounds(int playerIndex)
{
    return ((playerIndex < 0) || (playerIndex > c_playerCount));
}