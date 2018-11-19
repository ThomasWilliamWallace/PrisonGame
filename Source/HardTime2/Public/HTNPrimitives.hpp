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
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class Sleep : public HTNPrimitive
{
public:
	Sleep();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class UseGym : public HTNPrimitive
{
public:
	UseGym();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class RunCircuits : public HTNPrimitive
{
public:
	RunCircuits();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class GoToGym : public HTNPrimitive
{
public:
	GoToGym();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class GoToLibrary : public HTNPrimitive
{
public:
	GoToLibrary();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class GoToCircuitTrack : public HTNPrimitive
{
public:
	GoToCircuitTrack();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class GoToBedroom : public HTNPrimitive
{
public:
	GoToBedroom();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class GoToMainHall : public HTNPrimitive
{
public:
	GoToMainHall();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class Drink : public HTNPrimitive
{
public:
	Drink();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class Punch : public HTNPrimitive
{
	Player* m_targetPlayer;
public:
	Punch(Player* opponent);
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class Evade : public HTNPrimitive
{
public:
	Evade();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class PickUpItem : public HTNPrimitive
{
public:
	PickUpItem(SimActorItem* itemFocusPtr);
	SimActorItem* m_itemFocus;
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
};

//***********************************************************
class PickUpItem2 : public HTNPrimitive
{
public:
	PickUpItem2(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};

//***********************************************************
class DropItem : public HTNPrimitive
{
public:
	DropItem();
	bool Preconditions(HTNWorldState &htnWorldState);
	void Effect(HTNWorldState &htnWorldState);
	Actions Operate(AAICharacterC* aiCharacterC);
	bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC);
};