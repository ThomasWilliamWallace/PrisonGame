#pragma once

#ifndef TEXT_ONLY_HTN
#include "EItemType.generated.h"
#endif

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
	syringe,
	LAST = syringe
};