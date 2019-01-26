#pragma once

#include <iostream>
#include "PStats.hpp"
#include "Missions.hpp"
#include "BasicAI.hpp"
#include "ActorItem.h"
#include "Actions.hpp"
#include "Constants.hpp"
#include "Object.h"
#include "RelMapFwd.hpp"
#include "PlayerData.generated.h"

class Relationship //their opinion of another character. Asymptotically bound between 0 and 100.
{
    double aggro = 0; //your temporary heat against a character.
    double friendliness = 50; //your friendliness with this character. The default relationship gauge.
    double fear = 50; //the extent that you fear this character
    double threat = 50; //whether this character is recognised as a threat to be your interests. Raised by murders, particularly of
    // people who were not openly hostile to the character.
    double submissiveness = 50; //the extent to which you recognize the authority of this character
    double plotImportance = 50; //character will be given more attention in terms of missions, court cases etc
    double trust = 50; //whether you consider this character to be trusted or a traitor
    
public:
    double getAggro();
    double getFriendliness();
    double getFear();
    double getThreat();
    double getSubmissiveness();
    double getPlotImportance();
    double getTrust();
    
    void deltaAggro(double delta);
    void deltaFriendliness(double delta);
    void deltaFear(double delta);
    void deltaThreat(double delta);
    void deltaSubmissiveness(double delta);
    void deltaPlotImportance(double delta);
    void deltaTrust(double delta);
};

class USimWorld;
class AActorItem;
class AHardTime2Character;

UCLASS(BlueprintType, Blueprintable)
class UPlayerData : public UObject
{
	GENERATED_BODY()

public:
    PStats pStats;

	int m_key; //players PlayerRegistry index
    int cash = 0; //cash, in dollars, no bounds.
    int sentence = 5; //days left in prison sentence, only bound is above -1.
    Actions action = Actions::useRoom; //stores the current action being attempted. This is held till the end of the frame, as it may be interrupted by another action.
    Actions lastAction = Actions::useRoom; //stores the last action taken. Useful for checking if hidden.
    LocationClass locationClass; //location maps to a discrete set of locations, gym, library, circuit track, bed.
    LocationClass lastLocationClass; //location the character was at when the turn began. Used by the print display.
    bool attacked = false; //tracks whether an attack has disrupted his turn.
    //std::string narrative; //printed at the end of each round, giving the update for this character
    //std::string m_playerName; //name of the character, used in speech.
    MissionClass missionClass; //a mission currently assigned to the character
    AIController aiController; //controlling AI for this character
    MissionClass missionOffer; // a mission being offered to 'playerTarget'

	UPROPERTY()
		AActorItem* itemPtr = nullptr; //pointer to an item carried by the player

	UPROPERTY()
		UPlayerData* playerTargetPtr = nullptr; //index of the character being targetted. You must set this when attacking or assigning a mission to another player!

	UPROPERTY()
		AActorItem* itemFocusPtr = nullptr; //pointer to an item the player is trying to interact with

	UPROPERTY()
		AHardTime2Character* physicalCharacter = nullptr;

	void UpdateMissions(USimWorld &world);
    void PrintPlayer();
	UPlayerData();
    
	RelMap relMap;
};

std::string CharacterName(UPlayerData* playerPtr);
MissionClass CreateNewMission(UPlayerData* playerPtr);
