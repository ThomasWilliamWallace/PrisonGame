#include "BasicAI.h"
#include "PlayerData.h"
#include <stdexcept>
#include "HTNDomain.h"
#include "RequestHTNDomain.h"
#include "SimWorld.h"
#include "AbstractAction.h"
#include <sstream>
#include "pLog.h"
#include "Constants.h"
#include <vector>
#include "TranslateToHTNWorldState.h"
#include "HTNPrimitives.h"
#include "HTNNode.h"
#include "EActions.h"
#include "PlatformSpecificForPlanner.h"

EActions AIController::ChooseRoom(UPlayerData* playerData, PlayerMap &playerMap)
{
    if (playerData->locationClass.location == ELocations::mainHall)
    {
        int random = RandPercent();
        if (random < 25)
        {
            return EActions::goToLibrary;
        }
        if (random < 50)
        {
            return EActions::goToGym;
        }
        if (random < 75)
        {
            return EActions::goToCircuitTrack;
        }
        return EActions::goToBedroom;
    } else
    {
        return EActions::goToMainHall;
    }
}

std::shared_ptr<BaseAction> AIController::ChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld &world)
{
	int tempPlayerCount = playerMap.Num();
    std::vector<bool> playersInReach(tempPlayerCount);
    int countPlayersInReach = 0;
    
	int i = 0;
	for (auto &playerIter : playerMap)
    {
		UPlayerData* currPlayerData = playerIter.Value;
        if (playerData->OtherInReach(*currPlayerData, playerMap))
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

std::shared_ptr<BaseAction> AIController::DoNothingAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, std::vector<bool> playersInReach, int countPlayersInReach)
{
	return std::make_shared<BaseAction>(EActions::noAction);
}

std::shared_ptr<BaseAction> AIController::HTNAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld* simWorld)
{
	pLog("Entering htnAIChooseAction");
	playerData->PrintPlayer();
	//update worldstate from real world
	std::unique_ptr<HTNWorldState> htnWorldState = TranslateToHTNWorldState(playerData, *simWorld, playerMap, nullptr);

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

    if (lastActionInterrupted || ((playerData->lastAction != nullptr) && !(playerData->lastAction->LastActionSucceeded(*htnWorldState))))
	{
		pLog("Last Action did not succeed", true);
		hasValidPlan = false;
	} else if (htnPlan.size() > 0)
	{
		pLog("Check Precondition of plan primitive step");
		hasValidPlan = htnPlan.front()->Preconditions(*htnWorldState);
	} else {
		pLog("No plan exists at all.");
	}

	//If plan is not valid, abandon it and try to make a new plan
	if (!hasValidPlan)
	{
		{std::stringstream ss;
		ss << ": Make a new plan:";
		pLog(ss, true);}

		HTNWorldState htnWorldStateDFSCopy(*htnWorldState);
		HTNCompound* missionPtr = new PrisonerBehaviourCompound();
		htnPlan = HTNIterative(htnWorldStateDFSCopy, *missionPtr, 0);

		//once again, check if next step of the plan is valid.
		if (htnPlan.size() > 0)
		{
			hasValidPlan = htnPlan.front()->Preconditions(*htnWorldState);
		}
	}

	if (!hasValidPlan)
	{
		std::stringstream ss;
		ss <<  ": Give up and return noAction";
		pLog(ss, true);
		return std::make_shared<BaseAction>(EActions::noAction); //If next step of the plan is still not valid, then return failure state
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
		htnPlan.pop_front();
		pLog("Leaving htnAIChooseAction #2");
		return TranslatePrimitiveToAction(currentPlanStep);
	}
	pLog("Leaving htnAIChooseAction #3");
	return std::make_shared<BaseAction>(EActions::noAction);
}

AIController::AIController(AI _algo):
	algo(_algo),
	lastActionInterrupted(false)
{
}

AIController::AIController() :
	algo(AI::doNothingAI),
	lastActionInterrupted(false)
{
}

std::shared_ptr<BaseAction> TranslatePrimitiveToAction(HTNPrimitivePtr htnPrimitivePtr)
{
	// Convert from planner action to an Unreal action.
	// This is to work around RTTI being disabled in Unreal Engine.
	EActions type = static_cast<EActions>(htnPrimitivePtr->m_type);
	if (type == EActions::noAction) {
		return std::make_shared<BaseAction>(EActions::noAction);
	}
	else if (type == EActions::study) {
		return std::make_shared<BaseAction>(EActions::study);
	}
	else if (type == EActions::sleep) {
		return std::make_shared<BaseAction>(EActions::sleep);
	}
	else if (type == EActions::workOut) {
		return std::make_shared<BaseAction>(EActions::workOut);
	}
	else if (type == EActions::runCircuits) {
		return std::make_shared<BaseAction>(EActions::runCircuits);
	}
	else if (type == EActions::goToGym) {
		return std::make_shared<BaseAction>(EActions::goToGym);
	}
	else if (type == EActions::goToLibrary) {
		return std::make_shared<BaseAction>(EActions::goToLibrary);
	}
	else if (type == EActions::goToCircuitTrack) {
		return std::make_shared<BaseAction>(EActions::goToCircuitTrack);
	}
	else if (type == EActions::goToBedroom) {
		return std::make_shared<BaseAction>(EActions::goToBedroom);
	}
	else if (type == EActions::goToMainHall) {
		return std::make_shared<BaseAction>(EActions::goToMainHall);
	}
	else if (type == EActions::drink) {
		return std::make_shared<BaseAction>(EActions::drink);
	}
	else if (type == EActions::attack) {
		PunchPrim* punchPrim = static_cast<PunchPrim*>(htnPrimitivePtr.get());
		return std::make_shared<AttackAction>(punchPrim->m_targetPlayer);
	}
	else if (type == EActions::evade) {
		EvadePrim* evadePrim = static_cast<EvadePrim*>(htnPrimitivePtr.get());
		return std::make_shared<EvadeAction>(evadePrim->m_evadePlayer);
	}
	else if (type == EActions::pickUpItemByPtr) {
		PickUpItemByPtrPrim* pickUpItemByPtrPrim = static_cast<PickUpItemByPtrPrim*>(htnPrimitivePtr.get());
		return std::make_shared<PickUpItemByPtrAction>(pickUpItemByPtrPrim->m_itemFocus->m_realItem);
	}
	else if (type == EActions::pickUpItemByType) {
		PickUpItemByTypePrim* pickUpItemByTypePrim = static_cast<PickUpItemByTypePrim*>(htnPrimitivePtr.get());
		return std::make_shared<PickUpItemByTypeAction>(pickUpItemByTypePrim->m_itemType);
	}
	else if (type == EActions::dropItem) {
		return std::make_shared<BaseAction>(EActions::dropItem);
	}
	else if (type == EActions::requestItem) {
		RequestItemPrim* requestItemPrim = static_cast<RequestItemPrim*>(htnPrimitivePtr.get());
		return std::make_shared<RequestItemAction>(requestItemPrim->m_requestedPlayer);
	}
	else {
		ThrowException("Primitive from htn_planner could not be converted to an Action.");
	}
	return std::make_shared<BaseAction>(EActions::noAction);
}
