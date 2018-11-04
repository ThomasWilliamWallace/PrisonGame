//
//  RequestHTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "RequestHTNDomain.hpp"
#include "Locations.hpp"
#include "Player.hpp"
#include "World.hpp"

//Start HTNPrimitives****************************************
AcceptItemRequestPrim::AcceptItemRequestPrim() : HTNPrimitive("AcceptItemRequest") {}

void AcceptItemRequestPrim::Effect(HTNWorldState &htnWorldState)
{
    for (auto &simItem : htnWorldState.m_items)
    {
        if (simItem == htnWorldState.m_itemCarriedPtr)
        {
            simItem->m_carryingPlayer = nullptr; //TODO REQUESTING_PLAYER;
        }
    }
    htnWorldState.m_itemCarriedPtr = nullptr;
    return;
}

Actions AcceptItemRequestPrim::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::acceptRequest;
}

bool AcceptItemRequestPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
DeclineItemRequestPrim::DeclineItemRequestPrim() : HTNPrimitive("DeclineItemRequest") {}

void DeclineItemRequestPrim::Effect(HTNWorldState &htnWorldState)
{
    return;
}

Actions DeclineItemRequestPrim::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::declineRequest;
}

bool DeclineItemRequestPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
AcceptItemRequestMethod::AcceptItemRequestMethod()
{
    AddTask(new AcceptItemRequestPrim());
}

bool AcceptItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

DeclineItemRequestMethod::DeclineItemRequestMethod()
{
    AddTask(new DeclineItemRequestPrim());
}

bool DeclineItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

RespondToItemRequestCompound::RespondToItemRequestCompound() : HTNCompound("RespondToItemRequestCompound")
{
    m_methods.push_back(HTNMethodPtr(new AcceptItemRequestMethod()));
    m_methods.push_back(HTNMethodPtr(new DeclineItemRequestMethod()));
}

//***********************************************************
//StartMethod::StartMethod()
//{
//    AddTask(new RespondToItemRequestCompound());
//    AddTask(new PrisonerBehaviourCompound());
//}
//
//bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
//{
//    return true;
//}
//
//StartCompound::StartCompound(HTNWorldState &htnWorldState, Player player[]) : HTNCompound("StartCompound")
//{
//    m_methods.push_back(HTNMethodPtr(new StartMethod()));
//}