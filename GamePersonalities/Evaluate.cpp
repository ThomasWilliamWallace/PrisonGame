//
//  Evaluate.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Evaluate.hpp"
#include "Constants.hpp"
#include "Actions.hpp"
#include "Player.hpp"

double UtilityOfAttack(Player player[], int playerIndex, int targetIndex, double aggros[])
{
//    int chance = RandPercent();
//    std::cout << "utilityOfAttack(" << playerIndex << ")=" << chance << "\n";
//    return chance;
    return aggros[targetIndex];
}

double UtilityOfFriend(Player player[], int playerIndex, int targetIndex)
{
//    int chance = RandPercent();
//    std::cout << "utilityOfFriend(" << playerIndex << ")=" << chance << "\n";
//    return chance;
    return 0;
}

double UtilityOfMission(Player player[], int playerIndex, int targetIndex)
{
//    int chance = RandPercent();
//    std::cout << "utilityOfMission(" << playerIndex << ")=" << chance << "\n";
//    return chance;
    return 0;
}

void ConsiderOfferMission(Eval& eval, Player player[], int playerIndex)
{
    double maxMissionUtility = -1;
    int maxMissionUtilityIndex = -1;
        
    double missionUtilityTemp;
    // Choose the most friendly/effective character to make set a mission
    // NOTE: this is only for missions that the character actually wants completed.
    // For warden missions and 'character building' tasks, assign randomly.
    for (int i = 0; i < c_playerCount; i++)
    {
      missionUtilityTemp = UtilityOfMission(player, playerIndex, i);
      if (missionUtilityTemp > maxMissionUtility)
        {
            maxMissionUtility = missionUtilityTemp;
            maxMissionUtilityIndex = i;
        }
    }

    eval.maxMissionUtilityIndex = maxMissionUtilityIndex;
    eval.utilities.at(static_cast<int>(Actions::offerMission)) = maxMissionUtility;
}

void ConsiderAttack(Eval& eval, Player player[], int playerIndex)
{
    double aggros[c_playerCount];
    for (int i = 0; i < c_playerCount; i++)
    {
        aggros[i] = player[playerIndex].rel[i].getAggro();
    }
        
    double maxAttackUtility = -1;
    int maxAttackUtilityIndex = -1;
        
    double attackUtilityTemp;
    // Choose the most hostile/threatening character to attack
    for (int i = 0; i < c_playerCount; i++)
    {
      attackUtilityTemp = UtilityOfAttack(player, playerIndex, i, aggros);
      std::cout << "aggros[" << i << "]=" << aggros[i] << "\n";
      if (attackUtilityTemp > maxAttackUtility)
        {
            maxAttackUtility = attackUtilityTemp;
            maxAttackUtilityIndex = i;
        }
    }

    eval.maxAttackUtilityIndex = maxAttackUtilityIndex;
    eval.utilities.at(static_cast<int>(Actions::attack)) = maxAttackUtility;
}

void ConsiderMakeFriend(Eval& eval, Player player[], int playerIndex)
{
    double maxFriendUtility = -1;
    int maxFriendUtilityIndex = -1;
        
    double friendUtilityTemp;
    // Choose the most effective/trustworthy character to make friends
    for (int i = 0; i < c_playerCount; i++)
    {
      friendUtilityTemp = UtilityOfFriend(player, playerIndex, i);
      if (friendUtilityTemp > maxFriendUtility)
        {
            maxFriendUtility = friendUtilityTemp;
            maxFriendUtilityIndex = i;
        }
    }

    eval.maxFriendUtilityIndex = maxFriendUtilityIndex;
    eval.utilities.at(static_cast<int>(Actions::makeFriends)) = maxFriendUtility;
}

void ConsiderMission(Eval& eval, Player player[], int playerIndex)
{
    /*
    switch (player[playerIndex].missionClass.m_mission)
    {
        case Missions::increaseIntelligence:
            if (player[playerIndex].locationClass.location == Locations::library)
            {
                eval.utilities.at(static_cast<int>(Actions::useRoom)) += 100;
                break;
            } else if (player[playerIndex].locationClass.location == Locations::mainHall)
            {
                eval.utilities.at(static_cast<int>(Actions::goToLibrary)) += 100;
                break;
            } else
            {
                eval.utilities.at(static_cast<int>(Actions::goToMainHall)) += 100;
                break;
            }
        case Missions::increaseAgility:
            if (player[playerIndex].locationClass.location == Locations::circuitTrack)
            {
                eval.utilities.at(static_cast<int>(Actions::useRoom)) += 100;
                break;
            } else if (player[playerIndex].locationClass.location == Locations::mainHall)
            {
                eval.utilities.at(static_cast<int>(Actions::goToCircuitTrack)) += 100;
                break;
            } else
            {
                eval.utilities.at(static_cast<int>(Actions::goToMainHall)) += 100;
                break;
            }
        case Missions::increaseStrength:
            if (player[playerIndex].locationClass.location == Locations::gym)
            {
                eval.utilities.at(static_cast<int>(Actions::useRoom)) += 100;
                break;
            } else if (player[playerIndex].locationClass.location == Locations::mainHall)
            {
                eval.utilities.at(static_cast<int>(Actions::goToGym)) += 100;
                break;
            } else
            {
                eval.utilities.at(static_cast<int>(Actions::goToMainHall)) += 100;
                break;
            }
        case Missions::noMission:
            break;
    }
     */
}

Eval UtilityOfAction(Player player[], int playerIndex)
{
//    bool playersInReach[c_playerCount];
    int countPlayersInReach = 0;
    
    for (int i = 0; i < c_playerCount; i++)
    {
        if (OtherInReach(playerIndex, i, player))
        {
//            playersInReach[i] = true;
            countPlayersInReach += 1;
        }
//            playersInReach[i] = false;
    }
    
    Eval eval;
    
    eval.utilities.at(static_cast<int>(Actions::noAction)) += 1;
    if (countPlayersInReach > 0)
    {
//        assess each nearby player
        
//        double fears[c_playerCount];
//        for (int i = 0; i < c_playerCount; i++)
//        {
//            fears[i] = player[playerIndex].rel[i].getFear() * (1-(player[playerIndex].stats.proud/100));
//        }
//        
//        double friendlinesses[c_playerCount];
//        for (int i = 0; i < c_playerCount; i++)
//        {
//            friendlinesses[i] = player[playerIndex].rel[i].getFriendliness(); // multiply by a friendliness personality constant?
//        }
    
        ConsiderAttack(eval, player, playerIndex);
        ConsiderMakeFriend(eval, player, playerIndex);
        ConsiderOfferMission(eval, player, playerIndex);
    }
    
    //TODO consider immediate fights
    
    //consider missions
    ConsiderMission(eval, player, playerIndex);
    
    //TODO consider buffing stats
    
    //TODO what else
//    utilities.at(static_cast<int>(Actions::evade)) += 1;
    
    return eval;
}