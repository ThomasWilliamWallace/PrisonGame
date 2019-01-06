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
#include "AICharacterC.generated.h"

UCLASS()
class HARDTIME2_API AAICharacterC : public ACharacter
{
	GENERATED_BODY()

public:

	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool readyForNewAction = true;

	UFUNCTION(BlueprintCallable, Category = AI_World)
		void SetWorld(USimWorld* simWorld);

	UFUNCTION(BlueprintCallable, Category = AI_World)
		USimWorld* GetSimWorld();

	UFUNCTION(BlueprintCallable, Category = AI_World)
		void UpdateLocation(ELocations location);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaHealth(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaStrength(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaAgility(float delta);

	UFUNCTION(BlueprintCallable, Category = Stats)
		void DeltaIntelligence(float delta);

	// Sets default values for this character's properties
	AAICharacterC();

	UFUNCTION(BlueprintCallable, Category = AI)
		void SetLastActionInterrupted();

	UPROPERTY()
		UPlayerData* m_player;

	UPROPERTY()
		USimWorld* m_world;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void GoToLocation(ELocations location);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void AttackPlayer(ACharacter* character);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void PickUpItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void DropItem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void UseRoom();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void Evade();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AIControl)
		void RequestItem(AHardTime2Character* character);
};
