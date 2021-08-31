#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "IHTNWorldState.h"
#include "PlatformSpecific.h"

class UPlayerData;

//***********************************************************
class DoNothingPrim : public HTNPrimitive
{
public:
	DoNothingPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState& iHTNWorldState) override;
};

//***********************************************************
class StudyPrim : public HTNPrimitive
{
public:
    StudyPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class SleepPrim : public HTNPrimitive
{
public:
    SleepPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class UseGymPrim : public HTNPrimitive
{
public:
    UseGymPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class RunCircuitsPrim : public HTNPrimitive
{
public:
    RunCircuitsPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToGymPrim : public HTNPrimitive
{
public:
    GoToGymPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToLibraryPrim : public HTNPrimitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public HTNPrimitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToBedroomPrim : public HTNPrimitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToMainHallPrim : public HTNPrimitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class DrinkPrim : public HTNPrimitive
{
public:
    DrinkPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PunchPrim : public HTNPrimitive
{
public:
	UPlayerData* m_targetPlayer;
    PunchPrim(UPlayerData* opponent);
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class EvadePrim : public HTNPrimitive
{
public:
	UPlayerData* m_evadePlayer;
    EvadePrim(UPlayerData* opponent);
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PickUpItemByPtrPrim : public HTNPrimitive
{
public:
    PickUpItemByPtrPrim(SimItemPtr itemFocus);
	SimItemPtr m_itemFocus;
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PickUpItemByTypePrim : public HTNPrimitive
{
public:
    PickUpItemByTypePrim(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class DropItemPrim : public HTNPrimitive
{
public:
    DropItemPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class RequestItemPrim : public HTNPrimitive
{
	EItemType m_itemType;
public:
	UPlayerData* m_requestedPlayer;
    RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};
