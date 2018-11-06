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
#include "HTNDomain.hpp"

//Start HTNPrimitives****************************************
AcceptItemRequestPrim::AcceptItemRequestPrim() : HTNPrimitive("AcceptItemRequest") {}

void AcceptItemRequestPrim::Effect(HTNWorldState &htnWorldState)
{
    for (auto &simItem : htnWorldState.m_items)
    {
        if (simItem == htnWorldState.m_itemCarriedPtr)
        {
            simItem->m_carryingPlayer = htnWorldState.m_requester;
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
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(Item* requestedItem) : m_requestedItem(requestedItem)
{
    AddTask(new DeclineItemRequestPrim());
}

bool NeedItemDeclineRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
//    std::cout << "ENTERING NEEDITEMDECLINEREQUESTMETHOD: m_requestedItem = " << m_requestedItem << "\n";
//    if (m_requestedItem == nullptr)
//    {
//        std::cout << "ERROR: NeedItemDeclineRequestMethod called when m_requestedItem == nullptr.\n";
//        return false;
//    }
    SimItem* simItem = dynamic_cast<SimItem*>(m_requestedItem);
//    if (simItem == nullptr)
//    {
//        std::cout << "ERROR cast to m_requestedItem to SimItem failed.\n";
//        exit(0);
//    }
    for (auto &item : htnWorldState.m_itemsToKeep)
    {
//    std::cout << "item=" << item << "\n";
        if (item == &(simItem->m_realItem))
        {
//    std::cout << "RETURN TRUE\n";
            return true;
        }
    }
//    std::cout << "RETURN FALSE\n";
    return false;
}

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

RespondToItemRequestCompound::RespondToItemRequestCompound(Item* requestedItem) : HTNCompound("RespondToItemRequestCompound")
{
    AddMethod(new NeedItemDeclineRequestMethod(requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(HTNWorldState &htnWorldState, Player player[])
{
    Item* requestedItem = htnWorldState.m_itemCarriedPtr;
    AddTask(new PrisonerBehaviourCompound(htnWorldState, player));
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

StartCompound::StartCompound(HTNWorldState &htnWorldState, Player player[]) : HTNCompound("StartCompound")
{
    AddMethod(new StartMethod(htnWorldState, player));
}