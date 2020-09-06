#include "BasicAI.h"
#include "PlayerData.h"
#include <stdexcept>
#include "HTNDomain.h"
#include "RequestHTNDomain.h"
#include "SimWorld.h"
#include "Actions.h"
#include <sstream>
#include "pLog.h"
#include <vector>

Actions AIController::ChooseRoom(UPlayerData* playerData, PlayerMap &playerMap)
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

Actions AIController::ChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld &world)
{
	int tempPlayerCount = playerMap.Num();
    std::vector<bool> playersInReach(tempPlayerCount);
    int countPlayersInReach = 0;
    
	int i = 0;
	for (auto &playerIter : playerMap)
    {
		UPlayerData* currPlayerData = playerIter.Value;
        if (OtherInReach(playerData, currPlayerData, playerMap))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach.at(i) = false;
		i += 1;
    }
    
    switch(playerData->aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(playerData, playerMap, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return HTNAIChooseAction(playerData, playerMap, &world);
		default:
			throw std::invalid_argument("Selected an invalid AI controller type.");
    }
}

/*
UPlayerData* AIController::TargetForMakeFriend(UPlayerData* playerData, PlayerMap &playerMap, bool playersInReach[], int countPlayersInReach)
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

Actions AIController::DoNothingAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, std::vector<bool> playersInReach, int countPlayersInReach)
{
    return Actions::noAction;
}

Actions AIController::HTNAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld* simWorld)
{
	pLog("Entering htnAIChooseAction");
	//update worldstate from real world
	HTNWorldState htnWorldState(playerData, playerMap, *(simWorld));

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

    if (lastActionInterrupted || ((lastPrimitiveAction != nullptr) && !(lastPrimitiveAction->LastActionSucceeded(htnWorldState))))
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
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, ss.str().c_str());
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
