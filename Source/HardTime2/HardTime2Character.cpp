// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HardTime2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HTNWorldState.hpp"
#include "pLog.hpp"
#include "Engine/GameEngine.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "HardTime2GameMode.h"

//////////////////////////////////////////////////////////////////////////
// AHardTime2Character

AHardTime2Character::AHardTime2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_player = CreateDefaultSubobject<UPlayerData>(TEXT("PlayerData"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHardTime2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHardTime2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHardTime2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHardTime2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHardTime2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHardTime2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHardTime2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHardTime2Character::OnResetVR);
}


void AHardTime2Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHardTime2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AHardTime2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AHardTime2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHardTime2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHardTime2Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHardTime2Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Called when the game starts or when spawned
void AHardTime2Character::BeginPlay()
{
	Super::BeginPlay();
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
void AHardTime2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_player->UpdateMissions(*m_world);

	if (m_player->aiController.algo == AI::htnAI && readyForNewAction)
	{
		m_player->PrintPlayer();
		readyForNewAction = false;
		m_player->action = m_player->aiController.HTNAIChooseAction(m_player, m_world);
		m_player->aiController.lastActionInterrupted = false;
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

void AHardTime2Character::SetWorld(USimWorld* simWorld)
{
	pLog("AHardTime2Character::SetWorld", true);
	m_world = simWorld;
	std::stringstream ss;
	ss << "World in:" << simWorld << "\n";
	ss << "World set" << m_world;
	pLog(ss);
}

USimWorld* AHardTime2Character::GetSimWorld()
{
	pLog("AHardTime2Character::GetSimWorld", true);
	std::stringstream ss;
	ss << "World get " << m_world;
	pLog(ss, true);
	return m_world;
}

void AHardTime2Character::UpdateLocation(ELocations location)
{
	pLog("AHardTime2Character::UpdateLocation", true);
	m_player->locationClass.location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss);
}

void AHardTime2Character::DeltaHealth(float delta)
{
	pLog("AHardTime2Character::DeltaHealth", true);
	std::stringstream ss;
	m_player->pStats.deltaHealth(delta);
	ss << "m_player->pStats.getHealth():" << m_player->pStats.getHealth() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaStrength(float delta)
{
	pLog("AHardTime2Character::DeltaStrength", true);
	std::stringstream ss;
	m_player->pStats.deltaStrength(delta);
	ss << "m_player->pStats.getStrength():" << m_player->pStats.getStrength() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaAgility(float delta)
{
	pLog("AHardTime2Character::DeltaAgility", true);
	std::stringstream ss;
	m_player->pStats.deltaAgility(delta);
	ss << "m_player->pStats.getAgility():" << m_player->pStats.getAgility() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaIntelligence(float delta)
{
	pLog("AHardTime2Character::DeltaIntelligence", true);
	std::stringstream ss;
	m_player->pStats.deltaIntelligence(delta);
	ss << "m_player->pStats.getIntelligence():" << m_player->pStats.getIntelligence() << "\n";
	pLog(ss);
}

void AHardTime2Character::SetLastActionInterrupted()
{
	pLog("AAICharacterC::SetLastActionInterrupted", true);
	m_player->aiController.lastActionInterrupted = true;
}

void AHardTime2Character::BeginDestroy()
{
	Super::BeginDestroy();
	if (GetWorld() == nullptr)
	{
		pLog("ERROR: AHardTime2Character::BeginDestroy, GetWorld() is nullptr");
		return;
	}
	auto gameMode = GetWorld()->GetAuthGameMode();
	if (gameMode == nullptr)
	{
		pLog("ERROR: AHardTime2Character::BeginDestroy, gameMode is nullptr");
		return;
	}
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	if (hardTime2GameMode == nullptr)
	{
		pLog("ERROR: AHardTime2Character::BeginDestroy, hardTime2GameMode is nullptr");
		return;
	}
	if (hardTime2GameMode->m_simWorld == nullptr)
	{
		pLog("ERROR: AHardTime2Character::BeginDestroy, hardTime2GameMode->m_simWorld is nullptr");
		return;
	}
	hardTime2GameMode->m_simWorld->RemovePlayer(this->m_player);
}