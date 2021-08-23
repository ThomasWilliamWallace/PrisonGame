#pragma once

#include <vector>
#include <iostream>
#include "HTNPlanner.h"
#include "HTNWorldState.h"
#include "Item.h"

class UPlayerData;
class USimWorld;

//***********************************************************
class AcceptItemRequestPrim : public HTNPrimitive
{
public:
    AcceptItemRequestPrim();
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(std::shared_ptr<AbstractItem> requestedItem);
    std::shared_ptr<AbstractItem> m_requestedItem;
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
    std::shared_ptr<AbstractItem> m_requestedItem;
public:
    RespondToItemRequestCompound(std::shared_ptr<AbstractItem> requestedItem);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(Item* requestedItem);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class StartCompound : public HTNCompound
{
public:
    StartCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};