//
//  HTNDomain.hpp
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

class Study : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class Sleep : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class UseGym : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class RunCircuits : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class GoToGym : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class GoToLibrary : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class GoToCircuitTrack : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class GoToBedroom : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class GoToMainHall : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class Drink : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class Punch : public HTNPrimitive
{
public:
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[]);
    std::string ToString();
};

class IncreaseIntelligenceMethod1 : public HTNMethod
{
public:
    IncreaseIntelligenceMethod1();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class IncreaseIntelligenceMethod2 : public HTNMethod
{
public:
    IncreaseIntelligenceMethod2();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class IncreaseIntelligenceMethod3 : public HTNMethod
{
public:
    IncreaseIntelligenceMethod3();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
    IncreaseIntelligenceCompound();
};

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

class AttackMethod1 : public HTNMethod
{
public:
    AttackMethod1();
    bool Preconditions(HTNWorldState &htnWorldState);
};

class AttackCompound : public HTNCompound
{
public:
    AttackCompound();
};

#endif /* HTNDomain_hpp */