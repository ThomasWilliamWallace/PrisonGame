// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HardTime2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HTNWorldState.h"
#include "pLog.h"
#include "Names.h"
#include "Engine/GameEngine.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "HardTime2GameMode.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Core/Public/Internationalization/Text.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "PlatformSpecificForPlanner.h"

//////////////////////////////////////////////////////////////////////////
// AHardTime2Character

void AHardTime2Character::InitCamera()
{
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AHardTime2Character::InitCameraBoom()
{
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
}

void AHardTime2Character::Init()
{
	pLog("AHardTime2Character::Init");

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_carriedItem = nullptr;
	m_aiCommand = EAICommand::useRoom;
	m_aiState = EAIState::noTask;
	m_useCount = 0;

	m_player->missionClass = std::make_shared<MissionClass>(m_player);
	m_player->physicalCharacter = this;
	m_player->aiController.algo = AI::htnAI;
	m_player->aiController.lastActionInterrupted = false;

	std::string playerName = RandomName();
	m_player->m_playerName = FName(playerName.c_str());

	m_player->PrintPlayer();
}

AHardTime2Character::AHardTime2Character(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	pLog("AHardTime2Character::AHardTime2Character with FObjectInitializer");
	
	if (CameraBoom == nullptr)
	{
		// Create a camera boom (pulls in towards the player if there is a collision)
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	}
	InitCameraBoom();

	if (FollowCamera == nullptr)
	{
		// Create a follow camera
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	}
	InitCamera();

	
	if (m_player == nullptr)
	{
		m_player = CreateDefaultSubobject<UPlayerData>(TEXT("PlayerData"));
	}

	Init();
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
	pLog("AHardTime2Character::BeginPlay before SUPER");
	Super::BeginPlay();

	pLog("AHardTime2Character::BeginPlay after SUPER");

	/*
	if (CameraBoom == nullptr)
	{
		pLog("Constructing a CameraBoom");
		// Create a camera boom (pulls in towards the player if there is a collision)
		CameraBoom = NewObject<USpringArmComponent>();
	}
	InitCameraBoom();

	if (FollowCamera == nullptr)
	{
		pLog("Constructing a FollowCamera");
		// Create a follow camera
		FollowCamera = NewObject<UCameraComponent>();
	}
	InitCamera();
	*/
	if (m_player == nullptr)
	{
		pLog("Constructing an m_player");
		m_player = NewObject<UPlayerData>(this);
	}

	Init();

	pLog("Registering player with the worldState.");
	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	hardTime2GameMode->m_simWorld->AddPlayer(this->m_player);

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

void AHardTime2Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Remove delegates
	//AAIController* controller = Cast<AAIController>(GetController());
	//if (controller == nullptr)
	//	throw std::invalid_argument("Cannot remove delegates because controller is NULL.");
	//controller->GetPathFollowingComponent()->OnRequestFinished.Remove(pickUpItemMoveDelegateHandle);
	//controller->GetPathFollowingComponent()->OnRequestFinished.Remove(goToLocationMoveDelegateHandle);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	pLog("De-registering player from the worldState.");
	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	hardTime2GameMode->m_simWorld->RemovePlayer(this->m_player);
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
	if (m_player == nullptr)
	{
		pLog("M_PLAYER == NULLPTR, FAILED TO UPDATE LOCATION");
		return;
	}
	m_player->locationClass.location = location;
	m_location = location;
	std::stringstream ss;
	ss << "Location=" << static_cast<int>(location);
	pLog(ss);
}

void AHardTime2Character::DeltaHealth(float delta)
{
	pLog("AHardTime2Character::DeltaHealth", true);
	std::stringstream ss;
	m_player->pStats->deltaHealth(delta);
	ss << "m_player->abstractPlayerData.pStats.getHealth():" << m_player->pStats->getHealth() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaStrength(float delta)
{
	pLog("AHardTime2Character::DeltaStrength", true);
	std::stringstream ss;
	m_player->pStats->deltaStrength(delta);
	ss << "m_player->abstractPlayerData.pStats.getStrength():" << m_player->pStats->getStrength() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaAgility(float delta)
{
	pLog("AHardTime2Character::DeltaAgility", true);
	std::stringstream ss;
	m_player->pStats->deltaAgility(delta);
	ss << "m_player->abstractPlayerData.pStats.getAgility():" << m_player->pStats->getAgility() << "\n";
	pLog(ss);
}

void AHardTime2Character::DeltaIntelligence(float delta)
{
	pLog("AHardTime2Character::DeltaIntelligence", true);
	std::stringstream ss;
	m_player->pStats->deltaIntelligence(delta);
	ss << "m_player->abstractPlayerData.pStats.getIntelligence():" << m_player->pStats->getIntelligence() << "\n";
	pLog(ss);
}

void AHardTime2Character::SetLastActionInterrupted(bool interrupted)
{
	if (interrupted)
		pLog("AHARDTIME2CHARACTER::SetLastActionInterrupted(True)", true);
	else
		pLog("AHARDTIME2CHARACTER::SetLastActionInterrupted(False)", true);
	m_player->aiController.lastActionInterrupted = interrupted;
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

void AHardTime2Character::GoToLocation(ELocations location)
{
	switch (location)
	{
	case (ELocations::mainHall):
		m_targetLocation = m_mainHall;
		break;
	case (ELocations::gym):
		m_targetLocation = m_gym;
		break;
	case (ELocations::circuitTrack):
		m_targetLocation = m_circuitTrack;
		break;
	case (ELocations::library):
		m_targetLocation = m_library;
		break;
	case (ELocations::bedroom):
		m_targetLocation = m_bedroom;
		break;
	}
	m_aiCommand = EAICommand::goToLocation;
	m_aiState = EAIState::newCommand;
	UpdateStatus();
}

void AHardTime2Character::PickUpItemByPtr(std::shared_ptr<BaseAction> baseAction)
{
	PickUpItemByPtrAction* pickUpItemByPtrAction = static_cast<PickUpItemByPtrAction*>(baseAction.get());
	AActorItem* m_realItem = static_cast<AActorItem*>(pickUpItemByPtrAction->m_itemFocusPtr);
	m_targetItem = m_realItem;
	m_aiCommand = EAICommand::pickupItem;
	m_aiState = EAIState::newCommand;
	UpdateStatus();
}

void AHardTime2Character::DropItem()
{
	m_aiCommand = EAICommand::dropItem;
	m_aiState = EAIState::newCommand;
	UpdateStatus();
}

void AHardTime2Character::UseRoom()
{
	m_aiCommand = EAICommand::useRoom;
	m_aiState = EAIState::newCommand;
	UpdateStatus();
}

void AHardTime2Character::RequestItem(std::shared_ptr<BaseAction> baseAction)
{
	RequestItemAction* requestItemAction = static_cast<RequestItemAction*>(baseAction.get());

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHardTime2Character::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		AHardTime2Character* targetPlayer = static_cast<AHardTime2Character*>(actor);
		if (targetPlayer->m_player->m_key == requestItemAction->m_targetPlayer->m_key)
		{
			m_targetPlayer = targetPlayer;
			m_targetItem = m_targetPlayer->m_carriedItem;
			m_aiCommand = EAICommand::requestItem;
			m_aiState = EAIState::newCommand;
			UpdateStatus();
			return;
		}
	}
	ThrowException("Target player of RequestItemAction not found using key");
}

void AHardTime2Character::Attack(std::shared_ptr<BaseAction> baseAction)
{
	AttackAction* attackAction = static_cast<AttackAction*>(baseAction.get());

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHardTime2Character::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		AHardTime2Character* targetPlayer = static_cast<AHardTime2Character*>(actor);
		if (targetPlayer->m_player->m_key == attackAction->m_targetPlayer->m_key)
		{
			m_targetPlayer = targetPlayer;
			m_aiCommand = EAICommand::attack;
			m_aiState = EAIState::newCommand;
			UpdateStatus();
			return;
		}
	}
	ThrowException("Target player of AttackAction not found using key");
}

void AHardTime2Character::Evade(std::shared_ptr<BaseAction> baseAction)
{
	EvadeAction* evadeAction = static_cast<EvadeAction*>(baseAction.get());

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHardTime2Character::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		AHardTime2Character* targetPlayer = static_cast<AHardTime2Character*>(actor);
		if (targetPlayer->m_player->m_key == evadeAction->m_evadePlayer->m_key)
		{
			m_targetPlayer = targetPlayer;
			m_aiCommand = EAICommand::evade;
			m_aiState = EAIState::newCommand;
			UpdateStatus();
			return;
		}
	}
	ThrowException("Target player of evadeAction not found using key");
}

// Called every frame
void AHardTime2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStatus();
	m_player->UpdateMissions(*m_world);

	if (isStunned)
	{
		return;
	}

	//Planning
	if (m_player->aiController.algo == AI::htnAI && readyForNewAction)
	{
		m_player->PrintPlayer();
		readyForNewAction = false;
		m_player->lastAction = m_player->action;
		m_player->action = m_player->aiController.HTNAIChooseAction(m_player, m_world->m_playerRegistry->m_playerMap, m_world);
		m_player->aiController.lastActionInterrupted = false;
		pLog("HTN Planner chose an action:", true);
		if (m_player->action == nullptr) { ThrowException("Nullptr action returned by HTN planner"); }
		switch (m_player->action->m_action)
		{
		case EActions::goToBedroom:
			pLog("goToBedroom", true);
			GoToLocation(ELocations::bedroom);
			break;
		case EActions::goToCircuitTrack:
			pLog("goToCircuitTrack", true);
			GoToLocation(ELocations::circuitTrack);
			break;
		case EActions::goToGym:
			pLog("goToGym", true);
			GoToLocation(ELocations::gym);
			break;
		case EActions::goToLibrary:
			pLog("goToLibrary", true);
			GoToLocation(ELocations::library);
			break;
		case EActions::goToMainHall:
			pLog("goToMainHall", true);
			GoToLocation(ELocations::mainHall);
			break;
		case EActions::dropItem:
			pLog("dropItem", true);
			DropItem();
			break;
		case EActions::pickUpItemByPtr:
			pLog("pickUpItemByPtr", true);
			PickUpItemByPtr(m_player->action);
			break;
		case EActions::requestItem:
			pLog("requestItem", true);
			RequestItem(m_player->action);
			break;
		case EActions::useRoom:
			pLog("useRoom", true);
			UseRoom();
			break;
		case EActions::attack:
			pLog("attack", true);
			Attack(m_player->action);
			break;
		case EActions::evade:
			pLog("evade", true);
			Evade(m_player->action);
			break;
		default:
			pLog("NoAction", true);
			readyForNewAction = true;
			break;
		}
	}

	//Enact plan
	switch (m_aiState)
	{
	case EAIState::cooldown:
		OnCooldown();
		break;
	case EAIState::noTask:
		OnNoTask();
		break;
	case EAIState::commandInProgress:
		OnCommandInProgress();
		break;
	case EAIState::newCommand:
		OnNewCommand();
		break;
	case EAIState::usingRoom:
		OnUsingRoom();
		break;
	default:
		throw std::invalid_argument("EAIState not recognized.");
	}
}

