#include "BasicAI.hpp"
#include "PlayerData.h"
#include <stdexcept>
#include "HTNDomain.hpp"
#include "RequestHTNDomain.hpp"
#include "SimWorld.h"
#include "Actions.hpp"
#include <sstream>
#include "pLog.hpp"

Actions AIController::ChooseRoom(UPlayerData* playerData, UPlayerData player[])
{
    if (playerData->locationClass.location == ELocations::mainHall)
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

Actions AIController::ChooseAction(UPlayerData* playerData, UPlayerData player[], USimWorld &world)
{
    bool playersInReach[c_playerCount];
    int countPlayersInReach = 0;
    
    for (int i = 0; i < c_playerCount; i++)
    {
        if (OtherInReach(playerData, &(player[i]), player))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach[i] = false;
    }
    
    switch(playerData->aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(playerData, player, playersInReach, countPlayersInReach);
        case(AI::randomAI):
            return RandomAIChooseAction(playerData, player, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return HTNAIChooseAction(playerData, &world);
    }
	return RandomAIChooseAction(playerData, player, playersInReach, countPlayersInReach);
}

void AIController::CreateMissionOffer(UPlayerData player[], UPlayerData* playerData, bool playersInReach[], int countPlayersInReach)
{
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < c_playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
				playerData->playerTargetPtr = &(player[i]);
				playerData->missionOffer = CreateNewMission(playerData->playerTargetPtr);
                return;
            }
            target += 1;
        }
    }
}

UPlayerData* AIController::TargetForMakeFriend(UPlayerData* playerData, UPlayerData player[], bool playersInReach[], int countPlayersInReach)
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

Actions AIController::DoNothingAIChooseAction(UPlayerData* playerData, UPlayerData player[], bool playersInReach[], int countPlayersInReach)
{
    return Actions::noAction;
}

Actions AIController::RandomAIChooseAction(UPlayerData* playerData, UPlayerData player[], bool playersInReach[], int countPlayersInReach)
{
    if (countPlayersInReach > 0)
    {
        if (RandPercent() < playerData->pStats.aggression)
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
                        playerData->playerTargetPtr = &(player[i]);
                        return Actions::attack;
                    }
                    target += 1;
                }
            }
            std::cout << "ERROR: FAILED TO FIND ANY TARGET TO RANDOMLY ATTACK\n";
            playerData->playerTargetPtr = nullptr;
            return Actions::attack;
        } else if (RandPercent() < 25)
        {
            return Actions::evade;
        } else
        {
            return ChooseRoom(playerData, player);
        }
    } else if (RandPercent() < 80) {
        return Actions::useRoom;
    } else
    {
        return ChooseRoom(playerData, player);
    }
    return Actions::noAction;
}

Actions AIController::HTNAIChooseAction(UPlayerData* playerData, USimWorld* simWorld)
{
	pLog("Entering htnAIChooseAction", true);
	//update worldstate from real world
	HTNWorldState htnWorldState(playerData, *(simWorld));

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

    if (lastActionInterrupted || ((lastPrimitiveAction != nullptr) && !(lastPrimitiveAction->LastActionSucceeded(htnWorldState))))
	{
		pLog("Last Action did not succeed", true);
		hasValidPlan = false;
	} else if (htnPlan.size() > 0)
	{
		pLog("Check Precondition of plan primitive step", true);
		hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
	} else {
		pLog("No plan exists at all.", true);
	}

	//If plan is not valid, abandon it and try to make a new plan
	if (!hasValidPlan)
	{
		{std::stringstream ss;
		ss << playerData->m_playerName << ": Make a new plan:\n";
		pLog(ss, true);}
		HTNWorldState htnWorldStateDFSCopy(htnWorldState);
		HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);

		htnPlan = HTNdfs(htnWorldStateDFSCopy, *missionPtr, 0);
		{std::stringstream ss;
		for (auto &htnPrimitive : htnPlan)
		{
			ss << htnPrimitive->ToString() << ", ";
		}
		pLog(ss, true);}

		//once again, check if next step of the plan is valid.
		if (htnPlan.size() > 0)
		{
			hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
		}
	}

	if (!hasValidPlan)
	{
		std::stringstream ss;
		ss << playerData->m_playerName << ": Give up and return noAction\n";
		pLog(ss, true);
		return Actions::noAction; //If next step of the plan is still not valid, then return failure state
	} else {
		pLog("Valid plan found!", true);
		std::stringstream ss;
		ss << "Plan steps: ";
		for (auto &prim : playerData->aiController.htnPlan)
		{
			ss << prim->ToString() << ", ";
		}
		pLog(ss, true);
		HTNPrimitivePtr currentPlanStep = htnPlan.front();
		lastPrimitiveAction = currentPlanStep;
		htnPlan.pop_front();
		pLog("Leaving htnAIChooseAction #2", true);
		return currentPlanStep->Operate(playerData, *simWorld);
	}
	pLog("Leaving htnAIChooseAction #3", true);
	return Actions::noAction;
}

AIController::AIController(AI _algo):
	algo(_algo)
{
}

AIController::AIController() :
	algo(AI::randomAI)
{
}
