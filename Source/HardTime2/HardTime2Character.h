// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HTNPlanner.hpp"
#include "Missions.hpp"
#include "Locations.h"
#include "Actions.hpp"
#include "ActorItem.h"
#include "SimWorld.h"
#include "PlayerData.h"
#include "HardTime2Character.generated.h"

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
public:
	AHardTime2Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable, Category = AI)
		void SetLastActionInterrupted();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool readyForNewAction = true;

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void SetWorld(USimWorld* simWorld);

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		USimWorld* GetSimWorld();

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateLocation(ELocations location);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaHealth(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaStrength(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaAgility(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaIntelligence(float delta);

	UPlayerData* m_player;  //this pointer owns and maintains the m_player, but other objects such as world may also access it
	USimWorld* m_world;  //this is purely a reference to the single external world object used by the AI.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void GoToLocation(ELocations location);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void AttackPlayer(ACharacter* character);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void PickUpItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void DropItem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void UseRoom();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void Evade();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void RequestItem(ACharacter* character);
};

