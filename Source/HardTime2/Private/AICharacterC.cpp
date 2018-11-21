#include "AICharacterC.h"
#include "HTNWorldState.hpp"
#include "pLog.hpp"
#include "Engine/GameEngine.h"


// Sets default values
AAICharacterC::AAICharacterC(): lastPrimitiveAction(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacterC::BeginPlay()
{
	Super::BeginPlay();
	m_player.missionClass = MissionClass(&m_player);
}

// Called every frame
void AAICharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_player.missionClass.IsMissionComplete(m_world))
	{
		m_player.missionClass.m_mission = Missions::noMission;
		pLog("Mission complete", true);
	}

	if (readyForNewAction)
	{
		m_player.PrintPlayer();
		readyForNewAction = false;
		m_player.action = m_player.aiController.HTNAIChooseAction(this);
		pLog("HTN Planner chose an action:", true);
		switch (m_player.action)
		{
		case Actions::attack:
			//AttackPlayer();
			pLog("attack", true);
			break;
		case Actions::dropItem:
			pLog("dropItem", true);
			DropItem();
			break;
		case Actions::evade:
			pLog("evade", true);
			Evade();
			break;
		case Actions::goToBedroom:
			pLog("goToBedroom", true);
			GoToLocation(ELocations::bedroom);
			break;
		case Actions::goToCircuitTrack:
			pLog("goToCircuitTrack", true);
			GoToLocation(ELocations::circuitTrack);
			break;
		case Actions::goToGym:
			pLog("goToGym", true);
			GoToLocation(ELocations::gym);
			break;
		case Actions::goToLibrary:
			pLog("goToLibrary", true);
			GoToLocation(ELocations::library);
			break;
		case Actions::goToMainHall:
			pLog("goToMainHall", true);
			GoToLocation(ELocations::mainHall);
			break;
		case Actions::pickUpItem:
			pLog("pickUpItem", true);
			PickUpItem(m_player.itemFocusPtr);
			break;
		case Actions::useRoom:
			pLog("useRoom", true);
			UseRoom();
			break;
		default:
			pLog("NoAction", true);
			readyForNewAction = true;
			break;
		}
	}
}

// Called to bind functionality to input
void AAICharacterC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacterC::UpdateLocation(ELocations location)
{
	pLog("AAICharacterC::UpdateLocation", true);
	m_player.locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss, true);
}

void AAICharacterC::UpdateItemLocation(AActorItem* item, ELocations location)
{
	pLog("AAICharacterC::UpdateItemLocation", true);
	item->m_locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss, true);
}

void AAICharacterC::AddItem(AActorItem* item)
{
	pLog("AAICharacterC::AddItem", true);
	m_world.items.push_back(item);
	std::stringstream ss;
	ss << "item=" << item;
	pLog(ss, true);
}

void AAICharacterC::UpdateCarriedItemC(AActorItem* item, ACharacter* character)
{
	pLog("AAICharacterC::UpdateCarriedItemC", true);
	std::stringstream ss;
	ss << "item=" << item << ", character=" << character;
	pLog(ss, true);

	if (character == nullptr)
	{
		if (item != nullptr)
		{
			item->m_carryingPlayer = nullptr;
		}
		return;
	}

	AAICharacterC* aiCharacterC = Cast<AAICharacterC>(character);
	if (aiCharacterC == nullptr)
	{
		return;
	}

	if (character == this)
	{
		m_player.itemPtr = item;
	}

	if (item == nullptr)
	{
		for (auto &m_item : m_world.items)
		{
			if (m_item->m_carryingPlayer == &(aiCharacterC->m_player))
			{
				m_item->m_carryingPlayer = nullptr;
				break;
			}
		}
	}
	else
	{
		item->m_carryingPlayer = &(aiCharacterC->m_player);
	}
}
