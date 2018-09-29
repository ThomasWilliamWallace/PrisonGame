//
//  Stats.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 24/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Stats_hpp
#define Stats_hpp

#include <stdio.h>
#include <iostream>
#include "Constants.hpp"
#include "Locations.hpp"
#include "Missions.hpp"

class Stats //the abilities of the character. Generally linear and bound between 0 and 100.
{
    double health = 70; //physical health. When it reaches 0, a death may be triggered.
    double sanity = 70; //mental health. When it reaches 0, a breakdown is triggered.
    
    double strength = 0; //improves your health and fight damage
    double agility = 0; //improves your speed
    double intelligence = 0; //improves your ability to use items such as computers
    double charisma = 0; //ability to influence others socially
    double reputation = 0; //reputation for fearsome deeds
    double respect = 0; //reputation for effectiveness
    
public:
    // *** PERSONALITY TRAITS START ***
    int loyalty = rand() % 100; //loyal characters will stick by their friends, and make new friends slower.
    int traitorous = rand() % 100; //traitorous characters have a small chance of a calculated betrayal at an opportune time.
    int aggression = rand() % 100; //aggressive characters are more inclined to conflict
    int sociability = rand() % 100; //sociable characters talk more and offer and recieve more missions
    int curiosity = rand() % 100; //curious characters like to explore and find out information.
    int risktaking = rand() % 100; //risk-taking characters will take more risks to accomplish their goals
    int leader = rand() % 100; //leader characters prefer to establish their position at the top of the hierarchy
    int follower = rand() % 100; //follower characters will tend to follow strong individuals
    int herdfollower = rand() % 100; //A herd follower character prefers to follow the herd
    int strongwilled = rand() % 100; //A strong-willed character will stick to their goal once they have begun and cannot be easily deterred
    int proud = rand() % 100; //A proud character will not give up or surrender under pressure
    int forgiving = rand() % 100; //A character who is not forgiving prefers to hold a grudge.
    int discreet = rand() % 100; //A discreet character prefers not to share information.
    //dramatic, inappropriate, thieving, gym rat?
    //The AI will use these personality traits when choosing it's goals.
    // *** PERSONALITY TRAITS END ***

    double getHealth();
    double getSanity();
    double getStrength();
    double getAgility();
    double getIntelligence();
    double getCharisma();
    double getReputation();
    double getRespect();
    
    void deltaHealth(double delta);
    void deltaSanity(double delta);
    void deltaStrength(double delta);
    void deltaAgility(double delta);
    void deltaIntelligence(double delta);
    void deltaCharisma(double delta);
    void deltaReputation(double delta);
    void deltaRespect(double delta);
    
    void PrintStats();
    Stats();
};

double transformStat(double inputStat);

#endif /* Stats_hpp */
