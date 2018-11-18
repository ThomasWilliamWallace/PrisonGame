#include "AICharacterC.h"
#include "HTNWorldState.hpp"
#include <iostream>
#include "pLog.hpp"


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
		pLog("Mission complete");
	}

	if (readyForNewAction)
	{
		readyForNewAction = false;
		m_player.action = htnAIChooseAction(this);
		pLog("HTN Planner chose an action:");
		switch (m_player.action)
		{
		case Actions::attack:
			//AttackPlayer();
			pLog("attack");
			break;
		case Actions::dropItem:
			pLog("dropItem");
			DropItem();
			break;
		case Actions::evade:
			pLog("evade");
			Evade();
			break;
		case Actions::goToBedroom:
			pLog("goToBedroom");
			GoToLocation(3);
			break;
		case Actions::goToCircuitTrack:
			pLog("goToCircuitTrack");
			GoToLocation(4);
			break;
		case Actions::goToGym:
			pLog("goToGym");
			GoToLocation(1);
			break;
		case Actions::goToLibrary:
			pLog("goToLibrary");
			GoToLocation(2);
			break;
		case Actions::goToMainHall:
			pLog("goToMainHall");
			GoToLocation(0);
			break;
		case Actions::pickUpItem:
			pLog("pickUpItem");
			PickUpItem(m_player.itemFocusPtr);
			break;
		case Actions::useRoom:
			pLog("useRoom");
			UseRoom();
			break;
		default:
			pLog("NoAction");
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

void AAICharacterC::UpdateLocation(int locationAsInt)
{
	pLog("AAICharacterC::UpdateLocation");
	m_player.locationClass.location = static_cast<Locations>(locationAsInt);
}

void AAICharacterC::UpdateItemLocation(AActorItem* item, int locationAsInt)
{
	pLog("AAICharacterC::UpdateItemLocation");
	for (auto &i : m_world.items)
	{
		if (i == item)
		{
			i->m_locationClass.location = static_cast<Locations>(locationAsInt);
			break;
		}
	}
	for (auto &i : m_world.items)
	{
		//std::string itemPrint = "itemtype " + static_cast<int>(item->m_itemType) + " in location " + static_cast<int>(item->m_locationClass.location;
		//pLog(itemPrint);
	}
}

void AAICharacterC::AddItem(AActorItem* item)
{
	pLog("AAICharacterC::AddItem");
	m_world.items.push_back(item);
	//for (auto &i : m_world.items)
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("itemtype %d in location %d"), static_cast<int>(i->m_itemType), static_cast<int>(item->m_locationClass.location)));
	//}
}

void AAICharacterC::UpdateCarriedItemC(AActorItem* item, ACharacter* character)
{
	pLog("AAICharacterC::UpdateCarriedItemC");
	AAICharacterC* aiCharacterC = Cast<AAICharacterC>(character);
	if (aiCharacterC == nullptr)
	{
		return;
	}

	if (&(aiCharacterC->m_player) == &(m_player))
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
		for (auto &m_item : m_world.items)
		{
			if (m_item == item)
			{
				m_item->m_carryingPlayer = &(aiCharacterC->m_player);
				break; 
			}
		}
	}
}
