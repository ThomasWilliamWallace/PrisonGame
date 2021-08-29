#include "RequestHTNDomain.h"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.h"
#include "HTNWorldState.h"
/*
//Start HTNPrimitives****************************************
AcceptItemRequestPrim::AcceptItemRequestPrim() : HTNPrimitive("AcceptItemRequest") {}

void AcceptItemRequestPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState &>(iHTNWorldState);
    for (auto &simItem : state.m_items)
    {
        if (simItem == state.m_itemCarriedPtr)
        {
            simItem->m_carryingPlayer = state.m_requester;
        }
    }
    state.m_itemCarriedPtr = nullptr;
    return;
}

std::shared_ptr<BaseAction> AcceptItemRequestPrim::Operate(UPlayerData* playerPtr, USimWorld &world)
{
    return std::make_shared<BaseAction>(EActions::acceptRequest);
}

bool AcceptItemRequestPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

//***********************************************************
DeclineItemRequestPrim::DeclineItemRequestPrim() : HTNPrimitive("DeclineItemRequest") {}

void DeclineItemRequestPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    return;
}

std::shared_ptr<BaseAction> DeclineItemRequestPrim::Operate(UPlayerData* playerPtr, USimWorld &world)
{
    return std::make_shared<BaseAction>(EActions::declineRequest);
}

bool DeclineItemRequestPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(AActorItem* requestedItem): HTNMethod("NeedItemDeclineRequestMethod"), m_requestedItem(requestedItem)
{
}

bool NeedItemDeclineRequestMethod::Preconditions(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState &>(iHTNWorldState);
    for (auto &item : state.m_itemsToKeep)
    {
        if (item == m_requestedItem)
        {
            return true;
        }
    }
    return false;
}

void NeedItemDeclineRequestMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new DeclineItemRequestPrim());
}

AcceptItemRequestMethod::AcceptItemRequestMethod(): HTNMethod("AcceptItemRequestMethod")
{
}

bool AcceptItemRequestMethod::Preconditions(IHTNWorldState &iHTNWorldState)
{
    return true;
}

void AcceptItemRequestMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new AcceptItemRequestPrim());
}

DeclineItemRequestMethod::DeclineItemRequestMethod(): HTNMethod("DeclineItemRequestMethod")
{
}

bool DeclineItemRequestMethod::Preconditions(IHTNWorldState &iHTNWorldState)
{
    return true;
}

void DeclineItemRequestMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new DeclineItemRequestPrim());
}

RespondToItemRequestCompound::RespondToItemRequestCompound(AActorItem* requestedItem) : HTNCompound("RespondToItemRequestCompound"), m_requestedItem(requestedItem)
{
}

void RespondToItemRequestCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new NeedItemDeclineRequestMethod(m_requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(PlayerMap &playerMap): HTNMethod("StartMethod")
{
}

bool StartMethod::Preconditions(IHTNWorldState &iHTNWorldState)
{
    return true;
}

void StartMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState &>(iHTNWorldState);
    AActorItem* requestedItem = &(state.m_itemCarriedPtr->m_realItem);
    AddTask(new PrisonerBehaviourCompound());
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

StartCompound::StartCompound(PlayerMap &playerMap): HTNCompound("StartCompound"), m_playerMap(playerMap)
{
}

void StartCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new StartMethod(m_playerMap));
}
*/
