#pragma once

#include <vector>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"

class AActorItem;
class USimWorld;

//***********************************************************
class StudyPrim : public HTNPrimitive
{
public:
    StudyPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class SleepPrim : public HTNPrimitive
{
public:
    SleepPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class UseGymPrim : public HTNPrimitive
{
public:
    UseGymPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class RunCircuitsPrim : public HTNPrimitive
{
public:
    RunCircuitsPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class GoToGymPrim : public HTNPrimitive
{
public:
    GoToGymPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToLibraryPrim : public HTNPrimitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public HTNPrimitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToBedroomPrim : public HTNPrimitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToMainHallPrim : public HTNPrimitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class DrinkPrim : public HTNPrimitive
{
public:
    DrinkPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class PunchPrim : public HTNPrimitive
{
	UPlayerData* m_targetPlayer;
public:
    PunchPrim(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class EvadePrim : public HTNPrimitive
{
public:
    EvadePrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class PickUpItemByPtrPrim : public HTNPrimitive
{
public:
    PickUpItemByPtrPrim(SimActorItemPtr itemFocus);
    SimActorItemPtr m_itemFocus;
    bool Preconditions(HTNWorldState &htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class PickUpItemByTypePrim : public HTNPrimitive
{
public:
    PickUpItemByTypePrim(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class DropItemPrim : public HTNPrimitive
{
public:
    DropItemPrim();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
    UPlayerData* m_requestedPlayer;
    EItemType m_itemType;
public:
    RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* selfPlayer, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};
