#pragma once

#include <vector>
#include <iostream>
#include "HTNPlanner.h"
#include "IHTNWorldState.h"
#include "PlayerData.h"

class UPlayerData;
class USimWorld;
/*
//***********************************************************
class AcceptItemRequestPrim : public HTNPrimitive
{
public:
    AcceptItemRequestPrim();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(AActorItem* requestedItem);
    AActorItem* m_requestedItem;
    bool Preconditions(IHTNWorldState &iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(IHTNWorldState &iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(IHTNWorldState &iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class RespondToItemRequestCompound : public HTNCompound
{
    AActorItem* m_requestedItem;
public:
    RespondToItemRequestCompound(AActorItem* requestedItem);
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(AActorItem* requestedItem);
    bool Preconditions(IHTNWorldState &iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod(PlayerMap &playerMap);
    bool Preconditions(IHTNWorldState &iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class StartCompound : public HTNCompound
{
    PlayerMap m_playerMap;
public:
    StartCompound(PlayerMap &playerMap);
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};
*/
