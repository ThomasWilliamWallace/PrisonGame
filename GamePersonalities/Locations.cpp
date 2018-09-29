//
//  Locations.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Locations.hpp"

LocationClass::LocationClass()
{
    location = Locations::mainHall;
}

std::string LocationClass::LocationToString()
{
    switch(location)
    {
        case (Locations::gym):
            return "Gym";
        case (Locations::circuitTrack):
            return "Circuit track";
        case (Locations::library):
            return "Library";
        case (Locations::bedroom):
            return "Bedroom";
        case (Locations::mainHall):
            return "Main hall";
    }
    return "UnrecognisedLocation";
}
