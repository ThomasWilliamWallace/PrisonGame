#pragma once

#include "UObject/Object.h"
#include "PStats.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UPStats : public UObject
{
    GENERATED_BODY()

public:
    UPStats(const FObjectInitializer& ObjectInitializer);
    private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float health = 70; //physical health. When it reaches 0, a death may be triggered.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float sanity = 70; //mental health. When it reaches 0, a breakdown is triggered.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float strength = 50; //improves your health and fight damage
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float agility = 80; //improves your speed
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float intelligence = 30; //improves your ability to use items such as computers
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float charisma = 40; //ability to influence others socially
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float reputation = 20; //reputation for fearsome deeds
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        float respect = 60; //reputation for effectiveness

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
};

double transformStat(double inputStat);