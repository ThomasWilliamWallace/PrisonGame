//
//  BasicAI.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef BasicAI_hpp
#define BasicAI_hpp

#include "Actions.hpp" //todo remove
#include "Constants.hpp"
#include "HTN.hpp"

class World;

class AIController
{
    AI algo;
    HTNPrimitiveList htnPlan;
    Actions ChooseRoom(int playerIndex, Player player[]);
    Actions DoNothingAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach);
    Actions RandomAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach);
    Actions aggroAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach);
    Actions humanAIChooseAction(int playerIndex, Player player[], World &world, bool playersInReach[], int countPlayersInReach);
    Actions greedyAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach);
    Actions htnAIChooseAction(int playerIndex, Player player[], World &world, bool playersInReach[], int countPlayersInReach);
    void CreateMissionOffer(Player player[], int playerIndex, bool playersInReach[], int countPlayersInReach);
    int TargetForMakeFriend(Player player[], int playerIndex, bool playersInReach[], int countPlayersInReach);
public:
    Actions ChooseAction(int playerIndex, Player player[], World &world);
    AIController(AI _algo);
    AIController();
    bool lastActionSucceeded;
};

#endif /* BasicAI_hpp */
