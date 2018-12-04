#pragma once

#include <vector>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"

//***********************************************************
class GoToLibraryMethod1 : public HTNMethod
{
public:
	GoToLibraryMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToLibraryMethod2 : public HTNMethod
{
public:
	GoToLibraryMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToLibraryCompound : public HTNCompound
{
public:
	GoToLibraryCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class GoToGymMethod1 : public HTNMethod
{
public:
	GoToGymMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToGymMethod2 : public HTNMethod
{
public:
	GoToGymMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToGymCompound : public HTNCompound
{
public:
	GoToGymCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class GoToCircuitTrackMethod1 : public HTNMethod
{
public:
	GoToCircuitTrackMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToCircuitTrackMethod2 : public HTNMethod
{
public:
	GoToCircuitTrackMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToCircuitTrackCompound : public HTNCompound
{
public:
	GoToCircuitTrackCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class GoToBedroomMethod1 : public HTNMethod
{
public:
	GoToBedroomMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToBedroomMethod2 : public HTNMethod
{
public:
	GoToBedroomMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GoToBedroomCompound : public HTNCompound
{
public:
	GoToBedroomCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class IncreaseHealthMethod1 : public HTNMethod
{
public:
	IncreaseHealthMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseHealthMethod2 : public HTNMethod
{
public:
	IncreaseHealthMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseHealthCompound : public HTNCompound
{
public:
	IncreaseHealthCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class IncreaseStrengthMethod1 : public HTNMethod
{
public:
	IncreaseStrengthMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseStrengthMethod2 : public HTNMethod
{
public:
	IncreaseStrengthMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseStrengthCompound : public HTNCompound
{
public:
	IncreaseStrengthCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class IncreaseAgilityMethod1 : public HTNMethod
{
public:
	IncreaseAgilityMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseAgilityMethod2 : public HTNMethod
{
public:
	IncreaseAgilityMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseAgilityCompound : public HTNCompound
{
public:
	IncreaseAgilityCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class IncreaseIntelligenceMethod1 : public HTNMethod
{
public:
	IncreaseIntelligenceMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseIntelligenceMethod2 : public HTNMethod
{
public:
	IncreaseIntelligenceMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
	IncreaseIntelligenceCompound();
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class GetItemMethod1 : public HTNMethod
{
	EItemType m_itemType;
public:
	GetItemMethod1(EItemType itemType);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GetItemMethod2 : public HTNMethod
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    GetItemMethod2(UPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class GetItemCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    EItemType m_itemType;
public:
    GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType);
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class BringItemToLocationMethod1 : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
	BringItemToLocationMethod1(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class BringItemToLocationMethod2 : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
	BringItemToLocationMethod2(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class BringItemToLocationMethod3 : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
    BringItemToLocationMethod3(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class BringItemToLocationCompound : public HTNCompound
{
    HTNWorldState m_htnWorldState;
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass); //be wary with this. Probably just refactor to pass locationClass by value rather than reference
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class AttackMethod1 : public HTNMethod
{
	SimActorItem* m_item;
	UPlayerData* m_opponent;
public:
	AttackMethod1(SimActorItem* item, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class AttackMethod2 : public HTNMethod
{
	UPlayerData* m_opponent;
public:
	AttackMethod2(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class AttackCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
    virtual HTNMethodList& GetMethods() override;
};

class AttackCompoundMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	AttackCompoundMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

//***********************************************************
class DoMissionMethod1 : public HTNMethod
{
public:
	DoMissionMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class DoMissionMethod2 : public HTNMethod
{
public:
	DoMissionMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class DoMissionMethod3 : public HTNMethod
{
public:
	DoMissionMethod3();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class DoMissionMethod4 : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
public:
	DoMissionMethod4(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class DoMissionCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
public:
	DoMissionCompound(HTNWorldState &htnWorldState);
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class EvadeMethod : public HTNMethod
{
public:
	EvadeMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class CombatCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
    virtual HTNMethodList& GetMethods() override;
};

//***********************************************************
class CombatMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class DoMissionMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
public:
	DoMissionMethod(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

class IncreaseIntelligenceMethod : public HTNMethod
{
public:
	IncreaseIntelligenceMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

//***********************************************************
class PickUpItemMethod1 : public HTNMethod
{
    SimActorItem* m_itemFocusPtr;
public:
	PickUpItemMethod1(SimActorItem* itemFocus);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

//***********************************************************
class DropItemMethod1 : public HTNMethod
{
public:
	DropItemMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual HTNNodeList& GetTasks() override;
};

//***********************************************************
class PrisonerBehaviourCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
public:
	PrisonerBehaviourCompound(HTNWorldState &htnWorldState);
    virtual HTNMethodList& GetMethods() override;
};
