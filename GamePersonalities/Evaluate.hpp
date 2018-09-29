//
//  Evaluate.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Evaluate_hpp
#define Evaluate_hpp

#include <stdio.h>
#include "Constants.hpp"

class Player;

//represents a players eventual objective function that they try to optimize

class Eval
{
public:
    std::vector<double> utilities;
    int maxAttackUtilityIndex;
    int maxMissionUtilityIndex;
    int maxFriendUtilityIndex;
    
    Eval():
        utilities(static_cast<int>(v_action.size()), 0),
        maxAttackUtilityIndex(-1),
        maxMissionUtilityIndex(-1),
        maxFriendUtilityIndex(-1) {}
};

double UtilityOfAttack(int playerIndex); //utility of attacking this player
double UtilityOfFriend(int playerIndex); //utility of making friends with this player
double UtilityOfMission(int playerIndex); //utility of assigning this player a mission
Eval UtilityOfAction(Player player[], int playerIndex); //utility of taking this action

#endif /* Evaluate_hpp */
