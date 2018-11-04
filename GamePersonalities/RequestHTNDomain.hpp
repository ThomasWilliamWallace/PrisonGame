//
//  RequestHTNDomain.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef HTNDomain_hpp
#define HTNDomain_hpp
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
class GoToLibraryMethod1 : public HTNMethod
{
public:
    GoToLibraryMethod1();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class GoToLibraryMethod2 : public HTNMethod
{
public:
    GoToLibraryMethod2();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class GoToLibraryCompound : public HTNCompound
{
public:
    GoToLibraryCompound();
};

//***********************************************************
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
    RespondToItemRequestCompound();
};

class RespondToItemRequestMethod : public HTNMethod
{
public:
    RespondToItemRequestMethod();
    bool Preconditions(HTNWorldState &htnWorldState);
};

//***********************************************************
//class StartMethod : public HTNMethod
//{
//public:
//    StartMethod();
//    bool Preconditions(HTNWorldState &htnWorldState);
//};
//
//class StartCompound : public HTNCompound
//{
//public:
//    StartCompound(HTNWorldState &htnWorldState, Player player[]);
//};

#endif /* RequestHTNDomain_hpp */