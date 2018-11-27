#pragma once

#include <vector>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"
#include "Actions.hpp"

class AActorItem;

//***********************************************************
class Study : public HTNPrimitive
{
public:
	Study();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class Sleep : public HTNPrimitive
{
public:
	Sleep();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class UseGym : public HTNPrimitive
{
public:
	UseGym();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class RunCircuits : public HTNPrimitive
{
public:
	RunCircuits();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class GoToGym : public HTNPrimitive
{
public:
	GoToGym();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class GoToLibrary : public HTNPrimitive
{
public:
	GoToLibrary();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class GoToCircuitTrack : public HTNPrimitive
{
public:
	GoToCircuitTrack();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class GoToBedroom : public HTNPrimitive
{
public:
	GoToBedroom();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class GoToMainHall : public HTNPrimitive
{
public:
	GoToMainHall();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class Drink : public HTNPrimitive
{
public:
	Drink();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class Punch : public HTNPrimitive
{
	UPlayerData* m_targetPlayer;
public:
	Punch(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class Evade : public HTNPrimitive
{
public:
	Evade();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class PickUpItem : public HTNPrimitive
{
public:
	PickUpItem(SimActorItem* itemFocusPtr);
	SimActorItem* m_itemFocus;
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};

//***********************************************************
class PickUpItem2 : public HTNPrimitive
{
public:
	PickUpItem2(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class DropItem : public HTNPrimitive
{
public:
	DropItem();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
	bool LastActionSucceeded(HTNWorldState &htnWorldState);
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemPrim(UPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState);
    void Effect(HTNWorldState &htnWorldState);
    Actions Operate(UPlayerData* playerData, HTNWorldState &htnWorldState);
};
