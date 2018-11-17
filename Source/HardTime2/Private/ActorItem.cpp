#include "ActorItem.h"

std::string ItemTypeToString(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::assaultRifle:
		return "Assault Rifle";
	case ItemType::ball:
		return "Ball";
	case ItemType::bat:
		return "Bat";
	case ItemType::bottle:
		return "Bottle";
	case ItemType::brick:
		return "Brick";
	case ItemType::broom:
		return "Broom";
	case ItemType::cigarette:
		return "Cigarette";
	case ItemType::cleaver:
		return "Cleaver";
	case ItemType::dumbbell:
		return "Dumbbell";
	case ItemType::dynamite:
		return "Dynamite";
	case ItemType::extinguisher:
		return "Extinguisher";
	case ItemType::hammer:
		return "Hammer";
	case ItemType::knife:
		return "Knife";
	case ItemType::mirror:
		return "Mirror";
	case ItemType::pistol:
		return "Pistol";
	case ItemType::plank:
		return "Plank";
	case ItemType::poolCue:
		return "Pool Cue";
	case ItemType::rock:
		return "Rock";
	case ItemType::scissors:
		return "Scissors";
	case ItemType::sword:
		return "Sword";
	case ItemType::syringe:
		return "Syringe";
	}
	return "ERROR: NO ITEM NAME";
}

ItemType GetRandomItemType()
{
	int random = rand() % 100;
	if (random < 4)
		return ItemType::assaultRifle;
	else if (random < 9)
		return ItemType::ball;
	else if (random < 14)
		return ItemType::bat;
	else if (random < 19)
		return ItemType::bottle;
	else if (random < 24)
		return ItemType::brick;
	else if (random < 29)
		return ItemType::broom;
	else if (random < 34)
		return ItemType::cigarette;
	else if (random < 39)
		return ItemType::cleaver;
	else if (random < 44)
		return ItemType::dumbbell;
	else if (random < 49)
		return ItemType::dynamite;
	else if (random < 53)
		return ItemType::extinguisher;
	else if (random < 58)
		return ItemType::hammer;
	else if (random < 63)
		return ItemType::knife;
	else if (random < 67)
		return ItemType::mirror;
	else if (random < 71)
		return ItemType::pistol;
	else if (random < 76)
		return ItemType::plank;
	else if (random < 81)
		return ItemType::poolCue;
	else if (random < 86)
		return ItemType::rock;
	else if (random < 91)
		return ItemType::scissors;
	else if (random < 95)
		return ItemType::sword;
	else
		return ItemType::syringe;
}