void AHardTime2Character::OnCooldown_Implementation()
{
	if (!GetWorldTimerManager().IsTimerActive(cooldownTimerHandle))
	{
		pLog("set cooldown timer");
		GetWorldTimerManager().SetTimer(
			cooldownTimerHandle, this, &AHardTime2Character::CooldownTimerElapsed, 0.5f, false);
	}
}

void AHardTime2Character::CooldownTimerElapsed()
{
	pLog("ENTERING CooldownTimerElapsed");
	GetWorldTimerManager().ClearTimer(cooldownTimerHandle);
	if (m_aiState == EAIState::cooldown)
	{
		pLog("move from cooldown state to noTask state");
		readyForNewAction = true;
		m_aiState = EAIState::noTask;
		UpdateStatus();
		readyForNewAction = true;
	}
}

void AHardTime2Character::OnCommandInProgress_Implementation()
{}

void AHardTime2Character::OnNoTask_Implementation()
{}

void AHardTime2Character::OnNewCommand_Implementation()
{
	pLog("Entering AHardTime2Character::OnNewCommand_Implementation");
	AAIController* controller;
	switch (m_aiCommand)
	{
		case EAICommand::dropItem:
			if (m_carriedItem != nullptr)
			{
				DoDropItemAction();
			}
			m_aiState = EAIState::cooldown;
			UpdateStatus();
			break;
		case EAICommand::goToLocation:
			pLog("EAICommand::goToLocation", true);
			if (m_targetLocation != nullptr)
			{
				pLog("ATTEMPTING TO GO TO LOCATION!");
				m_aiState = EAIState::commandInProgress;
				controller = Cast<AAIController>(GetController());
				if (controller != nullptr)
				{
					FAIMoveRequest req;
					req.SetAcceptanceRadius(50);
					req.SetUsePathfinding(true);
					req.SetGoalActor(m_targetLocation);
					controller->MoveTo(req);

					goToLocationMoveDelegateHandle = controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AHardTime2Character::GoToLocationMoveCompleted);
				}
				else
					throw std::invalid_argument("Failed to cast character controller as AIController.");
			} else {
				m_aiState = EAIState::cooldown;
			}
			UpdateStatus();
			break;
		case EAICommand::pickupItem:
			pLog("ENTERING EAICommand::pickupItem", true);
			if (m_targetItem != nullptr)
			{
				pLog("ATTEMPTING TO GO TO ITEM!");
				m_aiState = EAIState::commandInProgress;
				controller = Cast<AAIController>(GetController());
				if (controller != nullptr)
				{
					pickUpItemMoveDelegateHandle = controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AHardTime2Character::PickUpItemMoveCompleted);
				
					FAIMoveRequest req;
					req.SetAcceptanceRadius(30);
					req.SetUsePathfinding(true);
					req.SetGoalActor(m_targetItem);
					UActorComponent* targetItemMeshActorComponent = m_targetItem->GetComponentByClass(UStaticMeshComponent::StaticClass());
					UStaticMeshComponent* targetItemMeshComp = Cast<UStaticMeshComponent>(targetItemMeshActorComponent);
					req.SetGoalLocation(targetItemMeshComp->GetComponentLocation());
					controller->MoveTo(req);
				}
				else
					throw std::invalid_argument("Failed to cast character controller as AIController.");
			} else {
				m_aiState = EAIState::cooldown;
			}
			UpdateStatus();
			break;
		case EAICommand::useRoom:
			m_useCount = 0;
			m_aiState = EAIState::usingRoom;
			break;
		case EAICommand::requestItem:
			pLog("EAICommand::requestItem", true);
			if (m_targetPlayer->m_carriedItem != nullptr)
			{
				pLog("ATTEMPTING TO GO TO PLAYER!");
				controller = Cast<AAIController>(GetController());
				if (controller != nullptr)
				{
					m_aiState = EAIState::commandInProgress;

					requestItemMoveDelegateHandle = controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AHardTime2Character::RequestItemMoveCompleted);

					FAIMoveRequest req;
					req.SetAcceptanceRadius(20);
					req.SetUsePathfinding(true);
					req.SetGoalActor(m_targetPlayer);
					controller->MoveTo(req);
				}
				else
					throw std::invalid_argument("Failed to cast character controller as AIController.");
			}
			else {
				m_aiState = EAIState::cooldown;
				pLog("m_aiState = EAIState::cooldown;", true);
			}
			UpdateStatus();
			break;
		case EAICommand::attack:
			pLog("ATTEMPTING TO CHASE PLAYER FOR ATTACK!");
			controller = Cast<AAIController>(GetController());
			if (controller != nullptr)
			{
				m_aiState = EAIState::commandInProgress;

				attackMoveDelegateHandle = controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AHardTime2Character::AttackMoveCompleted);

				FAIMoveRequest req;
				req.SetAcceptanceRadius(20);
				req.SetUsePathfinding(true);
				req.SetGoalActor(m_targetPlayer);
				controller->MoveTo(req);
			}
			else
				throw std::invalid_argument("Failed to cast character controller as AIController.");
			break;
		case EAICommand::evade:
			pLog("ATTEMPTING TO EVADE");
			TriggerEvadeBehaviour(m_targetPlayer);
			m_aiState = EAIState::commandInProgress;
			break;
		default:
			throw std::invalid_argument("Unrecognised AI command.");
	}
}

