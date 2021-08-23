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
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class SleepPrim : public HTNPrimitive
{
public:
    SleepPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class UseGymPrim : public HTNPrimitive
{
public:
    UseGymPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class RunCircuitsPrim : public HTNPrimitive
{
public:
    RunCircuitsPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class GoToGymPrim : public HTNPrimitive
{
public:
    GoToGymPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class GoToLibraryPrim : public HTNPrimitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public HTNPrimitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class GoToBedroomPrim : public HTNPrimitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class GoToMainHallPrim : public HTNPrimitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class DrinkPrim : public HTNPrimitive
{
public:
    DrinkPrim();
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class PunchPrim : public HTNPrimitive
{
    UPlayerData* m_targetPlayer;
public:
    PunchPrim(UPlayerData* opponent);
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class EvadePrim : public HTNPrimitive
{
	UPlayerData* m_evadePlayer;
public:
    EvadePrim(UPlayerData* opponent);
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class PickUpItemByPtrPrim : public HTNPrimitive
{
public:
    PickUpItemByPtrPrim(SimItemPtr itemFocus);
    SimItemPtr m_itemFocus;
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class PickUpItemByTypePrim : public HTNPrimitive
{
public:
    PickUpItemByTypePrim(EItemType itemType);
    EItemType m_itemType;
	bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};

//***********************************************************
class DropItemPrim : public HTNPrimitive
{
public:
    DropItemPrim(bool keepItem);
    bool Preconditions(HTNWorldState const& htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
    bool m_keepItem;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
	UPlayerData* m_requestedPlayer;
    EItemType m_itemType;
public:
    RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType);
    bool Preconditions(HTNWorldState const& htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    std::shared_ptr<BaseAction> Operate(UPlayerData* playerData) override;
};
