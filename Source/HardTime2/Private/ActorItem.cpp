#include "ActorItem.h"

std::string ItemTypeToString(EItemType itemType)
{
	switch (itemType)
	{
	case EItemType::assaultRifle:
		return "Assault Rifle";
	case EItemType::ball:
		return "Ball";
	case EItemType::bat:
		return "Bat";
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
	case EItemType::sword:
		return "Sword";
	case EItemType::syringe:
		return "Syringe";
	}
	return "ERROR: NO ITEM NAME";
}

EItemType GetRandomItemType()
{
	int random = rand() % 100;
	if (random < 4)
		return EItemType::assaultRifle;
	else if (random < 9)
		return EItemType::ball;
	else if (random < 14)
		return EItemType::bat;
	else if (random < 19)
		return EItemType::bottle;
	else if (random < 24)
		return EItemType::brick;
	else if (random < 29)
		return EItemType::broom;
	else if (random < 34)
		return EItemType::cigarette;
	else if (random < 39)
		return EItemType::cleaver;
	else if (random < 44)
		return EItemType::dumbbell;
	else if (random < 49)
		return EItemType::dynamite;
	else if (random < 53)
		return EItemType::extinguisher;
	else if (random < 58)
		return EItemType::hammer;
	else if (random < 63)
		return EItemType::knife;
	else if (random < 67)
		return EItemType::mirror;
	else if (random < 71)
		return EItemType::pistol;
	else if (random < 76)
		return EItemType::plank;
	else if (random < 81)
		return EItemType::poolCue;
	else if (random < 86)
		return EItemType::rock;
	else if (random < 91)
		return EItemType::scissors;
	else if (random < 95)
		return EItemType::sword;
	else
		return EItemType::syringe;
}

std::string AActorItem::ToString()
{
    return ItemTypeToString(m_itemType);
}

std::string SimActorItem::ToString()
{
	return ItemTypeToString(m_itemType);
}