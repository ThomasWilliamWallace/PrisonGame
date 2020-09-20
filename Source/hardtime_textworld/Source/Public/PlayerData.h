#pragma once

#include <iostream>
#include "PStats.h"
#include "Missions.h"
#include "BasicAI.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "PlatformSpecific.h"
#include "Relationship.h"
#include "AbstractPlayerData.h"

class USimWorld;
class MissionClass;

UCLASS(BlueprintType, Blueprintable)
class UPlayerData
{
	GENERATED_BODY()

public:
    int cash = 0; //cash, in dollars, no bounds.
    int sentence = 5; //days left in prison sentence, only bound is above -1.
    AIController aiController; //controlling AI for this character
    std::shared_ptr<MissionClass> missionOffer; // a mission being offered to 'playerTarget'

	UPROPERTY()
		RealItemType* itemPtr = nullptr; //pointer to an item carried by the player

	void UpdateMissions(USimWorld &world);
    void PrintPlayer();
	bool IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType);
	void SetRequested(UPlayerData* requestedPlayer);
	UPlayerData();

	UPROPERTY()
		RelMap relMap; //Relationships have manual memory management, as they are kept in a TMap without UProperty(). TODO Change to unreal memory management

	std::string CharacterName();
	AbstractPlayerData abstractPlayerData = AbstractPlayerData();
};

bool OtherInReach(AbstractPlayerData& playerPtr, AbstractPlayerData& otherPlayerPtr);