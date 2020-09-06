#include "RequestHTNDomain.h"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.h"
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
    for (auto &item : htnWorldState.m_itemsToKeep)
    {
        if (item == m_requestedItem)
        {
            return true;
        }
    }
    return false;
}

void NeedItemDeclineRequestMethod::CreateTasks()
{
    AddTask(new DeclineItemRequestPrim());
}

AcceptItemRequestMethod::AcceptItemRequestMethod(): HTNMethod("AcceptItemRequestMethod")
{
}

bool AcceptItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void AcceptItemRequestMethod::CreateTasks()
{
    AddTask(new AcceptItemRequestPrim());
}

DeclineItemRequestMethod::DeclineItemRequestMethod(): HTNMethod("DeclineItemRequestMethod")
{
}

bool DeclineItemRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void DeclineItemRequestMethod::CreateTasks()
{
    AddTask(new DeclineItemRequestPrim());
}

RespondToItemRequestCompound::RespondToItemRequestCompound(AActorItem* requestedItem) : HTNCompound("RespondToItemRequestCompound"), m_requestedItem(requestedItem)
{
}

void RespondToItemRequestCompound::CreateMethods()
{
    AddMethod(new NeedItemDeclineRequestMethod(m_requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(HTNWorldState &htnWorldState, PlayerMap &playerMap): HTNMethod("StartMethod"), m_htnWorldState(htnWorldState)
{
}

bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void StartMethod::CreateTasks()
{
    AActorItem* requestedItem = &(m_htnWorldState.m_itemCarriedPtr->m_realItem);
    AddTask(new PrisonerBehaviourCompound(m_htnWorldState));
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

StartCompound::StartCompound(HTNWorldState &htnWorldState, PlayerMap &playerMap): HTNCompound("StartCompound"), m_htnWorldState(htnWorldState), m_playerMap(playerMap)
{
}

void StartCompound::CreateMethods()
{
    AddMethod(new StartMethod(m_htnWorldState, m_playerMap));
}
*/
