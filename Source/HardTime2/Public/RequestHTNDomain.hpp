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
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operate(UPlayerData* playerPtr, UPlayerData player[], USimWorld &world);
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operate(UPlayerData* playerPtr, UPlayerData player[], USimWorld &world);
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(AActorItem* requestedItem);
    AActorItem* m_requestedItem;
    bool Preconditions(HTNWorldState &htnWorldState);
};

class AcceptItemRequestMethod : public HTNMethod
{
public:
    AcceptItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class DeclineItemRequestMethod : public HTNMethod
{
public:
    DeclineItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState);
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
    bool Preconditions(HTNWorldState &htnWorldState);
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod(HTNWorldState &htnWorldState, UPlayerData player[]);
    bool Preconditions(HTNWorldState &htnWorldState);
};

class StartCompound : public HTNCompound
{
public:
    StartCompound(HTNWorldState &htnWorldState, UPlayerData player[]);
};
*/