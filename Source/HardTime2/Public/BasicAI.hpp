#pragma once

#include "HTNPlanner.hpp"

class World;

enum class AI
{
    doNothingAI, //does nothing
    randomAI, //basic set of random actions.
    htnAI //uses an HTN to search with utility
};

class AIController
{
    AI algo;
    Actions ChooseRoom(Player* playerPtr, Player player[]);
    Actions DoNothingAIChooseAction(Player* playerPtr, Player player[], bool playersInReach[], int countPlayersInReach);
    Actions RandomAIChooseAction(Player* playerPtr, Player player[], bool playersInReach[], int countPlayersInReach);
    void CreateMissionOffer(Player player[], Player* playerPtr, bool playersInReach[], int countPlayersInReach);
    Player* TargetForMakeFriend(Player player[], Player* playerPtr, bool playersInReach[], int countPlayersInReach);
public:
	Actions HTNAIChooseAction(AAICharacterC* aiCharacterC);
    Actions ChooseAction(Player* playerPtr, Player player[], World &world, AAICharacterC* aiCharacterC);
    AIController(AI _algo);
    AIController();
	HTNPrimitiveList htnPlan;
};