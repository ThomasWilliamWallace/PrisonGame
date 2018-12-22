#pragma once

#include "HTNPlanner.hpp"

class USimWorld;

enum class AI
{
    doNothingAI, //does nothing
    htnAI //uses an HTN to search with utility
};

class AIController
{
    Actions ChooseRoom(UPlayerData* playerData, UPlayerData player[]);
    Actions DoNothingAIChooseAction(UPlayerData* playerData, UPlayerData player[], std::vector<bool> playersInReach, int countPlayersInReach);
    //UPlayerData* TargetForMakeFriend(UPlayerData* playerData, UPlayerData player[], bool playersInReach[], int countPlayersInReach);
public:
	Actions HTNAIChooseAction(UPlayerData* playerData, USimWorld* simWorld);
    Actions ChooseAction(UPlayerData* playerData, UPlayerData player[], USimWorld &world);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
	AI algo;
	HTNPrimitivePtr lastPrimitiveAction = nullptr;
	bool lastActionInterrupted = false;
};
