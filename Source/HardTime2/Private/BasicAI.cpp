#include "BasicAI.hpp"
#include "Player.hpp"
#include <stdexcept>
#include "HTNDomain.hpp"
#include "RequestHTNDomain.hpp"
#include "World.hpp"
#include "Actions.hpp"
#include <sstream>
#include "pLog.hpp"
#include "AICharacterC.h"

Actions AIController::ChooseRoom(Player* playerPtr, Player player[])
{
    if (playerPtr->locationClass.location == ELocations::mainHall)
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

Actions AIController::ChooseAction(Player* playerPtr, Player player[], World &world, AAICharacterC* aiCharacterC)
{
    bool playersInReach[c_playerCount];
    int countPlayersInReach = 0;
    
    for (int i = 0; i < c_playerCount; i++)
    {
        if (OtherInReach(playerPtr, &(player[i]), player))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach[i] = false;
    }
    
    switch(playerPtr->aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(playerPtr, player, playersInReach, countPlayersInReach);
        case(AI::randomAI):
            return RandomAIChooseAction(playerPtr, player, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return HTNAIChooseAction(aiCharacterC);
    }
	return RandomAIChooseAction(playerPtr, player, playersInReach, countPlayersInReach);
}

void AIController::CreateMissionOffer(Player player[], Player* playerPtr, bool playersInReach[], int countPlayersInReach)
{
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < c_playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                playerPtr->playerTargetPtr = &(player[i]);
                playerPtr->missionOffer = CreateNewMission(playerPtr->playerTargetPtr);
                return;
            }
            target += 1;
        }
    }
}

Player* AIController::TargetForMakeFriend(Player player[], Player* playerPtr, bool playersInReach[], int countPlayersInReach)
{
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < c_playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                return &(player[i]);
            }
            target += 1;
        }
    }
    throw std::out_of_range("Failed to pick a player in reach to make friends with.");
}

Actions AIController::DoNothingAIChooseAction(Player* playerPtr, Player player[], bool playersInReach[], int countPlayersInReach)
{
    return Actions::noAction;
}

Actions AIController::RandomAIChooseAction(Player* playerPtr, Player player[], bool playersInReach[], int countPlayersInReach)
{
    if (countPlayersInReach > 0)
    {
        if (RandPercent() < playerPtr->pStats.aggression)
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
                        playerPtr->playerTargetPtr = &(player[i]);
                        return Actions::attack;
                    }
                    target += 1;
                }
            }
            std::cout << "ERROR: FAILED TO FIND ANY TARGET TO RANDOMLY ATTACK\n";
            playerPtr->playerTargetPtr = nullptr;
            return Actions::attack;
        } else if (RandPercent() < 25)
        {
            return Actions::evade;
        } else
        {
            return ChooseRoom(playerPtr, player);
        }
    } else if (RandPercent() < 80) {
        return Actions::useRoom;
    } else
    {
        return ChooseRoom(playerPtr, player);
    }
    return Actions::noAction;
}

Actions AIController::HTNAIChooseAction(AAICharacterC* aiCharacterC)
{
	pLog("Entering htnAIChooseAction", true);
	//update worldstate from real world
	HTNWorldState htnWorldState(&(aiCharacterC->m_player), aiCharacterC->m_world);

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

	if ((aiCharacterC->lastPrimitiveAction != nullptr) && !(aiCharacterC->lastPrimitiveAction->LastActionSucceeded(htnWorldState, aiCharacterC)))
	{
		pLog("Last Action did not succeed", true);
		hasValidPlan = false;
	}
	else if (aiCharacterC->m_player.aiController.htnPlan.size() > 0)
	{
		pLog("Check Precondition of plan primitive step", true);
		hasValidPlan = (aiCharacterC->m_player.aiController.htnPlan).at(0)->Preconditions(htnWorldState);
	}

	//If plan is not valid, abandon it and try to make a new plan
	if (!hasValidPlan)
	{
		pLog("No valid plan exists! Try to replan.", true);
		//make new plan
		HTNWorldState htnWorldStateDFSCopy(htnWorldState);
		HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);
		aiCharacterC->m_player.aiController.htnPlan = HTNdfs(htnWorldStateDFSCopy, *missionPtr, 0);

		//once again, check if next step of the plan is valid.
		if ((aiCharacterC->m_player.aiController.htnPlan).size() > 0)
		{
			hasValidPlan = (aiCharacterC->m_player.aiController.htnPlan).at(0)->Preconditions(htnWorldState);
		}
	}

	if (!hasValidPlan)
	{
		pLog("No valid plan exists! Leaving htnAIChooseAction #1", true);
		return Actions::noAction; //If next step of the plan is still not valid, then return failure state
	}
	else {
		pLog("Valid plan found!"), true;
		//continue with current plan
		std::stringstream ss;
		ss << "Plan steps: ";
		for (auto &prim : aiCharacterC->m_player.aiController.htnPlan)
		{
			ss << prim->ToString() << ", ";
		}
		pLog(ss, true);
		HTNPrimitivePtr currentPlanStep = (aiCharacterC->m_player.aiController.htnPlan).front();
		aiCharacterC->lastPrimitiveAction = currentPlanStep;
		(aiCharacterC->m_player.aiController.htnPlan).pop_front();
		pLog("Leaving htnAIChooseAction #2", true);
		return currentPlanStep->Operate(aiCharacterC);
	}
	pLog("Leaving htnAIChooseAction #3", true);
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