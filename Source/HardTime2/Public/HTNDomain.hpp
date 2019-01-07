#pragma once

#include <vector>
#include "HTNPlanner.hpp"
#include "HTNWorldState.hpp"

//***********************************************************
class GoToNearbyLibraryMethod : public HTNMethod
{
public:
    GoToNearbyLibraryMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToDistantLibraryMethod : public HTNMethod
{
public:
    GoToDistantLibraryMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToLibraryCompound : public HTNCompound
{
public:
	GoToLibraryCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class GoToNearbyGymMethod : public HTNMethod
{
public:
    GoToNearbyGymMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToDistantGymMethod : public HTNMethod
{
public:
    GoToDistantGymMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToGymCompound : public HTNCompound
{
public:
	GoToGymCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class GoToNearbyCircuitTrackMethod : public HTNMethod
{
public:
    GoToNearbyCircuitTrackMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToDistantCircuitTrackMethod : public HTNMethod
{
public:
    GoToDistantCircuitTrackMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToCircuitTrackCompound : public HTNCompound
{
public:
	GoToCircuitTrackCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class GoToNearbyBedroomMethod : public HTNMethod
{
public:
    GoToNearbyBedroomMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToDistantBedroomMethod : public HTNMethod
{
public:
    GoToDistantBedroomMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToBedroomCompound : public HTNCompound
{
public:
	GoToBedroomCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class IncreaseHealthImmediateMethod : public HTNMethod
{
public:
    IncreaseHealthImmediateMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToAndIncreaseHealthMethod : public HTNMethod
{
public:
    GoToAndIncreaseHealthMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseHealthCompound : public HTNCompound
{
public:
	IncreaseHealthCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class IncreaseStrengthImmediateMethod : public HTNMethod
{
public:
    IncreaseStrengthImmediateMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToAndIncreaseStrengthMethod : public HTNMethod
{
public:
    GoToAndIncreaseStrengthMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseStrengthCompound : public HTNCompound
{
public:
	IncreaseStrengthCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class IncreaseAgilityImmediateMethod : public HTNMethod
{
public:
    IncreaseAgilityImmediateMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToAndIncreaseAgilityMethod : public HTNMethod
{
public:
    GoToAndIncreaseAgilityMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseAgilityCompound : public HTNCompound
{
public:
	IncreaseAgilityCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class IncreaseIntelligenceImmediateMethod : public HTNMethod
{
public:
    IncreaseIntelligenceImmediateMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GoToAndIncreaseIntelligenceMethod : public HTNMethod
{
public:
    GoToAndIncreaseIntelligenceMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
	IncreaseIntelligenceCompound();
    virtual void CreateMethods() override;
};

//***********************************************************
class PickupItemMethod : public HTNMethod
{
	EItemType m_itemType;
public:
    PickupItemMethod(EItemType itemType);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class RequestItemMethod : public HTNMethod
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemMethod(UPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GetItemCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    EItemType m_itemType;
public:
    GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType);
    virtual void CreateMethods() override;
};

//***********************************************************
class DropItemMethod : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
    DropItemMethod(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class BringAndDropItemMethod : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
    BringAndDropItemMethod(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class GetBringAndDropItemMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
    GetBringAndDropItemMethod(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class BringItemToLocationCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass); //be wary with this. Probably just refactor to pass locationClass by value rather than reference
    virtual void CreateMethods() override;
};

//***********************************************************
class PickupItemAndAttackMethod : public HTNMethod
{
    SimActorItemPtr m_item;
	UPlayerData* m_opponent;
public:
    PickupItemAndAttackMethod(SimActorItemPtr item, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class AttackImmediateMethod : public HTNMethod
{
	UPlayerData* m_opponent;
public:
    AttackImmediateMethod(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class AttackCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
    virtual void CreateMethods() override;
};

class AttackMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
    AttackMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

//***********************************************************
class EvadeMethod : public HTNMethod
{
public:
    EvadeMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class CombatCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
    CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
    virtual void CreateMethods() override;
};

//***********************************************************
class IncreaseStrengthMissionMethod : public HTNMethod
{
public:
    IncreaseStrengthMissionMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseAgilityMissionMethod : public HTNMethod
{
public:
    IncreaseAgilityMissionMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseIntelligenceMissionMethod : public HTNMethod
{
public:
    IncreaseIntelligenceMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class BringItemToRoomMissionMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
public:
    BringItemToRoomMissionMethod(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class DoMissionCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
public:
	DoMissionCompound(HTNWorldState &htnWorldState);
    virtual void CreateMethods() override;
};

//***********************************************************
class CombatMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
    UPlayerData* m_opponent;
public:
	CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class DoMissionMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
public:
	DoMissionMethod(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class IncreaseIntelligenceMethod : public HTNMethod
{
public:
	IncreaseIntelligenceMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

//***********************************************************
class PickUpItemByPtrMethod : public HTNMethod
{
    SimActorItemPtr m_itemFocusPtr;
public:
    PickUpItemByPtrMethod(SimActorItemPtr itemFocus);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

//***********************************************************
class DropAnyItemImmediateMethod : public HTNMethod
{
public:
	DropAnyItemImmediateMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

//***********************************************************
class PrisonerBehaviourCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
public:
	PrisonerBehaviourCompound(HTNWorldState &htnWorldState);
    virtual void CreateMethods() override;
};
