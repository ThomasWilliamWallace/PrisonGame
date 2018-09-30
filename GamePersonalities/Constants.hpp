//
//  Constants.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <stdio.h>
#include <iomanip> // setprecision
#include <sstream>
#include <algorithm>
using namespace std;

constexpr int c_empty = -1;
constexpr int c_playerCount = 2;
constexpr double c_aggro_scale = 30;
constexpr double c_aggroCooldown = 0.15;

enum class AI
{
    doNothingAI, //does nothing
    randomAI, //basic set of random actions.
    aggroAI, //uses aggro to determine attacks
    humanAI, //decisions come from player input
    greedyAI, //uses a greedy search with utility
    htnAI //uses an HTN to search with utility
};

enum class Actions //MUST KEEP IN SYNC WITH V_ACTION
{
    attack,
    useRoom,
    goToLibrary,
    goToGym,
    goToCircuitTrack,
    goToBedroom,
    goToMainHall,
    evade,
	makeFriends,
    offerMission,
    noAction // serves as a flag for any unset actions
};

const std::vector<Actions> v_action //MUST KEEP IN SYNC WITH ACTIONS
{
    Actions::attack,
    Actions::useRoom,
    Actions::goToLibrary,
    Actions::goToGym,
    Actions::goToCircuitTrack,
    Actions::goToBedroom,
    Actions::goToMainHall,
    Actions::evade,
    Actions::makeFriends,
    Actions::offerMission,
    Actions::noAction,
};

enum class Locations
{
    gym,
    circuitTrack,
    library,
    bedroom,
    mainHall
};

/*
 missions:
 assasinate
 bring item
 rough up
 steal item
 attack gang
 capture monkey
 bring person to location
 protect person
 hide item
 buy item
 sell item
 make friends with person
 make enemies with person
 let person out of cell
 destroy item
 wash incriminating item
 plant incriminating item
 buy drugs
 hook person on drugs
 guard drug dealers patch
 find witness
 coerce witness
 bribe witness
 murder witness
 keep person out of trouble
 bring incriminating item
 murder gang leader
 change appearance
 recommend man for a job
 testify against person
 testify for person
 find spy
 spy on
 (spy) give secret info on
 (spy) send person into trap
 increase strength
 increase agility
 increase intelligence
 increase charisma
 increase money
 increase reputation
 decrease reputation
 clean floor (can have someone else do it)
 mix chemicals (can have someone else do it)
 prepare food (can have someone else do it)
 do paperwork (can have someone else do it)
 */
enum class Missions
{
    noMission,
    increaseStrength,
    increaseAgility,
    increaseIntelligence
};

std::string FormatDouble(double input);
int RandPercent();
bool playerIndexOutOfBounds(int playerIndex);

inline const char * const BoolToString(bool b)
{
    return b ? "true" : "false";
};

/*
 Events:
 1: monkey enters the prison
 2: new prisoner enters prison
 3: hostile new gang enters prison
 4:
 */

#endif /* Constants_hpp */
