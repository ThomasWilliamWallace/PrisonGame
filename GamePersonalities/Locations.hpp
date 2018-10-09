//
//  Locations.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Locations_hpp
#define Locations_hpp

#include <iostream>
#include "Constants.hpp"

class LocationClass
{
public:
    Locations location;
    LocationClass(Locations l=Locations::mainHall) : location(l){}
    LocationClass(const LocationClass& l) : location(l.location) {}
    std::string ToString();
};

std::string LocationToString(Locations location);
Locations GetRandomLocation();

#endif /* Locations_hpp */
