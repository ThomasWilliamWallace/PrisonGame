#include "BasicAI.hpp"
#include "PlayerData.h"
#include <stdexcept>
#include "HTNDomain.hpp"
#include "RequestHTNDomain.hpp"
#include "SimWorld.h"
#include "Actions.hpp"
#include <sstream>
#include "pLog.hpp"
#include <vector>

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
	int currentPlayerCount = static_cast<int>(world.m_players.size());
    std::vector<bool> playersInReach(currentPlayerCount);
    int countPlayersInReach = 0;
    
    for (int i = 0; i < currentPlayerCount; i++)
    {
        if (OtherInReach(playerData, &(player[i]), player))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach.at(i) = false;
    }
    
    switch(playerData->aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(playerData, player, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return HTNAIChooseAction(playerData, &world);
		default:
			throw std::invalid_argument("Selected an invalid AI controller type.");
    }
}

/*
UPlayerData* AIController::TargetForMakeFriend(UPlayerData* playerData, UPlayerData player[], bool playersInReach[], int countPlayersInReach)
{
	int currentPlayerCount = static_cast<int>(world.m_players.size());
    double random = RandPercent();
    int target = 0;
    for (int i=0; i < currentPlayerCount; i++)
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
*/

Actions AIController::DoNothingAIChooseAction(UPlayerData* playerData, UPlayerData player[], std::vector<bool> playersInReach, int countPlayersInReach)
{
    return Actions::noAction;
}

Actions AIController::HTNAIChooseAction(UPlayerData* playerData, USimWorld* simWorld)
{
	pLog("Entering htnAIChooseAction");
	//update worldstate from real world
	HTNWorldState htnWorldState(playerData, *(simWorld));

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

    if (lastActionInterrupted || ((lastPrimitiveAction.IsValid()) && !(lastPrimitiveAction->LastActionSucceeded(htnWorldState))))
	{
		pLog("Last Action did not succeed", true);
		hasValidPlan = false;
	} else if (htnPlan.size() > 0)
	{
		pLog("Check Precondition of plan primitive step");
		hasValidPlan = htnPlan.front()->Preconditions(htnWorldState);
	} else {
		pLog("No plan exists at all.");
	}

	//If plan is not valid, abandon it and try to make a new plan
	if (!hasValidPlan)
	{
		{std::stringstream ss;
		ss << ": Make a new plan:";
		pLog(ss, true);}

		HTNWorldState htnWorldStateDFSCopy(htnWorldState);
		HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);
		htnPlan = HTNIterative(htnWorldStateDFSCopy, *missionPtr, 0);

		//once again, check if next step of the plan is valid.
		if (htnPlan.size() > 0)
		{
			hasValidPlan = htnPlan.front()->Preconditions(htnWorldState);
		}
	}

	if (!hasValidPlan)
	{
		std::stringstream ss;
		ss <<  ": Give up and return noAction";
		pLog(ss, true);
		return Actions::noAction; //If next step of the plan is still not valid, then return failure state
	} else {
		pLog("Valid plan found!");
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
		pLog("Leaving htnAIChooseAction #2");
		return currentPlanStep->Operate(playerData, *simWorld);
	}
	pLog("Leaving htnAIChooseAction #3");
	return Actions::noAction;
}

AIController::AIController(AI _algo):
	algo(_algo)
{
}

AIController::AIController() :
	algo(AI::doNothingAI)
{
}
