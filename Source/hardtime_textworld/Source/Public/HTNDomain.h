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
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToNearbyLibraryMethod : public HTNMethod
{
public:
    GoToNearbyLibraryMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToDistantLibraryMethod : public HTNMethod
{
public:
    GoToDistantLibraryMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToLibraryCompound : public HTNCompound
{
public:
    GoToLibraryCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class AlreadyInGymMethod : public HTNMethod
{
public:
    AlreadyInGymMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToNearbyGymMethod : public HTNMethod
{
public:
    GoToNearbyGymMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToDistantGymMethod : public HTNMethod
{
public:
    GoToDistantGymMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToGymCompound : public HTNCompound
{
public:
    GoToGymCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class AlreadyInCircuitTrackMethod : public HTNMethod
{
public:
    AlreadyInCircuitTrackMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToNearbyCircuitTrackMethod : public HTNMethod
{
public:
    GoToNearbyCircuitTrackMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToDistantCircuitTrackMethod : public HTNMethod
{
public:
    GoToDistantCircuitTrackMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToCircuitTrackCompound : public HTNCompound
{
public:
    GoToCircuitTrackCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class AlreadyInBedroomMethod : public HTNMethod
{
public:
    AlreadyInBedroomMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToNearbyBedroomMethod : public HTNMethod
{
public:
    GoToNearbyBedroomMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToDistantBedroomMethod : public HTNMethod
{
public:
    GoToDistantBedroomMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToBedroomCompound : public HTNCompound
{
public:
    GoToBedroomCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class IncreaseHealthImmediateMethod : public HTNMethod
{
public:
    IncreaseHealthImmediateMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToAndIncreaseHealthMethod : public HTNMethod
{
public:
    GoToAndIncreaseHealthMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseHealthCompound : public HTNCompound
{
public:
    IncreaseHealthCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class IncreaseStrengthImmediateMethod : public HTNMethod
{
public:
    IncreaseStrengthImmediateMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToAndIncreaseStrengthMethod : public HTNMethod
{
public:
    GoToAndIncreaseStrengthMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseStrengthCompound : public HTNCompound
{
public:
    IncreaseStrengthCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class IncreaseAgilityImmediateMethod : public HTNMethod
{
public:
    IncreaseAgilityImmediateMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToAndIncreaseAgilityMethod : public HTNMethod
{
public:
    GoToAndIncreaseAgilityMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseAgilityCompound : public HTNCompound
{
public:
    IncreaseAgilityCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class IncreaseIntelligenceImmediateMethod : public HTNMethod
{
public:
    IncreaseIntelligenceImmediateMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GoToAndIncreaseIntelligenceMethod : public HTNMethod
{
public:
    GoToAndIncreaseIntelligenceMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
    IncreaseIntelligenceCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class HaveItemMethod : public HTNMethod
{
    EItemType m_itemType;
public:
    HaveItemMethod(EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class PickupItemMethod : public HTNMethod
{
    EItemType m_itemType;
public:
    PickupItemMethod(EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class RequestItemMethod : public HTNMethod
{
    AbstractPlayerData* m_player;
    EItemType m_itemType;
public:
    RequestItemMethod(AbstractPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GetItemCompound : public HTNCompound
{
    EItemType m_itemType;
public:
    GetItemCompound(EItemType itemType);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class DropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    DropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class BringAndDropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringAndDropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class GetBringAndDropItemMethod : public HTNMethod
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    GetBringAndDropItemMethod(EItemType itemType, LocationClass &locationClass);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class BringItemToLocationCompound : public HTNCompound
{
    EItemType m_itemType;
    LocationClass& m_locationClass;
public:
    BringItemToLocationCompound(EItemType itemType, LocationClass &locationClass); //be wary with this. Probably just refactor to pass locationClass by value rather than reference
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class PickupItemAndAttackMethod : public HTNMethod
{
    SimItemPtr m_item;
    AbstractPlayerData* m_opponent;
public:
    PickupItemAndAttackMethod(SimItemPtr item, AbstractPlayerData* opponent);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class AttackImmediateMethod : public HTNMethod
{
    AbstractPlayerData* m_opponent;
public:
    AttackImmediateMethod(AbstractPlayerData* opponent);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class AttackCompound : public HTNCompound
{
    AbstractPlayerData* m_opponent;
public:
    AttackCompound(AbstractPlayerData* opponent);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

class AttackMethod : public HTNMethod
{
    AbstractPlayerData* m_opponent;
public:
    AttackMethod(AbstractPlayerData* opponent);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class EvadeMethod : public HTNMethod
{
    AbstractPlayerData* m_opponent;
public:
    EvadeMethod(AbstractPlayerData* opponent);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class CombatCompound : public HTNCompound
{
    AbstractPlayerData* m_opponent;
public:
    CombatCompound(AbstractPlayerData* opponent);
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class IncreaseStrengthMissionMethod : public HTNMethod
{
public:
    IncreaseStrengthMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseAgilityMissionMethod : public HTNMethod
{
public:
    IncreaseAgilityMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseIntelligenceMissionMethod : public HTNMethod
{
public:
    IncreaseIntelligenceMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class BringItemToRoomMissionMethod : public HTNMethod
{
public:
    BringItemToRoomMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class DoMissionCompound : public HTNCompound
{
public:
	DoMissionCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class PickUpUnneccessaryItemCompound : public HTNCompound
{
public:
    PickUpUnneccessaryItemCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};

class PickUpUnneccessaryItemMethod : public HTNMethod
{
public:
    PickUpUnneccessaryItemMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class CombatMethod : public HTNMethod
{
    AbstractPlayerData* m_opponent;
public:
	CombatMethod(AbstractPlayerData* opponent);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class DoMissionMethod : public HTNMethod
{
public:
	DoMissionMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

class IncreaseIntelligenceMethod : public HTNMethod
{
public:
    IncreaseIntelligenceMethod();
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class PickUpItemByPtrMethod : public HTNMethod
{
    SimItemPtr m_itemFocusPtr;
public:
    PickUpItemByPtrMethod(SimItemPtr itemFocus);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class DropAnyItemImmediateMethod : public HTNMethod
{
    bool m_keepItem;
public:
    DropAnyItemImmediateMethod(bool keepItem);
    bool Preconditions(HTNWorldState &htnWorldState) override;
    virtual void CreateTasks(HTNWorldState const& htnWorldState) override;
};

//***********************************************************
class PrisonerBehaviourCompound : public HTNCompound
{
public:
	PrisonerBehaviourCompound();
    virtual void CreateMethods(HTNWorldState const& htnWorldState) override;
};
