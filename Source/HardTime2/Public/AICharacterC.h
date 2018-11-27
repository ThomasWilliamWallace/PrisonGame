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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AAICharacterC)
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
