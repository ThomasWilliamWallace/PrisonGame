//
//  RequestHTNDomain.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef RequestHTNDomain_hpp
#define RequestHTNDomain_hpp
#include <vector>
#include <iostream>
#include "HTN.hpp"
#include "HTNWorldState.hpp"
#include "Player.hpp"

class World;

//***********************************************************
class AcceptItemRequestPrim : public HTNPrimitive
{
public:
    AcceptItemRequestPrim();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class DeclineItemRequestPrim : public HTNPrimitive
{
public:
    DeclineItemRequestPrim();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class NeedItemDeclineRequestMethod : public HTNMethod
{
public:
    NeedItemDeclineRequestMethod(Item* requestedItem);
    Item* m_requestedItem;
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
    RespondToItemRequestCompound(Item* requestedItem);
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod(Item* requestedItem);
    bool Preconditions(HTNWorldState &htnWorldState);
};

//***********************************************************
class StartMethod : public HTNMethod
{
public:
    StartMethod(HTNWorldState &htnWorldState, Player player[]);
    bool Preconditions(HTNWorldState &htnWorldState);
};

class StartCompound : public HTNCompound
{
public:
    StartCompound(HTNWorldState &htnWorldState, Player player[]);
};

#endif /* RequestHTNDomain_hpp */