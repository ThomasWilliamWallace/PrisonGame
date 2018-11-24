#include "AICharacterC.h"
#include "HTNWorldState.hpp"
#include "pLog.hpp"
#include "Engine/GameEngine.h"


// Sets default values
AAICharacterC::AAICharacterC(): lastPrimitiveAction(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_player = CreateDefaultSubobject<UPlayerData>(TEXT("PlayerData"));
}

// Called when the game starts or when spawned
void AAICharacterC::BeginPlay()
{
	Super::BeginPlay();
	m_player->missionClass = MissionClass(m_player);
	m_player->m_playerIndex = 0;
}

// Called every frame
void AAICharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_player->missionClass.IsMissionComplete(*m_world))
	{
		m_player->missionClass.m_mission = Missions::noMission;
		pLog("Mission complete", true);
	}

	if (readyForNewAction)
	{
		m_player->PrintPlayer();
		readyForNewAction = false;
		m_player->action = m_player->aiController.HTNAIChooseAction(this);
		pLog("HTN Planner chose an action:", true);
		switch (m_player->action)
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
			PickUpItem(m_player->itemFocusPtr);
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

void AAICharacterC::SetWorld(USimWorld* simWorld)
{
	pLog("AAICharacterC::SetWorld", true);
	m_world = simWorld;
	std::stringstream ss;
	ss << "World in:" << simWorld << "\n";
	ss << "World set" << m_world;
	pLog(ss, true);
}

USimWorld* AAICharacterC::GetSimWorld()
{
	pLog("AAICharacterC::GetSimWorld", true);
	std::stringstream ss;
	ss << "World get " << m_world;
	pLog(ss, true);
	return m_world;
}

void AAICharacterC::UpdateLocation(ELocations location)
{
	pLog("AAICharacterC::UpdateLocation", true);
	m_player->locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss, true);
}