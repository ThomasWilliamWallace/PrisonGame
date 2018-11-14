#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HTNPlanner.hpp"
#include "Missions.hpp"
#include "Locations.hpp"
#include "Actions.hpp"
#include "ActorItem.hpp"
#include "AICharacterC.generated.h"

//class HTNPrimitive;
//typedef std::shared_ptr<HTNPrimitive> HTNPrimitivePtr;
//typedef std::deque< HTNPrimitivePtr > HTNPrimitiveList;

UCLASS()
class HARDTIME2_API AAICharacterC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacterC();

	float health = 70;
	float sanity = 70;
	float strength = 50;
	float agility = 50;
	float intelligence = 50;

	bool lastActionSucceeded = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AAICharacterC)
		bool readyForNewAction = true;

	Actions lastAction;
	HTNPrimitivePtr lastPrimitiveAction;
	MissionClass missionClass;

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateLocation(int locationAsInt);

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateItemLocation(AActor* actor, int locationAsInt);

	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void AddItem(AActor* actor);

	LocationClass locationClass;
	LocationClass previousLocationClass;
	HTNPrimitiveList htnPlan;
	std::vector< SimActorItem* > m_items;
	Actions action;
	AActor* m_itemFocusPtr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* m_carriedItem{ nullptr };
	UFUNCTION(BlueprintCallable, Category = AAICharacterC)
		void UpdateCarriedItemC(AActor* item, ACharacter* character);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void GoToLocation(int location);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void AttackPlayer(ACharacter* character);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void PickUpItem(AActor* item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void DropItem();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void UseRoom();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = AAICharacterC)
		void Evade();	
	
};
