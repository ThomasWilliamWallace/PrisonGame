#pragma once

#include <vector>
#include "PlayerData.h"
#include "Object.h"
#include "PlayerRegistry.h"
#include "SimWorld.generated.h"

class AActorItem;

UCLASS(BlueprintType, Blueprintable)
class USimWorld : public UObject //represents the simulated world
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void AddItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void AddPlayer(UPlayerData* playerData);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void RemoveItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void RemovePlayer(UPlayerData* playerData);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void UpdateItemLocation(AActorItem* item, ELocations location);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void UpdateCarriedItem(AActorItem* item, ACharacter* character);

	AbstractPlayerData* weightsOccupied;
	AbstractPlayerData* circuitsOccupied;
	AbstractPlayerData* studyOccupied;
	AbstractPlayerData* bedOccupied;

    void Clean();
    USimWorld();
    std::vector< AActorItem* > items;

	PlayerRegistry m_playerRegistry;
};
