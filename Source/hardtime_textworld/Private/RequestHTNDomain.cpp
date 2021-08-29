#include "RequestHTNDomain.h"
#include "Locations.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.h"

//Start HTNPrimitives****************************************
AcceptItemRequestPrim::AcceptItemRequestPrim() : HTNPrimitive("AcceptItemRequest") {}

void AcceptItemRequestPrim::Effect(IHTNWorldState &iHTNWorldState)
{
    HTNWorldState& state = static_cast<HTNWorldState&>(iHTNWorldState);
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

std::shared_ptr<BaseAction> AcceptItemRequestPrim::Operate(UPlayerData* playerData)
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

std::shared_ptr<BaseAction> DeclineItemRequestPrim::Operate(UPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::declineRequest);
}

bool DeclineItemRequestPrim::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(std::shared_ptr<AbstractItem> requestedItem): HTNMethod("NeedItemDeclineRequestMethod"), m_requestedItem(requestedItem)
{
}

bool NeedItemDeclineRequestMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    for (auto &item : state.m_itemsToKeep)
    {
        if (item->m_realItem == m_requestedItem.get())
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

bool AcceptItemRequestMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
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

bool DeclineItemRequestMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

void DeclineItemRequestMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    AddTask(new DeclineItemRequestPrim());
}

RespondToItemRequestCompound::RespondToItemRequestCompound(std::shared_ptr<AbstractItem> requestedItem) : HTNCompound("RespondToItemRequestCompound"), m_requestedItem(requestedItem)
{
}

void RespondToItemRequestCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new NeedItemDeclineRequestMethod(m_requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(): HTNMethod("StartMethod")
{
}

bool StartMethod::Preconditions(IHTNWorldState const& iHTNWorldState)
{
    return true;
}

void StartMethod::CreateTasks(IHTNWorldState const& iHTNWorldState)
{
    HTNWorldState const& state = static_cast<HTNWorldState const&>(iHTNWorldState);
    std::shared_ptr<AbstractItem> requestedItem = state.m_itemCarriedPtr;
    AddTask(new PrisonerBehaviourCompound());
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

StartCompound::StartCompound(): HTNCompound("StartCompound")
{
}

void StartCompound::CreateMethods(IHTNWorldState const& iHTNWorldState)
{
    AddMethod(new StartMethod());
}