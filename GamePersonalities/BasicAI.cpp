//
//  BasicAI.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "BasicAI.hpp"
#include "Player.hpp"
#include <stdexcept>
#include "Constants.hpp"
#include "Evaluate.hpp"
#include "HTNDomain.hpp"
#include "World.hpp"

Actions AIController::ChooseRoom(int playerIndex, Player player[])
{
    if (player[playerIndex].locationClass.location == Locations::mainHall)
    {
        int random = RandPercent();
        if (random < 25)
        {
            return Actions::goToLibrary;
        }
        if (random < 50)
        {
            return Actions::goToGym;
        }
        if (random < 75)
        {
            return Actions::goToCircuitTrack;
        }
        return Actions::goToBedroom;
    } else
    {
        return Actions::goToMainHall;
    }
}

Actions AIController::ChooseAction(int playerIndex, Player player[], World &world)
{
    bool playersInReach[c_playerCount];
    int countPlayersInReach = 0;
    
    for (int i = 0; i < c_playerCount; i++)
    {
        if (OtherInReach(playerIndex, i, player))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach[i] = false;
    }
    
    switch(player[playerIndex].aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(playerIndex, player, playersInReach, countPlayersInReach);
        case(AI::randomAI):
            return RandomAIChooseAction(playerIndex, player, playersInReach, countPlayersInReach);
        case(AI::aggroAI):
            return aggroAIChooseAction(playerIndex, player, playersInReach, countPlayersInReach);
        case(AI::humanAI):
            return humanAIChooseAction(playerIndex, player, world, playersInReach, countPlayersInReach);
        case(AI::greedyAI):
            return greedyAIChooseAction(playerIndex, player, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return htnAIChooseAction(playerIndex, player, world, playersInReach, countPlayersInReach);
    }
	return RandomAIChooseAction(playerIndex, player, playersInReach, countPlayersInReach);
}

void AIController::CreateMissionOffer(Player player[], int playerIndex, bool playersInReach[], int countPlayersInReach)
{
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < c_playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                player[playerIndex].playerTarget = i;
                player[playerIndex].missionOffer = CreateNewMission(player, player[playerIndex].playerTarget);
                return;
            }
            target += 1;
        }
    }
}

int AIController::TargetForMakeFriend(Player player[], int playerIndex, bool playersInReach[], int countPlayersInReach)
{
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < c_playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                return i;
            }
            target += 1;
        }
    }
    throw std::out_of_range("Failed to pick a player in reach to make friends with.");
}

Actions AIController::DoNothingAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach)
{
    return Actions::noAction;
}

Actions AIController::RandomAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach)
{
    if (countPlayersInReach > 0)
    {
        if (RandPercent() < player[playerIndex].stats.aggression)
        {
            // attack --a random target in the room
            int target = 0;
            double random = RandPercent();
            for (int i = 0; i < c_playerCount; i++)
            {
                if (playersInReach[i] == true)
                {
                    if (random <= (100 * (target + 1) / countPlayersInReach))
                    {
                        player[playerIndex].playerTarget = i;
                        return Actions::attack;
                    }
                    target += 1;
                }
            }
            std::cout << "ERROR: FAILED TO FIND ANY TARGET TO RANDOMLY ATTACK\n";
            player[playerIndex].playerTarget = c_empty;
            return Actions::attack;
        } else if (RandPercent() < 25)
        {
            return Actions::evade;
        } else if (RandPercent() < 35)
        {
            player[playerIndex].playerTarget = TargetForMakeFriend(player, playerIndex, playersInReach, countPlayersInReach);
            return Actions::makeFriends;
        } else if (RandPercent() < 50)
        {
            CreateMissionOffer(player, playerIndex, playersInReach, countPlayersInReach);
            return Actions::offerMission;
        } else
        {
            return ChooseRoom(playerIndex, player);
        }
    } else if (RandPercent() < 80) {
        return Actions::useRoom;
    } else
    {
        return ChooseRoom(playerIndex, player);
    }
    return Actions::noAction;
}

