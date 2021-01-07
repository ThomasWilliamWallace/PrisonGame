#pragma once

#include "Locations.h"
#include "GameFramework/Actor.h"
#include "AbstractItem.h"
#include "EItemType.h"
#include "PlayerData.h"
#include "ActorItem.generated.h"

UCLASS()
class AActorItem : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EItemType m_itemType;

	virtual void BeginDestroy() override;

	LocationClass m_locationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = World)
    	UPlayerData* m_carryingPlayer;
    std::string ToString();
};
