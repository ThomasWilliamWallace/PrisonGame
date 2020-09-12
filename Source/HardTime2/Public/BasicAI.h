#pragma once

#include "HTNPlanner.h"
#include "EActions.h"
#include "PlatformSpecific.h"

class USimWorld;
class BaseAction;

enum class AI
{
    doNothingAI, //does nothing
    htnAI //uses an HTN task planner
};

class AIController
{
    EActions ChooseRoom(UPlayerData* playerData, PlayerMap &playerMap);
    std::shared_ptr<BaseAction> DoNothingAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, std::vector<bool> playersInReach, int countPlayersInReach);
    //UPlayerData* TargetForMakeFriend(UPlayerData* playerData, PlayerMap &playerMap, bool playersInReach[], int countPlayersInReach);
public:
    std::shared_ptr<BaseAction> HTNAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld* simWorld);
    std::shared_ptr<BaseAction> ChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld &world);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
	AI algo;
	HTNPrimitivePtr lastPrimitiveAction = nullptr;
	bool lastActionInterrupted = false;
};
