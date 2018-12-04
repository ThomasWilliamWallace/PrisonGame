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

Actions AcceptItemRequestPrim::Operate(UPlayerData* playerPtr, USimWorld &world)
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

Actions DeclineItemRequestPrim::Operate(UPlayerData* playerPtr, USimWorld &world)
{
    return Actions::declineRequest;
}

bool DeclineItemRequestPrim::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(AActorItem* requestedItem): HTNMethod("NeedItemDeclineRequestMethod"), m_requestedItem(requestedItem)
{
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

HTNNodeList& NeedItemDeclineRequestMethod::GetTasks()
{
    AddTask(new DeclineItemRequestPrim());
    return m_nodeList;
}

AcceptItemRequestMethod::AcceptItemRequestMethod(): HTNMethod("AcceptItemRequestMethod")
{
}

bool AcceptItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& AcceptItemRequestMethod::GetTasks()
{
    AddTask(new AcceptItemRequestPrim());
    return m_nodeList;
}

DeclineItemRequestMethod::DeclineItemRequestMethod(): HTNMethod("DeclineItemRequestMethod")
{
}

bool DeclineItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& DeclineItemRequestMethod::GetTasks()
{
    AddTask(new DeclineItemRequestPrim());
    return m_nodeList;
}

RespondToItemRequestCompound::RespondToItemRequestCompound(AActorItem* requestedItem) : HTNCompound("RespondToItemRequestCompound"), m_requestedItem(requestedItem)
{
}

HTNMethodList& RespondToItemRequestCompound::GetMethods()
{
    AddMethod(new NeedItemDeclineRequestMethod(m_requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
    return m_methods;
}

//***********************************************************
StartMethod::StartMethod(HTNWorldState &htnWorldState, UPlayerData player[]): HTNMethod("StartMethod"), m_htnWorldState(htnWorldState)
{
}

bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

HTNNodeList& StartMethod::GetTasks()
{
    AActorItem* requestedItem = m_htnWorldState.m_itemCarriedPtr;
    AddTask(new PrisonerBehaviourCompound(m_htnWorldState));
    AddTask(new RespondToItemRequestCompound(requestedItem));
    return m_nodeList;
}

StartCompound::StartCompound(HTNWorldState &htnWorldState, UPlayerData player[]): HTNCompound("StartCompound"), m_htnWorldState(htnWorldState), m_player(player)
{
}

HTNMethodList& StartCompound::GetMethods()
{
    AddMethod(new StartMethod(m_htnWorldState, m_player));
    return m_methods;
}
*/
