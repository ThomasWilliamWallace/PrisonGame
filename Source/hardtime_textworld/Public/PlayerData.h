#pragma once

#include <iostream>
#include "PStats.h"
#include "Missions.h"
#include "BasicAI.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "PlatformSpecific.h"
#include "Relationship.h"

class USimWorld;
class MissionClass;

UCLASS(BlueprintType, Blueprintable)
class UPlayerData
{
	GENERATED_BODY()

public:

    int m_key; //players PlayerRegistry index
    std::shared_ptr<BaseAction> action; //stores the current action being attempted. This is held till the end of the frame, as it may be interrupted by another action.
    std::shared_ptr<BaseAction> lastAction; //stores the last action taken. Useful for checking if hidden.
    LocationClass locationClass; //location maps to a discrete set of locations, gym, library, circuit track, bed.
    LocationClass lastLocationClass; //location the character was at when the turn began. Used by the print display.
    bool attacked = false; //tracks whether an attack has disrupted his turn.
    std::string narrative; //printed at the end of each round, giving the update for this character
    std::string m_playerName = "No-name"; //name of the character, used in speech
    std::shared_ptr<MissionClass> missionClass; //a mission currently assigned to the character

    PStats pStats;
    int cash; //cash, in dollars, no bounds.
    int sentence; //days left in prison sentence, only bound is above -1.
    AIController aiController; //controlling AI for this character
    std::shared_ptr<MissionClass> missionOffer; // a mission being offered to 'playerTarget'

	UPROPERTY()
		RealItemType* itemPtr; //pointer to an item carried by the player

	void UpdateMissions(USimWorld &world);
    void PrintPlayer();
	bool IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType);
	void SetRequested(UPlayerData* requestedPlayer);
	UPlayerData();

	UPROPERTY()
		RelMap relMap; //Relationships have manual memory management, as they are kept in a TMap without UProperty(). TODO Change to unreal memory management

	std::string CharacterName();
    bool OtherInReach(UPlayerData& otherPlayerPtr);
};