void AHardTime2Character::GoToLocationMoveCompleted(FAIRequestID a, const FPathFollowingResult &b)
{
	pLog("GoToLocationMoveCompleted", true);

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller == nullptr)
		throw std::invalid_argument("Cannot unbind goToLocationMoveDelegateHandle because controller is NULL.");
	controller->GetPathFollowingComponent()->OnRequestFinished.Remove(goToLocationMoveDelegateHandle);

	if (b.IsSuccess())
	{
		m_aiState = EAIState::cooldown;
	} else {
		m_aiState = EAIState::noTask;
	}
	UpdateStatus();
}

void AHardTime2Character::PickUpItemMoveCompleted(FAIRequestID a, const FPathFollowingResult &b)
{
	pLog("PickUpItemMoveCompleted", true);

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller == nullptr)
		throw std::invalid_argument("Cannot unbind pickUpItemMoveDelegateHandle because controller is NULL.");
	controller->GetPathFollowingComponent()->OnRequestFinished.Remove(pickUpItemMoveDelegateHandle);

	m_aiState = EAIState::cooldown;
	UpdateStatus();
	DoPickupItemAction(m_targetItem);
}

void AHardTime2Character::RequestItemMoveCompleted(FAIRequestID a, const FPathFollowingResult &b)
{
	pLog("RequestItemMoveCompleted", true);

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller == nullptr)
		throw std::invalid_argument("Cannot unbind requestItemMoveDelegateHandle because controller is NULL.");
	controller->GetPathFollowingComponent()->OnRequestFinished.Remove(requestItemMoveDelegateHandle);

	m_aiState = EAIState::commandInProgress;
	UpdateStatus();
	DoRequestItemAction(m_targetPlayer);
}

