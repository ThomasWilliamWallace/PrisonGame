#pragma once
//
//  Item.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Locations.hpp"
#include "GameFramework/Actor.h"

class ACharacter;

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

class SimActorItem
{
public:
	ItemType m_itemType;
	LocationClass m_locationClass;
	AActor* m_unrealItem;
	ACharacter* m_carryingPlayer;
	SimActorItem(ItemType itemE, Locations location, AActor* unrealItem, ACharacter* carryingPlayer = nullptr) : m_itemType(itemE), m_locationClass(location), m_unrealItem(unrealItem), m_carryingPlayer(carryingPlayer) {};
	std::string ToString();
	virtual ~SimActorItem() = default;
};