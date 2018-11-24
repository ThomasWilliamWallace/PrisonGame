#pragma once

#include "HTNPlanner.hpp"

class USimWorld;

enum class AI
{
    doNothingAI, //does nothing
    randomAI, //basic set of random actions.
    htnAI //uses an HTN to search with utility
};

class AIController
{
    AI algo;
    Actions ChooseRoom(UPlayerData* playerPtr, UPlayerData player[]);
    Actions DoNothingAIChooseAction(UPlayerData* playerPtr, UPlayerData player[], bool playersInReach[], int countPlayersInReach);
    Actions RandomAIChooseAction(UPlayerData* playerPtr, UPlayerData player[], bool playersInReach[], int countPlayersInReach);
    void CreateMissionOffer(UPlayerData player[], UPlayerData* playerPtr, bool playersInReach[], int countPlayersInReach);
    UPlayerData* TargetForMakeFriend(UPlayerData player[], UPlayerData* playerPtr, bool playersInReach[], int countPlayersInReach);
public:
	Actions HTNAIChooseAction(AAICharacterC* aiCharacterC);
    Actions ChooseAction(UPlayerData* playerPtr, UPlayerData player[], USimWorld &world, AAICharacterC* aiCharacterC);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
};