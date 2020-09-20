#include "RequestHTNDomain.h"
#include "Locations.h"
#include "AbstractPlayerData.h"
#include "SimWorld.h"
#include "HTNDomain.h"

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

std::shared_ptr<BaseAction> AcceptItemRequestPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::acceptRequest);
}

bool AcceptItemRequestPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return true;
}

//***********************************************************
DeclineItemRequestPrim::DeclineItemRequestPrim() : HTNPrimitive("DeclineItemRequest") {}

void DeclineItemRequestPrim::Effect(HTNWorldState &htnWorldState)
{
    return;
}

std::shared_ptr<BaseAction> DeclineItemRequestPrim::Operate(AbstractPlayerData* playerData)
{
    return std::make_shared<BaseAction>(EActions::declineRequest);
}

bool DeclineItemRequestPrim::Preconditions(HTNWorldState const& htnWorldState)
{
    return true;
}

//Start HTNCompounds*****************************************
 NeedItemDeclineRequestMethod::NeedItemDeclineRequestMethod(std::shared_ptr<AbstractItem> requestedItem): HTNMethod("NeedItemDeclineRequestMethod"), m_requestedItem(requestedItem)
{
}

bool NeedItemDeclineRequestMethod::Preconditions(HTNWorldState &htnWorldState)
{
    for (auto &item : htnWorldState.m_itemsToKeep)
    {
        if (item->m_realItem == m_requestedItem.get())
        {
            return true;
        }
    }
    return false;
}

void NeedItemDeclineRequestMethod::CreateTasks(HTNWorldState const& htnWorldState)
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

void AcceptItemRequestMethod::CreateTasks(HTNWorldState const& htnWorldState)
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

void DeclineItemRequestMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    AddTask(new DeclineItemRequestPrim());
}

RespondToItemRequestCompound::RespondToItemRequestCompound(std::shared_ptr<AbstractItem> requestedItem) : HTNCompound("RespondToItemRequestCompound"), m_requestedItem(requestedItem)
{
}

void RespondToItemRequestCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    AddMethod(new NeedItemDeclineRequestMethod(m_requestedItem));
    AddMethod(new AcceptItemRequestMethod());
    AddMethod(new DeclineItemRequestMethod());
}

//***********************************************************
StartMethod::StartMethod(HTNWorldState &htnWorldState): HTNMethod("StartMethod"), m_htnWorldState(htnWorldState)
{
}

bool StartMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void StartMethod::CreateTasks(HTNWorldState const& htnWorldState)
{
    std::shared_ptr<AbstractItem> requestedItem = m_htnWorldState.m_itemCarriedPtr;
    AddTask(new PrisonerBehaviourCompound(m_htnWorldState));
    AddTask(new RespondToItemRequestCompound(requestedItem));
}

StartCompound::StartCompound(HTNWorldState &htnWorldState): HTNCompound("StartCompound"), m_htnWorldState(htnWorldState)
{
}

void StartCompound::CreateMethods(HTNWorldState const& htnWorldState)
{
    AddMethod(new StartMethod(m_htnWorldState));
}