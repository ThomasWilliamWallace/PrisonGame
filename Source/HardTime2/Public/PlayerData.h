#pragma once

#include <iostream>
#include "PStats.h"
#include "Missions.h"
#include "BasicAI.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "Object.h"
#include "PlatformSpecific.h"
#include "Relationship.h"
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "AbstractPlayerData.h"
#include "PlayerData.generated.h"

class USimWorld;
class AActorItem;
class AHardTime2Character;
class MissionClass;

UCLASS(BlueprintType, Blueprintable)
class UPlayerData : public UObject
{
	GENERATED_BODY()

public:
    int cash; //cash, in dollars, no bounds.
    int sentence; //days left in prison sentence, only bound is above -1.
    FName m_playerName; //name of the character, used in speech.
    AIController aiController; //controlling AI for this character
    std::shared_ptr<MissionClass> missionOffer; // a mission being offered to 'playerTarget'

	UPROPERTY()
		AActorItem* itemPtr; //pointer to an item carried by the player

	UPROPERTY()
		UPlayerData* playerTargetPtr; //index of the character being targetted. You must set this when attacking or assigning a mission to another player!

	UPROPERTY()
		AActorItem* itemFocusPtr; //pointer to an item the player is trying to interact with

	UPROPERTY()
		AHardTime2Character* physicalCharacter;

	void UpdateMissions(USimWorld &world);
    void PrintPlayer();
	bool IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType);
	void SetRequested(UPlayerData* requestedPlayer);
	UPlayerData();

	UPROPERTY()
		TMap<int, URelationship*> relMap; //Relationships have manual memory management, as they are kept in a TMap without UProperty(). TODO Change to unreal memory management

	virtual class UWorld* GetWorld() const override;

	std::string CharacterName();
	AbstractPlayerData abstractPlayerData;
};


bool OtherInReach(AbstractPlayerData& playerPtr, AbstractPlayerData& otherPlayerPtr, PlayerMap& playerMap);