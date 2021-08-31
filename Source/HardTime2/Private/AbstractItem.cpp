#include "AbstractItem.h"
#include "PlayerData.h"
#include "PlatformSpecificForPlanner.h"

// Unreal version needs this include
#ifndef TEXT_ONLY_HTN
#include "ActorItem.h"
#endif

std::string ItemTypeToString(EItemType itemType)
{
	switch (itemType)
	{
	case EItemType::assaultRifle:
		return "Assault Rifle";
	case EItemType::ball:
		return "Ball";
	case EItemType::barbell:
		return "Barbell";
	case EItemType::bat:
		return "Bat";
	case EItemType::baton:
		return "Baton";
	case EItemType::bottle:
		return "Bottle";
	case EItemType::brick:
		return "Brick";
	case EItemType::broom:
		return "Broom";
	case EItemType::cigarette:
		return "Cigarette";
	case EItemType::cleaver:
		return "Cleaver";
	case EItemType::comb:
		return "Comb";
	case EItemType::dumbbell:
		return "Dumbbell";
	case EItemType::dynamite:
		return "Dynamite";
	case EItemType::extinguisher:
		return "Extinguisher";
	case EItemType::hammer:
		return "Hammer";
	case EItemType::knife:
		return "Knife";
	case EItemType::mirror:
		return "Mirror";
	case EItemType::pipe:
		return "Pipe";
	case EItemType::pistol:
		return "Pistol";
	case EItemType::plank:
		return "Plank";
	case EItemType::poolCue:
		return "Pool Cue";
	case EItemType::rock:
		return "Rock";
	case EItemType::scissors:
		return "Scissors";
	case EItemType::screw:
		return "Screwdriver";
	case EItemType::sword:
		return "Sword";
	case EItemType::syringe:
		return "Syringe";
	}
	ThrowException("ERROR: NO ITEM NAME");
	return "ERROR: NO ITEM NAME";
}

EItemType GetRandomItemType()
{
    int random = rand() % 100;
    if (random<4)
        return EItemType::assaultRifle;
	else if (random < 8)
        return EItemType::ball;
	else if (random < 12)
		return EItemType::barbell;
	else if (random < 16)
        return EItemType::bat;
	else if (random < 20)
		return EItemType::baton;
    else if (random<24)
		return EItemType::bottle;
	else if (random < 28)
        return EItemType::brick;
	else if (random < 32)
        return EItemType::broom;
	else if (random < 36)
        return EItemType::cigarette;
	else if (random < 40)
        return EItemType::cleaver;
    else if (random<44)
        return EItemType::dumbbell;
	else if (random < 48)
        return EItemType::dynamite;
	else if (random < 52)
        return EItemType::extinguisher;
    else if (random<58)
        return EItemType::hammer;
	else if (random < 62)
        return EItemType::knife;
	else if (random < 66)
        return EItemType::mirror;
	else if (random < 70)
		return EItemType::pipe;
	else if (random < 74)
        return EItemType::pistol;
	else if (random < 78)
        return EItemType::plank;
	else if (random < 82)
        return EItemType::poolCue;
    else if (random<86)
        return EItemType::rock;
	else if (random < 90)
        return EItemType::scissors;
	else if (random < 94)
		return EItemType::screw;
	else if (random < 98)
        return EItemType::sword;
    else
        return EItemType::syringe;
}

std::string AbstractItem::ToString()
{
    return ItemTypeToString(m_itemType);
}

SimItem::SimItem(CreateSimFromRealItem c, RealItemType* realItem):
	AbstractItem(realItem->m_itemType, realItem->m_locationClass.location),
	m_realItem(realItem)
{
#ifdef TEXT_ONLY_HTN
	if (realItem->m_carryingPlayer != nullptr) {
		m_carryingPlayer = realItem->m_carryingPlayer;
	}
#else
	if (realItem->m_carryingPlayer != nullptr) {
		m_carryingPlayer = realItem->m_carryingPlayer;
	}
#endif
}

SimItem::SimItem(RealItemType* realItem, EItemType itemE, ELocations location, UPlayerData* carryingPlayer):
	AbstractItem(itemE, location, carryingPlayer),
	m_realItem(realItem)
{}

SimItem::SimItem(SimItem& item):
	SimItem(item.m_realItem, item.m_itemType, item.m_locationClass.location, item.m_carryingPlayer)
{}