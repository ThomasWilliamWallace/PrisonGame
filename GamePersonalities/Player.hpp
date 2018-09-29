//
//  Player.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Stats.hpp"
#include "Missions.hpp"
#include "BasicAI.hpp"

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
    
    void PrintRel(std::string name1, std::string name2);
};

class Player{
public:
    Stats stats;

    int m_playerIndex; //players array index
    int cash = 0; //cash, in dollars, no bounds.
    int sentence = 5; //days left in prison sentence, only bound is above -1.
    Actions action = Actions::useRoom; //stores the current action being attempted. This is held till the end of the frame, as it may be interrupted by another action.
    Actions lastAction = Actions::useRoom; //stores the last action taken. Useful for checking if hidden.
    LocationClass locationClass; //location maps to a discrete set of locations, gym, library, circuit track, bed.
    LocationClass lastLocationClass; //location the character was at when the turn began. Used by the print display.
    bool attacked = false; //tracks whether an attack has disrupted his turn.
    std::string narrative; //printed at the end of each round, giving the update for this character
    std::string name = "No-name"; //name of the character, used in speech
    MissionClass missionClass; //a mission currently assigned to the character
    AIController aiController; //controlling AI for this character
    int playerTarget = c_empty; //index of the character being targetted. You must set this when attacking or assigning a mission to another player!
    MissionClass missionOffer; // a mission being offered to 'playerTarget'
    
	bool IsMissionComplete();
    void UpdateMissions(Player player[]);
    void PrintPlayer();
    
    Relationship rel[c_playerCount];
};

std::string CharacterName(Player player[], int playerIndex);
MissionClass CreateNewMission(Player player[], int playerIndex);

#endif /* Player_hpp */
