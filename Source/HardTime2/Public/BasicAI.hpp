#pragma once

#include "HTNPlanner.hpp"
#include "PlayerMapFwd.hpp"  //TODO rename to just PlayerMap

class USimWorld;

enum class AI
{
    doNothingAI, //does nothing
    htnAI //uses an HTN task planner
};

class AIController
{
    Actions ChooseRoom(UPlayerData* playerData, PlayerMap &playerMap);
    Actions DoNothingAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, std::vector<bool> playersInReach, int countPlayersInReach);
    //UPlayerData* TargetForMakeFriend(UPlayerData* playerData, PlayerMap &playerMap, bool playersInReach[], int countPlayersInReach);
public:
	Actions HTNAIChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld* simWorld);
    Actions ChooseAction(UPlayerData* playerData, PlayerMap &playerMap, USimWorld &world);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
	AI algo;
	HTNPrimitivePtr lastPrimitiveAction = nullptr;
	bool lastActionInterrupted = false;
};
