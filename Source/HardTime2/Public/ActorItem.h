#pragma once

#include "Locations.hpp"
#include "GameFramework/Actor.h"
#include "ActorItem.generated.h"

class Player;

enum class ItemType
{
	assaultRifle,
	ball,
	bat,
	bottle,
	brick,
	broom,
	cigarette,
	cleaver,
	dumbbell,
	dynamite,
	extinguisher,
	hammer,
	knife,
	mirror,
	pistol,
	plank,
	poolCue,
	rock,
	scissors,
	sword,
	syringe
};

std::string ItemTypeToString(ItemType itemType);
ItemType GetRandomItemType();

UCLASS()
class AActorItem : public AActor
{
	GENERATED_BODY()
public:
	ItemType m_itemType;
	LocationClass m_locationClass;
	Player* m_carryingPlayer;
    std::string ToString();
};

class SimActorItem
{
public:
	ItemType m_itemType;
	LocationClass m_locationClass;
	Player* m_carryingPlayer;
	AActorItem* m_realItem;
	SimActorItem(AActorItem* realItem, ItemType itemType, Locations location, Player* carryingPlayer = nullptr):
		m_itemType(itemType),
		m_locationClass(location),
		m_carryingPlayer(carryingPlayer),
		m_realItem(realItem)
    {};
    std::string ToString();
};
