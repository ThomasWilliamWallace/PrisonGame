#pragma once

#include <vector>
#include "HTNPlanner.h"
#include "HTNWorldState.h"

//***********************************************************
class AlreadyInLibraryMethod : public HTNMethod
{
public:
    AlreadyInLibraryMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToNearbyLibraryMethod : public HTNMethod
{
public:
    GoToNearbyLibraryMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToDistantLibraryMethod : public HTNMethod
{
public:
    GoToDistantLibraryMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToLibraryCompound : public HTNCompound
{
public:
    GoToLibraryCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class AlreadyInGymMethod : public HTNMethod
{
public:
    AlreadyInGymMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToNearbyGymMethod : public HTNMethod
{
public:
    GoToNearbyGymMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToDistantGymMethod : public HTNMethod
{
public:
    GoToDistantGymMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToGymCompound : public HTNCompound
{
public:
    GoToGymCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class AlreadyInCircuitTrackMethod : public HTNMethod
{
public:
    AlreadyInCircuitTrackMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToNearbyCircuitTrackMethod : public HTNMethod
{
public:
    GoToNearbyCircuitTrackMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToDistantCircuitTrackMethod : public HTNMethod
{
public:
    GoToDistantCircuitTrackMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToCircuitTrackCompound : public HTNCompound
{
public:
    GoToCircuitTrackCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class AlreadyInBedroomMethod : public HTNMethod
{
public:
    AlreadyInBedroomMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToNearbyBedroomMethod : public HTNMethod
{
public:
    GoToNearbyBedroomMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToDistantBedroomMethod : public HTNMethod
{
public:
    GoToDistantBedroomMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToBedroomCompound : public HTNCompound
{
public:
    GoToBedroomCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class IncreaseHealthImmediateMethod : public HTNMethod
{
public:
    IncreaseHealthImmediateMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToAndIncreaseHealthMethod : public HTNMethod
{
public:
    GoToAndIncreaseHealthMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseHealthCompound : public HTNCompound
{
public:
    IncreaseHealthCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class IncreaseStrengthImmediateMethod : public HTNMethod
{
public:
    IncreaseStrengthImmediateMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToAndIncreaseStrengthMethod : public HTNMethod
{
public:
    GoToAndIncreaseStrengthMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseStrengthCompound : public HTNCompound
{
public:
    IncreaseStrengthCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class IncreaseAgilityImmediateMethod : public HTNMethod
{
public:
    IncreaseAgilityImmediateMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToAndIncreaseAgilityMethod : public HTNMethod
{
public:
    GoToAndIncreaseAgilityMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseAgilityCompound : public HTNCompound
{
public:
    IncreaseAgilityCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class IncreaseIntelligenceImmediateMethod : public HTNMethod
{
public:
    IncreaseIntelligenceImmediateMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GoToAndIncreaseIntelligenceMethod : public HTNMethod
{
public:
    GoToAndIncreaseIntelligenceMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
    IncreaseIntelligenceCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class HaveItemMethod : public HTNMethod
{
    EItemType m_itemType;
public:
    HaveItemMethod(EItemType itemType);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class PickupItemMethod : public HTNMethod
{
    EItemType m_itemType;
public:
    PickupItemMethod(EItemType itemType);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class RequestItemMethod : public HTNMethod
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemMethod(UPlayerData* player, EItemType itemType);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GetItemCompound : public HTNCompound
{
    EItemType m_itemType;
public:
    GetItemCompound(EItemType itemType);
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class DropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    DropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class BringAndDropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringAndDropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class GetBringAndDropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    GetBringAndDropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class BringItemToLocationCompound : public HTNCompound
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringItemToLocationCompound(EItemType itemType, LocationClass &locationClass); //be wary with this. Probably just refactor to pass locationClass by value rather than reference
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class PickupItemAndAttackMethod : public HTNMethod
{
    SimItemPtr m_item;
    UPlayerData* m_opponent;
public:
    PickupItemAndAttackMethod(SimItemPtr item, UPlayerData* opponent);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class AttackImmediateMethod : public HTNMethod
{
    UPlayerData* m_opponent;
public:
    AttackImmediateMethod(UPlayerData* opponent);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class AttackCompound : public HTNCompound
{
    UPlayerData* m_opponent;
public:
    AttackCompound(UPlayerData* opponent);
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

class AttackMethod : public HTNMethod
{
    UPlayerData* m_opponent;
public:
    AttackMethod(UPlayerData* opponent);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class EvadeMethod : public HTNMethod
{
    UPlayerData* m_opponent;
public:
    EvadeMethod(UPlayerData* opponent);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class CombatCompound : public HTNCompound
{
    UPlayerData* m_opponent;
public:
    CombatCompound(UPlayerData* opponent);
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class IncreaseStrengthMissionMethod : public HTNMethod
{
public:
    IncreaseStrengthMissionMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseAgilityMissionMethod : public HTNMethod
{
public:
    IncreaseAgilityMissionMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseIntelligenceMissionMethod : public HTNMethod
{
public:
    IncreaseIntelligenceMissionMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class BringItemToRoomMissionMethod : public HTNMethod
{
public:
    BringItemToRoomMissionMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class DoMissionCompound : public HTNCompound
{
public:
	DoMissionCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class PickUpUnneccessaryItemCompound : public HTNCompound
{
public:
    PickUpUnneccessaryItemCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};

class PickUpUnneccessaryItemMethod : public HTNMethod
{
public:
    PickUpUnneccessaryItemMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class CombatMethod : public HTNMethod
{
    UPlayerData* m_opponent;
public:
	CombatMethod(UPlayerData* opponent);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class DoMissionMethod : public HTNMethod
{
public:
	DoMissionMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

class IncreaseIntelligenceMethod : public HTNMethod
{
public:
    IncreaseIntelligenceMethod();
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class PickUpItemByPtrMethod : public HTNMethod
{
    SimItemPtr m_itemFocusPtr;
public:
    PickUpItemByPtrMethod(SimItemPtr itemFocus);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class DropAnyItemImmediateMethod : public HTNMethod
{
    bool m_keepItem;
public:
    DropAnyItemImmediateMethod(bool keepItem);
    bool Preconditions(IHTNWorldState const& iHTNWorldState) override;
    virtual void CreateTasks(IHTNWorldState const& iHTNWorldState) override;
};

//***********************************************************
class PrisonerBehaviourCompound : public HTNCompound
{
public:
	PrisonerBehaviourCompound();
    virtual void CreateMethods(IHTNWorldState const& iHTNWorldState) override;
};
