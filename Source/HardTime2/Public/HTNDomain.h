#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "HTNWorldState.h"

//***********************************************************
class AlreadyInLibraryMethod : public HTNMethod
{
public:
    AlreadyInLibraryMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

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
class AlreadyInGymMethod : public HTNMethod
{
public:
    AlreadyInGymMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

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
class AlreadyInCircuitTrackMethod : public HTNMethod
{
public:
    AlreadyInCircuitTrackMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

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
class AlreadyInBedroomMethod : public HTNMethod
{
public:
    AlreadyInBedroomMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

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
class HaveItemMethod : public HTNMethod
{
    EItemType m_itemType;
public:
    HaveItemMethod(EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

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
    AbstractPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemMethod(AbstractPlayerData* player, EItemType itemType);
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
    SimItemPtr m_item;
    AbstractPlayerData* m_opponent;
public:
    PickupItemAndAttackMethod(SimItemPtr item, AbstractPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class AttackImmediateMethod : public HTNMethod
{
    AbstractPlayerData* m_opponent;
public:
    AttackImmediateMethod(AbstractPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks() override;
};

class AttackCompound : public HTNCompound
{
    HTNWorldState& m_htnWorldState;
    AbstractPlayerData* m_opponent;
public:
	AttackCompound(HTNWorldState &htnWorldState, AbstractPlayerData* opponent);
    virtual void CreateMethods() override;
};

class AttackMethod : public HTNMethod
{
    HTNWorldState& m_htnWorldState;
    AbstractPlayerData* m_opponent;
public:
    AttackMethod(HTNWorldState &htnWorldState, AbstractPlayerData* opponent);
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
    AbstractPlayerData* m_opponent;
public:
    CombatCompound(HTNWorldState &htnWorldState, AbstractPlayerData* opponent);
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
    AbstractPlayerData* m_opponent;
public:
	CombatMethod(HTNWorldState &htnWorldState, AbstractPlayerData* opponent);
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
    SimItemPtr m_itemFocusPtr;
public:
    PickUpItemByPtrMethod(SimItemPtr itemFocus);
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
