#pragma once

#include <vector>
#include <iostream>
#include "PlatformSpecific.h"
#include "EActions.h"

class HTNWorldState;

class MissionClass;
#ifndef TEXT_ONLY_HTN
class AActorItem;
#endif

std::string ActionToString(EActions action);

class BaseAction
{
public:
    BaseAction(EActions action): m_action(action) {};
    virtual std::string ToString();
    virtual bool LastActionSucceeded(HTNWorldState const& htnWorldState); //returns true if this action appears to have succeeded.
    EActions m_action;
    virtual ~BaseAction() = default;
};

class GoToGymAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class GoToLibraryAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class GoToCircuitTrackAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class GoToBedroomAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class GoToMainHallAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class AttackAction : public BaseAction
{
public:
    AttackAction(UPlayerData* targetPlayer): BaseAction(EActions::attack), m_targetPlayer(targetPlayer) {};
    UPlayerData* m_targetPlayer;
};

class EvadeAction : public BaseAction
{
public:
    EvadeAction(UPlayerData* evadePlayer) : BaseAction(EActions::evade), m_evadePlayer(evadePlayer) {};
    UPlayerData* m_evadePlayer;
};

class PickUpItemByPtrAction : public BaseAction
{
public:
    PickUpItemByPtrAction(RealItemType* itemFocusPtr): BaseAction(EActions::pickUpItemByPtr), m_itemFocusPtr(itemFocusPtr) {};
    RealItemType* m_itemFocusPtr;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class PickUpItemByTypeAction : public BaseAction
{
public:
    PickUpItemByTypeAction(EItemType itemType): BaseAction(EActions::pickUpItemByType), m_itemType(itemType) {};
    EItemType m_itemType;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class RequestItemAction : public BaseAction
{
public:
    RequestItemAction(UPlayerData* targetPlayer, EItemType itemType);
    RequestItemAction(UPlayerData* targetPlayer);
    UPlayerData* m_targetPlayer;
    bool m_itemTypeSpecified;
    EItemType m_itemType;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class DropItemAction : public BaseAction
{
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

class MakeFriendsAction : public BaseAction
{
public:
    MakeFriendsAction(UPlayerData* targetPlayer): BaseAction(EActions::makeFriends), m_targetPlayer(targetPlayer) {};
    UPlayerData* m_targetPlayer;
};

class OfferMissionAction : public BaseAction
{
public:
    OfferMissionAction(UPlayerData* targetPlayer, std::shared_ptr<MissionClass> offeredMission): BaseAction(EActions::offerMission), m_targetPlayer(targetPlayer), m_offeredMission(offeredMission) {};
    UPlayerData* m_targetPlayer;
    std::shared_ptr<MissionClass> m_offeredMission;
};