Actions AIController::aggroAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach)
{
    if (countPlayersInReach > 0)
    {
        double aggros[c_playerCount];
        for (int i = 0; i < c_playerCount; i++)
        {
            aggros[i] = player[playerIndex].rel[i].getAggro() * player[playerIndex].stats.aggression/100;
        }
        
        double fears[c_playerCount];
        for (int i = 0; i < c_playerCount; i++)
        {
            fears[i] = player[playerIndex].rel[i].getFear() * (1-(player[playerIndex].stats.proud/100));
        }
        
        double friendlinesses[c_playerCount];
        for (int i = 0; i < c_playerCount; i++)
        {
            friendlinesses[i] = player[playerIndex].rel[i].getFriendliness(); // multiply by a friendliness personality constant?
        }
        
        double max_aggro = -1;
        int max_aggro_index = -1;
        double aggroTemp;
        // Choose the most aggro/hostile character to attack
        for (int i = 0; i < c_playerCount; i++)
        {
            aggroTemp = aggros[i] * (100 - fears[i]) * (100 - friendlinesses[i]) / (100 * 100); // willingness to attack this character. Increases with aggro, decreases with fear.
         //   std::cout << "aggro[" << i << "]=" << aggros[i] << ", fears[" << i << "]=" << fears[i] << ", friendlinesses[" << i << "]=" << friendlinesses[i] << ", aggroTemp=" << aggroTemp << "\n";
            if (aggroTemp > max_aggro)
            {
                max_aggro = aggroTemp;
                max_aggro_index = i;
            }
        }

        if (RandPercent() < (c_aggro_scale * max_aggro * player[playerIndex].stats.aggression / 100))
        {
			if (RandPercent() < 25)
			{
				return Actions::evade;
			} else
			{
				player[playerIndex].playerTarget = max_aggro_index;
				return Actions::attack;
			}
        } else if (RandPercent() < 20)
        {
            player[playerIndex].playerTarget = TargetForMakeFriend(player, playerIndex, playersInReach, countPlayersInReach);
            return Actions::makeFriends;
        } else if (RandPercent() < 60)
        {
            CreateMissionOffer(player, playerIndex, playersInReach, countPlayersInReach);
            return Actions::offerMission;
        } else
        {
            return ChooseRoom(playerIndex, player);
        }
    } else if (RandPercent() < 80)
    {
        return Actions::useRoom;
    } else
    {
        return ChooseRoom(playerIndex, player);
    }
    return Actions::noAction;
}

Actions AIController::greedyAIChooseAction(int playerIndex, Player player[], bool playersInReach[], int countPlayersInReach)
{    
    //find the index of the action with the highest utility
    int maxIndex = -1;
    double maxUtility = -1;
    Eval eval = UtilityOfAction(player, playerIndex);
    for (int i=0; i < static_cast<int>(eval.utilities.size()); i++)
    {
        if (eval.utilities.at(i) > maxUtility)
        {
            maxIndex = i;
            maxUtility = eval.utilities.at(maxIndex);
        }
    }
    Actions maxActionUtilityIndex = static_cast<Actions>(maxIndex);
    
    switch (maxActionUtilityIndex)
    {
        case Actions::attack:
            player[playerIndex].playerTarget = eval.maxAttackUtilityIndex;
            break;
        case Actions::makeFriends:
            player[playerIndex].playerTarget = eval.maxFriendUtilityIndex;
            break;
        case Actions::offerMission:
            player[playerIndex].playerTarget = eval.maxMissionUtilityIndex;
            player[playerIndex].missionOffer = CreateNewMission(player, player[playerIndex].playerTarget);
            break;
        default:
            break;
    }
    
    return maxActionUtilityIndex;
}

Actions AIController::htnAIChooseAction(int playerIndex, Player player[], World &world, bool playersInReach[], int countPlayersInReach)
{
    //update worldstate from real world
    HTNWorldState htnWorldState(playerIndex, player, world);
    
    bool hasValidPlan = false;
    // check if next step of the plan is valid.
    
    if (!lastActionSucceeded)
    {
        hasValidPlan = false;
    } else if (htnPlan.size() > 0)
    {
        hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
    }
    
    //If plan is not valid, abandon it and try to make a new plan
    if (!hasValidPlan)
    {
        //make new plan
        std::cout << "Make a new plan\n";
        HTNWorldState htnWorldStateDFSCopy(htnWorldState);
        HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);
        htnPlan = HTNdfs(htnWorldStateDFSCopy, *missionPtr, 0);
        for (auto &htnPrimitive : htnPlan)
        {
            htnPrimitive->PointToRealItems(htnWorldStateDFSCopy);
        }
        
        //once again, check if next step of the plan is valid.
        if (htnPlan.size() > 0)
        {
            hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
        }
    }
    
    if (!hasValidPlan)
    {
        std::cout << "Give up and return noAction\n";
        return Actions::noAction; //If next step of the plan is still not valid, then return failure state
    } else {
        //continue with current plan
        std::cout << "Continue\n";
        HTNPrimitivePtr currentPlanStep = htnPlan.front();
        htnPlan.pop_front();
        return currentPlanStep->Operator(playerIndex, player, world);
    }
}

