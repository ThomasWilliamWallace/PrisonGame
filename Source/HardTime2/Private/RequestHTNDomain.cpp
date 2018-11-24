#include "RequestHTNDomain.hpp"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.hpp"
/*
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

Actions AcceptItemRequestPrim::Operate(UPlayerData* playerPtr, UPlayerData player[], USimWorld &world)
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

Actions DeclineItemRequestPrim::Operate(UPlayerData* playerPtr, UPlayerData player[], USimWorld &world)
{
    return Actions::declineRequest;
}

bool DeclineItemRequestPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(AActorItem* requestedItem) : m_requestedItem(requestedItem)
{
    AddTask(new DeclineItemRequestPrim());
}

bool NeedItemDeclineRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    SimActorItem* simItem = dynamic_cast<SimActorItem*>(m_requestedItem);
    for (auto &item : htnWorldState.m_itemsToKeep)
    {
        if (item == &(simItem->m_realItem))
        {
            return true;
        }
    }
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

RespondToItemRequestCompound::RespondToItemRequestCompound(AActorItem* requestedItem) : HTNCompound("RespondToItemRequestCompound")
{
    AddMethod(new NeedItemDeclineRequestMethod(requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(HTNWorldState &htnWorldState, UPlayerData player[])
{
    AActorItem* requestedItem = htnWorldState.m_itemCarriedPtr;
    AddTask(new PrisonerBehaviourCompound(htnWorldState));
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

StartCompound::StartCompound(HTNWorldState &htnWorldState, UPlayerData player[]) : HTNCompound("StartCompound")
{
    AddMethod(new StartMethod(htnWorldState, player));
}
*/