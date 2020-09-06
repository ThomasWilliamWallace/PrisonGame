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
    bool Preconditions(HTNWorldState &htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerPtr, USimWorld &world) override;
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerPtr, USimWorld &world) override;
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(AActorItem* requestedItem);
    AActorItem* m_requestedItem;
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class RespondToItemRequestCompound : public HTNCompound
{
    AActorItem* m_requestedItem;
public:
    RespondToItemRequestCompound(AActorItem* requestedItem);
    virtual void CreateMethods() override;
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(AActorItem* requestedItem);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
public:
    StartMethod(HTNWorldState &htnWorldState, PlayerMap &playerMap);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class StartCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    PlayerMap m_playerMap;
public:
    StartCompound(HTNWorldState &htnWorldState, PlayerMap &playerMap);
    virtual void CreateMethods() override;
};
*/