void AHardTime2Character::AttackMoveCompleted(FAIRequestID a, const FPathFollowingResult& b)
{
	pLog("AttackMoveCompleted", true);

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller == nullptr)
		throw std::invalid_argument("Cannot unbind attackMoveDelegateHandle because controller is NULL.");
	controller->GetPathFollowingComponent()->OnRequestFinished.Remove(attackMoveDelegateHandle);

	m_aiState = EAIState::commandInProgress;
	UpdateStatus();
	DoAttackActionUnreal(m_targetPlayer);
}

void AHardTime2Character::EvadeMoveCompleted(FAIRequestID a, const FPathFollowingResult& b)
{
	pLog("EvadeMoveCompleted", true);

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller == nullptr)
		throw std::invalid_argument("Cannot unbind evadeMoveDelegateHandle because controller is NULL.");
	controller->GetPathFollowingComponent()->OnRequestFinished.Remove(evadeMoveDelegateHandle);

	m_aiState = EAIState::noTask;
	UpdateStatus();
}

void AHardTime2Character::OnUsingRoom_Implementation()
{
	pLog("ENTERING OnUsingRoom_Implementation");
	if (m_useCount >= 4)
	{
		pLog("m_useCount >= 4");
		m_aiState = EAIState::cooldown;
		UpdateStatus();
	} else {
		pLog("m_useCount < 4");
		Jump();
		switch (m_location)
		{
			case ELocations::bedroom:
				DeltaHealth(1);
				break;
			case ELocations::circuitTrack:
				DeltaAgility(1);
				break;
			case ELocations::gym:
				DeltaStrength(1);
				break;
			case ELocations::library:
				DeltaIntelligence(1);
				break;
			case ELocations::mainHall:
				m_aiState = EAIState::cooldown;
				UpdateStatus();
				pLog("Tried to use main hall and failed.", true);
				return;
			default:
				throw std::invalid_argument("Location not recognised when using room");
		}
		m_useCount += 1;
		m_aiState = EAIState::commandInProgress;
		UpdateStatus();

		pLog("About to try and set timer");
		if (!GetWorldTimerManager().IsTimerActive(usingRoomTimerHandle))
		{
			GetWorldTimerManager().SetTimer(
				usingRoomTimerHandle, this, &AHardTime2Character::UsingRoomTimerElapsed, 1.4, false);
			pLog("Timer was set successfully!");
		}
	}
}

