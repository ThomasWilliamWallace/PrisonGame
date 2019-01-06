#pragma once

#include <vector>
#include "PlayerData.h"
#include "Object.h"
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
		int AddPlayer(UPlayerData* playerData);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void RemoveItem(AActorItem* item);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void RemovePlayer(UPlayerData* playerData);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void UpdateItemLocation(AActorItem* item, ELocations location);

	UFUNCTION(BlueprintCallable, Category = UpdateWorld)
		void UpdateCarriedItemC(AActorItem* item, ACharacter* character);

	UPROPERTY()
		UPlayerData* weightsOccupied;

	UPROPERTY()
		UPlayerData* circuitsOccupied;

	UPROPERTY()
		UPlayerData* studyOccupied;

	UPROPERTY()
		UPlayerData* bedOccupied;

    void WorldEffects(UPlayerData player[], int frame);
    void PrintWorld(UPlayerData player[]);
    void FullDisplay(UPlayerData player[]);
    void Clean();
    USimWorld();
    std::vector< AActorItem* > items;
	std::vector< UPlayerData* > m_players;
};
