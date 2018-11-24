#pragma once

#include "Locations.h"
#include "GameFramework/Actor.h"
#include "ActorItem.generated.h"

class UPlayerData;

UENUM(BlueprintType, Blueprintable)
enum class EItemType : uint8
{
	assaultRifle,
	ball,
	barbell,
	bat,
	baton,
	bottle,
	brick,
	broom,
	cigarette,
	cleaver,
	comb,
	dumbbell,
	dynamite,
	extinguisher,
	hammer,
	knife,
	mirror,
	pipe,
	pistol,
	plank,
	poolCue,
	rock,
	scissors,
	screw,
	sword,
	syringe
};

std::string ItemTypeToString(EItemType itemType);
EItemType GetRandomItemType();

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

	LocationClass m_locationClass;
	UPlayerData* m_carryingPlayer;
    std::string ToString();
};

class SimActorItem
{
public:
	EItemType m_itemType;
	LocationClass m_locationClass;
	UPlayerData* m_carryingPlayer;
	AActorItem* m_realItem;
	SimActorItem(AActorItem* realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer = nullptr):
		m_itemType(itemType),
		m_locationClass(location),
		m_carryingPlayer(carryingPlayer),
		m_realItem(realItem)
    {};
    std::string ToString();
};