Actions AIController::humanAIChooseAction(int playerIndex, Player player[], World &world, bool playersInReach[], int countPlayersInReach)
{
    string input;
    int targetPlayer;
    std::cout << "Choose action:";
    int itemsInRoom;
    int playersInRoom;
    while (true)
    {
        std::cin >> input;
        switch(input[0]){
        case 'v':
            std::cout << "Room contains:\n";
            playersInRoom = 0;
            for (int i = 0; i < c_playerCount; i++)
            {
                if (player[i].locationClass.location == player[playerIndex].locationClass.location)
                {
                    std::cout << "Player \"" << player[i].name << "\", (index=" << i << ")\n";
                    playersInRoom += 1;
                }
            }
            if (playersInRoom == 0)
            {
                std::cout << "No players in room.\n";
            }
            itemsInRoom = 0;
            for (auto &item : world.items)
            {
                if (item->m_locationClass.location == player[playerIndex].locationClass.location)
                {
                    std::cout << "Item \"" << item->ToString() << "\", (index=" << itemsInRoom << ")\n";
                    itemsInRoom += 1;
                }
            }
            if (itemsInRoom == 0)
            {
                std::cout << "No items in room.\n";
            }
            std::cout << "\n";
            break;
        case 'q':
            exit(0);
        case 'h':
            std::cout << "Commands:\n";
            std::cout << "v: view room\n";
            std::cout << "a: " << ActionToString(Actions::attack) << "\n";
            std::cout << "e: " << ActionToString(Actions::evade) << "\n";
            std::cout << "b: " << ActionToString(Actions::goToBedroom) << "\n";
            std::cout << "c: " << ActionToString(Actions::goToCircuitTrack) << "\n";
            std::cout << "g: " << ActionToString(Actions::goToGym) << "\n";
            std::cout << "l: " << ActionToString(Actions::goToLibrary) << "\n";
            std::cout << "m: " << ActionToString(Actions::goToMainHall) << "\n";
            std::cout << "p: " << ActionToString(Actions::pickUpItem) << "\n";
            std::cout << "d: " << ActionToString(Actions::dropItem) << "\n";
            std::cout << "f: " << ActionToString(Actions::makeFriends) << "\n";
            std::cout << "o: " << ActionToString(Actions::offerMission) << "\n";
            std::cout << "u: " << ActionToString(Actions::useRoom) << "\n";
            std::cout << "h: display help\n";
            std::cout << "q: quit\n";
            break;
        case 'a':
            while (true)
            {
                std::cout << "Choose target player:";
                std::cin >> targetPlayer;
                player[playerIndex].playerTarget = targetPlayer;
                return Actions::attack;
            }
        case 'e': return Actions::evade;
        case 'b': return Actions::goToBedroom;
        case 'c': return Actions::goToCircuitTrack;
        case 'g': return Actions::goToGym;
        case 'l': return Actions::goToLibrary;
        case 'm': return Actions::goToMainHall;
        case 'p': 
            while (true)
            {
                std::cout << "Choose target item (-1 means no item):";
                int targetItem;
                std::cin >> targetItem;
                if (targetItem == -1)
                {
                    player[playerIndex].itemFocusPtr = nullptr;
                    return Actions::pickUpItem;
                } else if (targetItem < 0 || targetItem >= static_cast<int>(world.items.size())) 
                {
                    std::cout << "ERROR: invalid target item index. Please enter a new action:\n";
                    break;
                } else {
                    player[playerIndex].itemFocusPtr = world.items.at(targetItem);
                    return Actions::pickUpItem;
                }
            }
            break;
        case 'd': return Actions::dropItem;
        case 'f':
            while (true)
            {
                std::cout << "Choose target player:";
                std::cin >> targetPlayer;
                player[playerIndex].playerTarget = targetPlayer;
                return Actions::makeFriends;
            }
        case 'o':
            while (true)
            {
                std::cout << "Choose target player:";
                std::cin >> targetPlayer;
                player[playerIndex].playerTarget = targetPlayer;
                player[playerIndex].missionOffer = CreateNewMission(player, targetPlayer);
                return Actions::offerMission;
            }
        case 'u': return Actions::useRoom;
        }
    }
    return Actions::noAction;
}

AIController::AIController(AI _algo)
{
    algo = _algo;
}

AIController::AIController()
{
    algo = AI::randomAI;
}