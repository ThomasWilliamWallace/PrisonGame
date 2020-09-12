// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HTNPlanner.h"
#include "Missions.h"
#include "Locations.h"
#include "AbstractAction.h"
#include "ActorItem.h"
#include "SimWorld.h"
#include "PlayerData.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "HardTime2Character.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EAIState : uint8
{
	cooldown			UMETA(DisplayName = "Cooldown"),
	noTask				UMETA(DisplayName = "No task"),
	commandInProgress	UMETA(DisplayName = "Command in progress"),
	newCommand			UMETA(DisplayName = "New command"),
	usingRoom			UMETA(DisplayName = "Using room"),
};

UENUM(BlueprintType, Blueprintable)
enum class EAICommand : uint8
{
	goToLocation		UMETA(DisplayName = "Go to location"),
	pickupItem			UMETA(DisplayName = "Pickup item"),
	dropItem			UMETA(DisplayName = "Drop item"),
	useRoom				UMETA(DisplayName = "Use room"),
	requestItem			UMETA(DisplayName = "Request item"),
	attack				UMETA(DisplayName = "Attack"),
};

UCLASS(config=Game)
class AHardTime2Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	void InitCameraBoom();

	void InitCamera();

	void Init();

public:

	AHardTime2Character(const FObjectInitializer& ObjectInitializer);
	AHardTime2Character();

	virtual void BeginDestroy() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, Category = Planning_AI)
		void SetLastActionInterrupted(bool interrupted);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Planning_AI)
		bool readyForNewAction = true;

	UFUNCTION(BlueprintCallable, Category = Planning_AI)
		void SetWorld(USimWorld* simWorld);

	UFUNCTION(BlueprintCallable, Category = Planning_AI)
		USimWorld* GetSimWorld();

	UFUNCTION(BlueprintCallable, Category = Planning_AI)
		void UpdateLocation(ELocations location);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaHealth(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaStrength(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaAgility(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaIntelligence(float delta);

	UPROPERTY(Instanced)
	    UPlayerData* m_player;  //this pointer owns and maintains the m_player, but other objects such as world may also access it

	UPROPERTY()
		USimWorld* m_world;  //a reference to the single external world object used by the AI.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void GoToLocation(ELocations location);

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void PickUpItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void DropItem();

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void UseRoom();

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void RequestItem(AHardTime2Character* character);

	UFUNCTION(BlueprintCallable, Category = LowLevelAI)
		void Attack(AHardTime2Character* character);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		EAIState m_aiState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		EAICommand m_aiCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		AActorItem* m_targetItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		AHardTime2Character* m_targetPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		AActor* m_targetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Knowledge)
		AActor* m_mainHall;  //TODO move these to game world state

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Knowledge)
		AActor* m_bedroom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Knowledge)
		AActor* m_circuitTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Knowledge)
		AActor* m_gym;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Knowledge)
		AActor* m_library;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		int m_useCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		ELocations m_location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LowLevelAI)
		AActorItem* m_carriedItem;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = LowLevelAI)
		void OnCooldown();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = LowLevelAI)
		void OnCommandInProgress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = LowLevelAI)
		void OnNoTask();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = LowLevelAI)
		void OnNewCommand();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = LowLevelAI)
		void OnUsingRoom();

	UFUNCTION()
	void CooldownTimerElapsed();
	FTimerHandle cooldownTimerHandle;

	UFUNCTION()
	void UsingRoomTimerElapsed();
	FTimerHandle usingRoomTimerHandle;

	void PickUpItemMoveCompleted(FAIRequestID a, const FPathFollowingResult &b);
	FDelegateHandle pickUpItemMoveDelegateHandle;

	void GoToLocationMoveCompleted(FAIRequestID a, const FPathFollowingResult &b);
	FDelegateHandle goToLocationMoveDelegateHandle;

	void RequestItemMoveCompleted(FAIRequestID a, const FPathFollowingResult &b);
	FDelegateHandle requestItemMoveDelegateHandle;

	void AttackMoveCompleted(FAIRequestID a, const FPathFollowingResult &b);
	FDelegateHandle attackMoveDelegateHandle;

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayStatus(const FString& displayString);

	UFUNCTION(BlueprintCallable, Category = Action)
		void PickupItemAction(AActorItem* item);

	UFUNCTION(BlueprintCallable, Category = Action)
		void DropItemAction();

	UFUNCTION(BlueprintCallable, Category = Action)
		void RequestItemAction(AHardTime2Character* targetCharacter);

	UFUNCTION(BlueprintCallable, Category = Action)
		void AttackAction(AHardTime2Character* targetCharacter);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Action)
		void AttackEffect(AHardTime2Character* targetCharacter);

	void UpdateStatus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
		void RespondToItemRequest(AHardTime2Character* requestingCharacter, const FText &question);

	UFUNCTION(BlueprintCallable, Category = Action)
		void RequestItemHandleResponse(AHardTime2Character* targetCharacter);

private:

};