#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "HTNWorldState.h"
#include "AbstractAction.h"
#include "AbstractItem.h"

class AbstractPlayerData;

//***********************************************************
class StudyPrim : public HTNPrimitive
{
public:
    StudyPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class SleepPrim : public HTNPrimitive
{
public:
    SleepPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class UseGymPrim : public HTNPrimitive
{
public:
    UseGymPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class RunCircuitsPrim : public HTNPrimitive
{
public:
    RunCircuitsPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class GoToGymPrim : public HTNPrimitive
{
public:
    GoToGymPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class GoToLibraryPrim : public HTNPrimitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public HTNPrimitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class GoToBedroomPrim : public HTNPrimitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class GoToMainHallPrim : public HTNPrimitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class DrinkPrim : public HTNPrimitive
{
public:
    DrinkPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class PunchPrim : public HTNPrimitive
{
    AbstractPlayerData* m_targetPlayer;
public:
    PunchPrim(AbstractPlayerData* opponent);
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class EvadePrim : public HTNPrimitive
{
public:
    EvadePrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class PickUpItemByPtrPrim : public HTNPrimitive
{
public:
    PickUpItemByPtrPrim(SimItemPtr itemFocus);
    SimItemPtr m_itemFocus;
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class PickUpItemByTypePrim : public HTNPrimitive
{
public:
    PickUpItemByTypePrim(EItemType itemType);
    EItemType m_itemType;
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class DropItemPrim : public HTNPrimitive
{
public:
    DropItemPrim(bool keepItem);
    bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
    bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
    bool m_keepItem;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
	AbstractPlayerData* m_requestedPlayer;
    EItemType m_itemType;
public:
    RequestItemPrim(AbstractPlayerData* requestedPlayer, EItemType itemType);
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
	bool LastActionSucceeded(HTNWorldState const& htnWorldState) override;
};
