#include "AICharacterC.h"
#include "HTNWorldState.hpp"
#include "Engine/GameEngine.h"


// Sets default values
AAICharacterC::AAICharacterC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacterC::BeginPlay()
{
	Super::BeginPlay();
	missionClass = MissionClass(this);
}

// Called every frame
void AAICharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (missionClass.IsMissionComplete())
	{
		missionClass.m_mission = Missions::noMission;
		UE_LOG(LogTemp, Warning, TEXT("Mission complete"));
	}

	if (readyForNewAction)
	{
		readyForNewAction = false;
		action = htnAIChooseAction(this);
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HTN Planner chose an action"));
		switch (action)
		{
		case Actions::attack:
			//AttackPlayer();
			break;
		case Actions::dropItem:
			DropItem();
			break;
		case Actions::evade:
			Evade();
			break;
		case Actions::goToBedroom:
			GoToLocation(3);
			break;
		case Actions::goToCircuitTrack:
			GoToLocation(4);
			break;
		case Actions::goToGym:
			GoToLocation(1);
			break;
		case Actions::goToLibrary:
			GoToLocation(2);
			break;
		case Actions::goToMainHall:
			GoToLocation(0);
			break;
		case Actions::pickUpItem:
			PickUpItem(m_itemFocusPtr);
			break;
		case Actions::useRoom:
			UseRoom();
			break;
		default:
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
	locationClass.location = static_cast<Locations>(locationAsInt);
}

void AAICharacterC::UpdateItemLocation(AActor* actor, int locationAsInt)
{
	for (auto &item : m_items)
	{
		if (item->m_unrealItem == actor)
		{
			item->m_locationClass.location = static_cast<Locations>(locationAsInt);
			break;
		}
	}
	for (auto &item : m_items)
	{
		//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("itemtype %d in location %d"), static_cast<int>(item->m_itemType), static_cast<int>(item->m_locationClass.location)));
	}
}

void AAICharacterC::AddItem(AActor* actor)
{
	m_items.push_back(new SimActorItem(ItemType::sword, Locations::mainHall, actor, (m_carriedItem==actor) ? this : nullptr ));
	if (GEngine)
	{
		for (auto &item : m_items)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("itemtype %d in location %d"), static_cast<int>(item->m_itemType), static_cast<int>(item->m_locationClass.location)));
		}
	}
}

void AAICharacterC::UpdateCarriedItemC(AActor* item, ACharacter* character)
{
	if (character == this)
	{
		m_carriedItem = item;
	}

	if (item == nullptr)
	{
		for (auto &m_item : m_items)
		{
			if (m_item->m_carryingPlayer == character)
			{
				m_item->m_carryingPlayer = nullptr;
				break;
			}
		}
	}
	else
	{
		for (auto &m_item : m_items)
		{
			if (m_item->m_unrealItem == item)
			{
				m_item->m_carryingPlayer = character;
				break;
			}
		}
	}
}
