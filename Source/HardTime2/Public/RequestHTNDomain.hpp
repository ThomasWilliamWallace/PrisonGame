#pragma once

#include <vector>
#include <iostream>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"
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
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
};

class RespondToItemRequestCompound : public HTNCompound
{
public:
    RespondToItemRequestCompound(AActorItem* requestedItem);
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(AActorItem* requestedItem);
    bool Preconditions(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod(HTNWorldState &htnWorldState, UPlayerData player[]);
    bool Preconditions(HTNWorldState &htnWorldState) override;
};

class StartCompound : public HTNCompound
{
public:
    StartCompound(HTNWorldState &htnWorldState, UPlayerData player[]);
};
*/
