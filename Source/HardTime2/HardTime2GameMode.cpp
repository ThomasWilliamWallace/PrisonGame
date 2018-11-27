// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "HardTime2GameMode.h"
#include "HardTime2Character.h"
#include "pLog.hpp"
#include "UObject/ConstructorHelpers.h"

AHardTime2GameMode::AHardTime2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass (TEXT("/Game/ThirdPersonCPP/Blueprints/MasterControllerBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	pLog("AHardTime2GameMode::AHardTime2GameMode", true);
	m_simWorld = CreateDefaultSubobject<USimWorld>(TEXT("SimWorld"));
}
