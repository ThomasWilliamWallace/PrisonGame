#pragma once

#include <vector>
#include <iostream>
#include "HTNPlanner.h"
#include "IHTNWorldState.h"
#include "Item.h"

class UPlayerData;
class USimWorld;

//***********************************************************
class AcceptItemRequestPrim : public HTNPrimitive
{
public:
    AcceptItemRequestPrim();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(std::shared_ptr<AbstractItem> requestedItem);
    std::shared_ptr<AbstractItem> m_requestedItem;
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class RespondToItemRequestCompound : public HTNCompound
{
    std::shared_ptr<AbstractItem> m_requestedItem;
public:
    RespondToItemRequestCompound(std::shared_ptr<AbstractItem> requestedItem);
    virtual void CreateMethods(IHTNWorldState const& IHTNWorldState) override;
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(Item* requestedItem);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class StartCompound : public HTNCompound
{
public:
    StartCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};