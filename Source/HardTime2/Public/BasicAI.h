#pragma once

#include "HTNPlanner.h"
#include "PlatformSpecific.h"

class USimWorld;

enum class AI
{
    doNothingAI, //does nothing
    htnAI //uses an HTN task planner
};

class AIController
{
    EActions ChooseRoom(UPlayerData* playerData, PlayerMap &playerMap);
    EActions DoNothingAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, std::vector<bool> playersInReach, int countPlayersInReach);
    //UPlayerData* TargetForMakeFriend(UPlayerData* playerData, PlayerMap &playerMap, bool playersInReach[], int countPlayersInReach);
public:
	EActions HTNAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld* simWorld);
    EActions ChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld &world);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
	AI algo;
	HTNPrimitivePtr lastPrimitiveAction = nullptr;
	bool lastActionInterrupted = false;
};
