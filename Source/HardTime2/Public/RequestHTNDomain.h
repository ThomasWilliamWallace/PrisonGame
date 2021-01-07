#pragma once

#include <vector>
#include <iostream>
#include "HTNPlanner.h"
#include "HTNWorldState.h"
#include "PlayerData.h"

class USimWorld;
/*
//***********************************************************
class AcceptItemRequestPrim : public HTNPrimitive
{
public:
    AcceptItemRequestPrim();
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerPtr, USimWorld &world) override;
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerPtr, USimWorld &world) override;
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(AActorItem* requestedItem);
    AActorItem* m_requestedItem;
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class RespondToItemRequestCompound : public HTNCompound
{
    AActorItem* m_requestedItem;
public:
    RespondToItemRequestCompound(AActorItem* requestedItem);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(AActorItem* requestedItem);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod(PlayerMap &playerMap);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class StartCompound : public HTNCompound
{
    PlayerMap m_playerMap;
public:
    StartCompound(PlayerMap &playerMap);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};
*/
