#include "AICharacterC.h"
#include "HTNWorldState.hpp"
#include "pLog.hpp"
#include "Engine/GameEngine.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "HardTime2GameMode.h"


// Sets default values
AAICharacterC::AAICharacterC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_player = CreateDefaultSubobject<UPlayerData>(TEXT("PlayerData"));
}

// Called when the game starts or when spawned
void AAICharacterC::BeginPlay()
{
	Super::BeginPlay();
	if (m_player == nullptr)
		pLog("ERROR: M_PLAYER IS NULL DURING AAICHARACTERC::BEGINPLAY", true);
	if (!IsValid(m_player))
		pLog("ERROR: M_PLAYER IS NOT VALID DURING AAICHARACTERC::BEGINPLAY", true);
	m_player->m_playerName = "No-name";
	m_player->missionClass = MissionClass(m_player);
	m_player->m_playerIndex = 0;
	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	m_player->m_playerIndex = hardTime2GameMode->m_simWorld->AddPlayer(this->m_player);

	m_player->aiController.algo = AI::htnAI;
	for (FConstPlayerControllerIterator iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		APlayerController* playerController = Cast<APlayerController>(*iterator);
		if (playerController != nullptr && playerController == GetController())
		{
			if (playerController->IsLocalController())
			{
				m_player->aiController.algo = AI::doNothingAI;
			}
		}
	}
}

// Called every frame
void AAICharacterC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	pLog("AAICharacterC::Tick", true);
	std::stringstream ss;
	ss << "m_player=" << m_player << "\n";
	ss << "m_world=" << m_world << "\n";
	pLog(ss, true);
	if (!IsValid(m_player))
	{
		pLog("ERROR: M_PLAYER IS NOT VALID DURING AAICHARACTERC::Tick", true);
		return;
	}
	if (!IsValid(m_world))
	{
		pLog("ERROR: M_WORLD IS NOT VALID DURING AAICHARACTERC::Tick", true);
		return;
	}
	if (m_player->missionClass.IsMissionComplete(*m_world))
	{
		m_player->missionClass.m_mission = Missions::noMission;
		pLog("********************** Mission complete, creating new mission:", true);
		m_player->missionClass = MissionClass(m_player);
		pLog(m_player->missionClass.MissionNarrative(), true);
	}

	if (m_player->aiController.algo == AI::htnAI && readyForNewAction)
	{
		m_player->PrintPlayer();
		readyForNewAction = false;
		m_player->action = m_player->aiController.HTNAIChooseAction(m_player, m_world, lastActionSucceeded);
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
	pLog(ss);
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
	pLog(ss);
}

void AAICharacterC::DeltaHealth(float delta)
{
	pLog("AAICharacterC::DeltaHealth", true);
	std::stringstream ss;
	m_player->pStats.deltaHealth(delta);
	ss << "m_player->pStats.getHealth():" << m_player->pStats.getHealth() << "\n";
	pLog(ss);
}

void AAICharacterC::DeltaStrength(float delta)
{
	pLog("AAICharacterC::DeltaStrength", true);
	std::stringstream ss;
	m_player->pStats.deltaStrength(delta);
	ss << "m_player->pStats.getStrength():" << m_player->pStats.getStrength() << "\n";
	pLog(ss);
}

void AAICharacterC::DeltaAgility(float delta)
{
	pLog("AAICharacterC::DeltaAgility", true);
	std::stringstream ss;
	m_player->pStats.deltaAgility(delta);
	ss << "m_player->pStats.getAgility():" << m_player->pStats.getAgility() << "\n";
	pLog(ss);
}

void AAICharacterC::DeltaIntelligence(float delta)
{
	pLog("AAICharacterC::DeltaIntelligence", true);
	std::stringstream ss;
	m_player->pStats.deltaIntelligence(delta);
	ss << "m_player->pStats.getIntelligence():" << m_player->pStats.getIntelligence() << "\n";
	pLog(ss);
}