void AHardTime2Character::UsingRoomTimerElapsed()
{
	pLog("ENTERING UsingRoomTimerElapsed");
	GetWorldTimerManager().ClearTimer(usingRoomTimerHandle);
	if (!(m_player->aiController.lastActionInterrupted))
	{
		m_aiState = EAIState::usingRoom;
	} else {
		pLog("using room interrupted!");
		m_aiState = EAIState::cooldown;
	}
	UpdateStatus();
}

void AHardTime2Character::UpdateStatus()
{
	FString status = "No status";
	status = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAIState"), true)->GetDisplayNameTextByIndex(static_cast<int32>(m_aiState)).ToString();
	status.Append(", ");
	status.Append(FindObject<UEnum>(ANY_PACKAGE, TEXT("EAICommand"), true)->GetDisplayNameTextByIndex(static_cast<int32>(m_aiCommand)).ToString());
	DisplayStatus(status);
}

void AHardTime2Character::DoPickupItemAction(AActorItem* item)
{
	if (m_carriedItem != nullptr) {
		DoDropItemAction();
	}
	if (item != nullptr && item->m_carryingPlayer != nullptr)
	{
		return;
	};
	bool canReachItem = false;
	if (item != nullptr) {
		UStaticMeshComponent* selfMeshComp = Cast<UStaticMeshComponent>(this->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		UStaticMeshComponent* targetItemMeshComp = Cast<UStaticMeshComponent>(item->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		float grabDistance = 500;
		float grabDistanceSquared = grabDistance * grabDistance;
		float itemDistanceSquared = (selfMeshComp->GetComponentLocation() - targetItemMeshComp->GetComponentLocation()).SizeSquared();
		if (itemDistanceSquared < grabDistanceSquared)
		{
			canReachItem = true;
		}
	}
	else {
        // Grab first item in reach
		TArray <AActor*> overlappingActors;
		GetOverlappingActors(overlappingActors, AActorItem::StaticClass());
		if (overlappingActors.Num() > 0) {
			item = static_cast<AActorItem*>(overlappingActors[0]);
			canReachItem = true;
		}
	}
	if (!canReachItem)
	{
		pLog("PickupItemAction: Couldn't reach item.", true);
		return;
	}
	UActorComponent* itemComp = item->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* itemMeshComp = Cast<UStaticMeshComponent>(itemComp);
	itemComp = item->GetComponentByClass(UCapsuleComponent::StaticClass());
	UCapsuleComponent* itemCapsule = Cast<UCapsuleComponent>(itemComp);

	itemMeshComp->SetSimulatePhysics(false);
	//itemCapsule->SetGenerateOverlapEvents(false);
	itemMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemMeshComp->SetGenerateOverlapEvents(false);
	itemMeshComp->IgnoreActorWhenMoving(this, true);

	USkeletalMeshComponent* skeletalMesh = GetMesh();
	UCapsuleComponent* capsule = GetCapsuleComponent();

	capsule->IgnoreActorWhenMoving(item, true);
	skeletalMesh->IgnoreActorWhenMoving(item, true);

	FName socketName = "itemSocket";
	FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	item->AttachToComponent(skeletalMesh, attachRules, socketName);

	m_carriedItem = item;
	if (item->m_carryingPlayer != nullptr)
	{
		if (item->m_carryingPlayer->physicalCharacter == nullptr)
		{
			throw std::invalid_argument("Cannot remove item from current carrying player. Physical character is NULL.");
		}
		item->m_carryingPlayer->physicalCharacter->m_carriedItem = nullptr;
	}
	item->m_carryingPlayer = this->m_player;

	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	if (hardTime2GameMode != nullptr)
	{
		hardTime2GameMode->m_simWorld->UpdateCarriedItem(m_carriedItem, this);
	}
	else {
		throw std::invalid_argument("Failed to cast gameMode to AHardTime2GameMode.");
	}
}

void AHardTime2Character::DoDropItemAction()
{
	if (m_carriedItem == nullptr)
	{
		pLog("DropItemAction: couldn't drop item as no item was being carried.", true);
		return;
	}
	UActorComponent* itemComp = m_carriedItem->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* itemMeshComp = Cast<UStaticMeshComponent>(itemComp);
	itemComp = m_carriedItem->GetComponentByClass(UCapsuleComponent::StaticClass());
	UCapsuleComponent* itemCapsule = Cast<UCapsuleComponent>(itemComp);

	FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, false);
	itemMeshComp->DetachFromComponent(rules);
	itemMeshComp->ClearMoveIgnoreActors();
	itemMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	itemMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	itemMeshComp->SetSimulatePhysics(true);
	itemMeshComp->SetGenerateOverlapEvents(true);
	//itemCapsule->SetGenerateOverlapEvents(true);

	USkeletalMeshComponent* skeletalMesh = GetMesh();
	UCapsuleComponent* capsule = GetCapsuleComponent();

	capsule->ClearMoveIgnoreActors();
	skeletalMesh->ClearMoveIgnoreActors();

	m_carriedItem->m_carryingPlayer = nullptr;
	m_carriedItem = nullptr;

	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	if (hardTime2GameMode != nullptr)
	{
		hardTime2GameMode->m_simWorld->UpdateCarriedItem(nullptr, this);
	}
	else {
		throw std::invalid_argument("Failed to cast gameMode to AHardTime2GameMode.");
	}
}

void AHardTime2Character::DoRequestItemAction(AHardTime2Character* targetCharacter)
{
	if (targetCharacter->m_carriedItem == nullptr)
	{
		pLog("RequestItemAction: character isn't carrying any item.", true);
		m_aiState = EAIState::cooldown;
		UpdateStatus();
		return;
	}

	FVector displacement = GetActorLocation() - targetCharacter->GetActorLocation();
	if (abs(displacement.Size()) > 500)
	{
		pLog("RequestItemAction: couldn't reach character.", true);
		m_aiState = EAIState::cooldown;
		UpdateStatus();
		return;
	}
	FString itemString(ItemTypeToString(targetCharacter->m_carriedItem->m_itemType).c_str());
	FString questionString = m_player->m_playerName.ToString() + ": Give me the " + itemString + " you are carrying.";
	const FText questionText = FText::FromString(questionString);
	targetCharacter->RespondToItemRequest(this, questionText);
}

void AHardTime2Character::RespondToItemRequest_Implementation(AHardTime2Character* requestingCharacter, const FText &question)
{/*
	pLog("RespondToItemRequest", true);
	DoDropItemAction();
	SetLastActionInterrupted(true);
	requestingCharacter->RequestItemHandleResponse(this);*/
}

void AHardTime2Character::AcceptItemRequest(AHardTime2Character* requestingCharacter)
{
	pLog("AcceptItemRequest", true);
	DoDropItemAction();
	SetLastActionInterrupted(true);
	requestingCharacter->RequestItemHandleResponse(this);
}

void AHardTime2Character::RequestItemHandleResponse(AHardTime2Character* targetCharacter)
{
	pLog("RequestItemHandleResponse", true);
	m_player->SetRequested(targetCharacter->m_player);
	if (m_targetItem->m_carryingPlayer == nullptr)
	{
		DoDropItemAction();
		pLog("Item pickedup");
		DoPickupItemAction(m_targetItem);
		m_aiState = EAIState::cooldown;
		UpdateStatus();
	} else {
		pLog("No item pickedup");
		m_aiState = EAIState::cooldown;
		SetLastActionInterrupted(true);
		UpdateStatus();
	}
}

void AHardTime2Character::DoAttackAction(AHardTime2Character* targetCharacter)
{
	pLog("ENTERING AHardTime2Character::AttackAction", true);
	std::stringstream ss;
	ss << "targetCharacter = " << TCHAR_TO_UTF8(*(targetCharacter->m_player->m_playerName.ToString())) << "\n";
	pLog(ss, true);
	targetCharacter->DeltaHealth(-1);
	targetCharacter->m_player->relMap[this->m_player->m_key]->deltaAggro(50);
	AttackEffect(targetCharacter);
	m_aiState = EAIState::cooldown;
	UpdateStatus();
}