#pragma once

#include <vector>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"
#include "Actions.hpp"

class AActorItem;
class USimWorld;

//***********************************************************
class Study : public HTNPrimitive
{
public:
	Study();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class Sleep : public HTNPrimitive
{
public:
	Sleep();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class UseGym : public HTNPrimitive
{
public:
	UseGym();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class RunCircuits : public HTNPrimitive
{
public:
	RunCircuits();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class GoToGym : public HTNPrimitive
{
public:
	GoToGym();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToLibrary : public HTNPrimitive
{
public:
	GoToLibrary();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToCircuitTrack : public HTNPrimitive
{
public:
	GoToCircuitTrack();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToBedroom : public HTNPrimitive
{
public:
	GoToBedroom();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class GoToMainHall : public HTNPrimitive
{
public:
	GoToMainHall();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class Drink : public HTNPrimitive
{
public:
	Drink();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class Punch : public HTNPrimitive
{
	UPlayerData* m_targetPlayer;
public:
	Punch(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class Evade : public HTNPrimitive
{
public:
	Evade();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class PickUpItem : public HTNPrimitive
{
public:
	PickUpItem(SimActorItem* itemFocusPtr);
	SimActorItem* m_itemFocus;
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};

//***********************************************************
class PickUpItem2 : public HTNPrimitive
{
public:
	PickUpItem2(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class DropItem : public HTNPrimitive
{
public:
	DropItem();
	bool Preconditions(HTNWorldState &htnWorldState) override;
	void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
	bool LastActionSucceeded(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemPrim(UPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    void Effect(HTNWorldState &htnWorldState) override;
    Actions Operate(UPlayerData* playerData, USimWorld &world) override;
};
