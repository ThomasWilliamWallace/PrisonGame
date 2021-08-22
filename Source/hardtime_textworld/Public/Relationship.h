#pragma once
//TODO cull unused includes
#include <iostream>
#include "PStats.h"
#include "Missions.h"
#include "BasicAI.h"
#include "AbstractAction.h"
#include "Constants.h"
#include "PlatformSpecific.h"

UCLASS()
class URelationship  //their opinion of another character. Asymptotically bound between 0 and 100.
{
	GENERATED_BODY()

private:
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
    
	bool isRequestedRecently = false;
    void SetRecentlyRequested();
};