#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "HTNWorldState.h"

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
};

//***********************************************************
class GoToLibraryPrim : public HTNPrimitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
	std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public HTNPrimitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
	std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class GoToBedroomPrim : public HTNPrimitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
	std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
};

//***********************************************************
class GoToMainHallPrim : public HTNPrimitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
	std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
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
};

//***********************************************************
class DropItemPrim : public HTNPrimitive
{
public:
    DropItemPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
	std::shared_ptr<BaseAction> Operate(AbstractPlayerData* playerData) override;
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
};
