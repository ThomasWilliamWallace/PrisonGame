#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "IHTNWorldState.h"
#include "PlatformSpecific.h"
#include "EActions.h"

class UPlayerData;

// The only purpose of this class is to allow us to set the type on primitives without writing an enum-to-int cast.
// Maybe this can be replaced by removing the separate htn_planner primitive / Unreal action distinction.
class Primitive : public HTNPrimitive
{
public:
	Primitive(std::string name, EActions type): HTNPrimitive(name, static_cast<int>(type)) {};
};

//***********************************************************
class DoNothingPrim : public Primitive
{
public:
	DoNothingPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState& iHTNWorldState) override;
};

//***********************************************************
class StudyPrim : public Primitive
{
public:
    StudyPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class SleepPrim : public Primitive
{
public:
    SleepPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class UseGymPrim : public Primitive
{
public:
    UseGymPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class RunCircuitsPrim : public Primitive
{
public:
    RunCircuitsPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToGymPrim : public Primitive
{
public:
    GoToGymPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToLibraryPrim : public Primitive
{
public:
    GoToLibraryPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToCircuitTrackPrim : public Primitive
{
public:
    GoToCircuitTrackPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToBedroomPrim : public Primitive
{
public:
    GoToBedroomPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class GoToMainHallPrim : public Primitive
{
public:
    GoToMainHallPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class DrinkPrim : public Primitive
{
public:
    DrinkPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PunchPrim : public Primitive
{
public:
	UPlayerData* m_targetPlayer;
    PunchPrim(UPlayerData* opponent);
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class EvadePrim : public Primitive
{
public:
	UPlayerData* m_evadePlayer;
    EvadePrim(UPlayerData* opponent);
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PickUpItemByPtrPrim : public Primitive
{
public:
    PickUpItemByPtrPrim(SimItemPtr itemFocus);
	SimItemPtr m_itemFocus;
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class PickUpItemByTypePrim : public Primitive
{
public:
    PickUpItemByTypePrim(EItemType itemType);
	EItemType m_itemType;
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class DropItemPrim : public Primitive
{
public:
    DropItemPrim();
	bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
	void Effect(IHTNWorldState &iHTNWorldState) override;
};

//***********************************************************
class RequestItemPrim : public Primitive
{
	EItemType m_itemType;
public:
	UPlayerData* m_requestedPlayer;
    RequestItemPrim(UPlayerData* requestedPlayer, EItemType itemType);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    void Effect(IHTNWorldState &iHTNWorldState) override;
};
