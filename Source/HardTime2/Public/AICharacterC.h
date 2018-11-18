#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HTNPlanner.hpp"
#include "Missions.hpp"
#include "Locations.hpp"
#include "Actions.hpp"
#include "ActorItem.h"
#include "World.hpp"
#include "Player.hpp"
#include "AICharacterC.generated.h"

UCLASS()
class HARDTIME2_API AAICharacterC : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AAICharacterC)
		bool readyForNewAction = true;

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateLocation(int locationAsInt);

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateItemLocation(AActorItem* item, int locationAsInt);

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void AddItem(AActorItem* item);

	// Sets default values for this character's properties
	AAICharacterC();

	bool lastActionSucceeded = true;
	HTNPrimitivePtr lastPrimitiveAction;
	HTNPrimitiveList htnPlan;
	Player m_player;
	World m_world;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateCarriedItemC(AActorItem* item, ACharacter* character);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void GoToLocation(int location);

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
};
