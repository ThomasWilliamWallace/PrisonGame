#pragma once

#include <vector>
#include <iostream>
#include "PlatformSpecific.h"
#include "EActions.h"

class AbstractMission;
#ifndef TEXT_ONLY_HTN
class AActorItem;
#endif

std::string ActionToString(EActions action);

class BaseAction
{
public:
    BaseAction(EActions action): m_action(action) {};
    virtual std::string ToString();
    EActions m_action;
    virtual ~BaseAction() = default;
};

class AttackAction : public BaseAction
{
public:
    AttackAction(AbstractPlayerData* targetPlayer): BaseAction(EActions::attack), m_targetPlayer(targetPlayer) {};
    AbstractPlayerData* m_targetPlayer;
};

class PickUpItemByPtrAction : public BaseAction
{
public:
    PickUpItemByPtrAction(RealItemType* itemFocusPtr): BaseAction(EActions::pickUpItemByPtr), m_itemFocusPtr(itemFocusPtr) {};
    RealItemType* m_itemFocusPtr;
};

class PickUpItemByTypeAction : public BaseAction
{
public:
    PickUpItemByTypeAction(EItemType itemType): BaseAction(EActions::pickUpItemByType), m_itemType(itemType) {};
    EItemType m_itemType;
};

class RequestItemAction : public BaseAction
{
public:
    RequestItemAction(AbstractPlayerData* targetPlayer): BaseAction(EActions::requestItem), m_targetPlayer(targetPlayer) {};
    AbstractPlayerData* m_targetPlayer;
};

class MakeFriendsAction : public BaseAction
{
public:
    MakeFriendsAction(AbstractPlayerData* targetPlayer): BaseAction(EActions::makeFriends), m_targetPlayer(targetPlayer) {};
    AbstractPlayerData* m_targetPlayer;
};

class OfferMissionAction : public BaseAction
{
public:
    OfferMissionAction(AbstractPlayerData* targetPlayer, std::shared_ptr<AbstractMission> offeredMission): BaseAction(EActions::offerMission), m_targetPlayer(targetPlayer), m_offeredMission(offeredMission) {};
    AbstractPlayerData* m_targetPlayer;
    std::shared_ptr<AbstractMission> m_offeredMission;
};
