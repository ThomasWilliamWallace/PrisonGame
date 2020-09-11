#include "ActorItem.h"
#include "HardTime2GameMode.h"
#include "pLog.h"


std::string AActorItem::ToString()
{
    return ItemTypeToString(m_itemType);
}

std::string SimActorItem::ToString()
{
	return ItemTypeToString(m_itemType);
}

// Called when the game starts or when spawned
void AActorItem::BeginPlay()
{
	Super::BeginPlay();
	auto gameMode = GetWorld()->GetAuthGameMode();
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	hardTime2GameMode->m_simWorld->AddItem(this);
}

void AActorItem::BeginDestroy()
{
	Super::BeginDestroy();
	if (GetWorld() == nullptr)
	{
		pLog("ERROR: AActorItem::BeginDestroy, GetWorld() is nullptr");
		return;
	}
	auto gameMode = GetWorld()->GetAuthGameMode();
	if (gameMode == nullptr)
	{
		pLog("ERROR: AActorItem::BeginDestroy, gameMode is nullptr");
		return;
	}
	AHardTime2GameMode* hardTime2GameMode = static_cast<AHardTime2GameMode*>(gameMode);
	if (hardTime2GameMode == nullptr)
	{
		pLog("ERROR: AActorItem::BeginDestroy, hardTime2GameMode is nullptr");
		return;
	}
	if (hardTime2GameMode->m_simWorld == nullptr)
	{
		pLog("ERROR: AActorItem::BeginDestroy, hardTime2GameMode->m_simWorld is nullptr");
		return;
	}
	hardTime2GameMode->m_simWorld->RemoveItem(this);
}
