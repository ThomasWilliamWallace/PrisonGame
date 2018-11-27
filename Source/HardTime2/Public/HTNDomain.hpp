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
};

class GoToLibraryMethod2 : public HTNMethod
{
public:
	GoToLibraryMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToLibraryCompound : public HTNCompound
{
public:
	GoToLibraryCompound();
};

//***********************************************************
class GoToGymMethod1 : public HTNMethod
{
public:
	GoToGymMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToGymMethod2 : public HTNMethod
{
public:
	GoToGymMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToGymCompound : public HTNCompound
{
public:
	GoToGymCompound();
};

//***********************************************************
class GoToCircuitTrackMethod1 : public HTNMethod
{
public:
	GoToCircuitTrackMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToCircuitTrackMethod2 : public HTNMethod
{
public:
	GoToCircuitTrackMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToCircuitTrackCompound : public HTNCompound
{
public:
	GoToCircuitTrackCompound();
};

//***********************************************************
class GoToBedroomMethod1 : public HTNMethod
{
public:
	GoToBedroomMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToBedroomMethod2 : public HTNMethod
{
public:
	GoToBedroomMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GoToBedroomCompound : public HTNCompound
{
public:
	GoToBedroomCompound();
};

//***********************************************************
class IncreaseHealthMethod1 : public HTNMethod
{
public:
	IncreaseHealthMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseHealthMethod2 : public HTNMethod
{
public:
	IncreaseHealthMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseHealthCompound : public HTNCompound
{
public:
	IncreaseHealthCompound();
};

//***********************************************************
class IncreaseStrengthMethod1 : public HTNMethod
{
public:
	IncreaseStrengthMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseStrengthMethod2 : public HTNMethod
{
public:
	IncreaseStrengthMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseStrengthCompound : public HTNCompound
{
public:
	IncreaseStrengthCompound();
};

//***********************************************************
class IncreaseAgilityMethod1 : public HTNMethod
{
public:
	IncreaseAgilityMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseAgilityMethod2 : public HTNMethod
{
public:
	IncreaseAgilityMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseAgilityCompound : public HTNCompound
{
public:
	IncreaseAgilityCompound();
};

//***********************************************************
class IncreaseIntelligenceMethod1 : public HTNMethod
{
public:
	IncreaseIntelligenceMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseIntelligenceMethod2 : public HTNMethod
{
public:
	IncreaseIntelligenceMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseIntelligenceCompound : public HTNCompound
{
public:
	IncreaseIntelligenceCompound();
};

//***********************************************************
class GetItemMethod1 : public HTNMethod
{
	EItemType m_itemType;
public:
	GetItemMethod1(EItemType itemType);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GetItemMethod2 : public HTNMethod
{
    UPlayerData* m_player;
    EItemType m_itemType;
public:
    GetItemMethod2(UPlayerData* player, EItemType itemType);
    bool Preconditions(HTNWorldState &htnWorldState) override;
};

class GetItemCompound : public HTNCompound
{
public:
    GetItemCompound(HTNWorldState &htnWorldState, EItemType itemType);
};

//***********************************************************
class BringItemToLocationMethod1 : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
	BringItemToLocationMethod1(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class BringItemToLocationMethod2 : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
	BringItemToLocationMethod2(EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class BringItemToLocationMethod3 : public HTNMethod
{
	EItemType m_itemType;
	LocationClass& m_locationClass;
public:
    BringItemToLocationMethod3(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class BringItemToLocationCompound : public HTNCompound
{
public:
    BringItemToLocationCompound(HTNWorldState &htnWorldState, EItemType itemType, LocationClass &locationClass);
};

//***********************************************************
class AttackMethod1 : public HTNMethod
{
	SimActorItem* m_item;
	UPlayerData* m_opponent;
public:
	AttackMethod1(SimActorItem* item, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class AttackMethod2 : public HTNMethod
{
	UPlayerData* m_opponent;
public:
	AttackMethod2(UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class AttackCompound : public HTNCompound
{
public:
	AttackCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
};

class AttackCompoundMethod : public HTNMethod
{
public:
	AttackCompoundMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class DoMissionMethod1 : public HTNMethod
{
public:
	DoMissionMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DoMissionMethod2 : public HTNMethod
{
public:
	DoMissionMethod2();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DoMissionMethod3 : public HTNMethod
{
public:
	DoMissionMethod3();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DoMissionMethod4 : public HTNMethod
{
public:
	DoMissionMethod4(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DoMissionCompound : public HTNCompound
{
public:
	DoMissionCompound(HTNWorldState &htnWorldState);
};

//***********************************************************
class EvadeMethod : public HTNMethod
{
public:
	EvadeMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class CombatCompound : public HTNCompound
{
public:
	CombatCompound(HTNWorldState &htnWorldState, UPlayerData* opponent);
};

//***********************************************************
class CombatMethod : public HTNMethod
{
public:
	CombatMethod(HTNWorldState &htnWorldState, UPlayerData* opponent);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class DoMissionMethod : public HTNMethod
{
public:
	DoMissionMethod(HTNWorldState &htnWorldState);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

class IncreaseIntelligenceMethod : public HTNMethod
{
public:
	IncreaseIntelligenceMethod();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class PickUpItemMethod1 : public HTNMethod
{
public:
	PickUpItemMethod1(SimActorItem* itemFocus);
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class DropItemMethod1 : public HTNMethod
{
public:
	DropItemMethod1();
	bool Preconditions(HTNWorldState &htnWorldState) override;
};

//***********************************************************
class PrisonerBehaviourCompound : public HTNCompound
{
public:
	PrisonerBehaviourCompound(HTNWorldState &htnWorldState);
};
