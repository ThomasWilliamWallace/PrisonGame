//
//  HTNPrimitives.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef HTNPrimitives_hpp
#define HTNPrimitives_hpp
#include <vector>
#include <iostream>
#include "HTN.hpp"
#include "HTNWorldState.hpp"
#include "Player.hpp"

class Item;
class World;

//***********************************************************
class Study : public HTNPrimitive
{
public:
    Study();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class Sleep : public HTNPrimitive
{
public:
    Sleep();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class UseGym : public HTNPrimitive
{
public:
    UseGym();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class RunCircuits : public HTNPrimitive
{
public:
    RunCircuits();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class GoToGym : public HTNPrimitive
{
public:
    GoToGym();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class GoToLibrary : public HTNPrimitive
{
public:
    GoToLibrary();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class GoToCircuitTrack : public HTNPrimitive
{
public:
    GoToCircuitTrack();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class GoToBedroom : public HTNPrimitive
{
public:
    GoToBedroom();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class GoToMainHall : public HTNPrimitive
{
public:
    GoToMainHall();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class Drink : public HTNPrimitive
{
public:
    Drink();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class Punch : public HTNPrimitive
{
    int m_targetPlayerIndex;
public:
    Punch(int playerIndex);
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class Evade : public HTNPrimitive
{
public:
    Evade();
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class PickUpItem : public HTNPrimitive
{
public:
    PickUpItem(Item* itemFocusPtr);
    Item* m_itemFocusPtr;
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
    void PointToRealItems(HTNWorldState &htnWorldState);
};

//***********************************************************
class PickUpItem2 : public HTNPrimitive
{
public:
    PickUpItem2(ItemType itemType);
    ItemType m_itemType;
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

//***********************************************************
class DropItem : public HTNPrimitive
{
public:
    DropItem(bool keepItem);
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
    bool m_keepItem;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
    int m_playerIndex;
    Player* m_player;
    ItemType m_itemType;
public:
    RequestItemPrim(int playerIndex, Player* player, ItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operator(int playerIndex, Player player[], World &world);
};

#endif /* HTNPrimitives_hpp */