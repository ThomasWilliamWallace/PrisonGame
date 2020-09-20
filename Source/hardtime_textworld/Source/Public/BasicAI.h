#pragma once

#include "HTNPlanner.h"
#include "EActions.h"
#include "PlatformSpecific.h"

class USimWorld;
class BaseAction;

enum class AI
{
    doNothingAI, //does nothing
    htnAI, //uses an HTN task planner
    humanAI, // human controlled
    aggroAI,
    randomAI
};

class AIController
{
    AI algo;
    HTNPrimitiveList htnPlan;
    EActions ChooseRoom(AbstractPlayerData& player);
    std::shared_ptr<BaseAction> DoNothingAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    std::shared_ptr<BaseAction> RandomAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    std::shared_ptr<BaseAction> aggroAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    std::shared_ptr<BaseAction> humanAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    std::shared_ptr<BaseAction> htnAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    void CreateMissionOffer(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
    int TargetForMakeFriend(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach);
public:
    std::shared_ptr<BaseAction> ChooseAction(UPlayerData& player, USimWorld& world);
    AIController(AI _algo);
    AIController();
    bool lastActionSucceeded;
    bool RespondToOffer(UPlayerData& player, USimWorld& world, int requesterIndex);
};
