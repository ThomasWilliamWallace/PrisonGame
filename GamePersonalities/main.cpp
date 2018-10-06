#include <iostream>
#include <time.h>
#include <iomanip> // setprecision
#include <sstream>
#include "Constants.hpp"
#include "Player.hpp"
#include "Missions.hpp"
#include "Actions.hpp"
#include "Locations.hpp"
#include "World.hpp"
#include "BasicAI.hpp"
#include "HTN.hpp"
using namespace std;

void PriorityActions(int frame, Player player[], World &world)
{
    Actions action;
    for (int playerIndex = 0; playerIndex<c_playerCount; playerIndex++)
    {
        action = player[playerIndex].action;
        
        switch(action)
        {
            case Actions::attack:
                AttackAction(playerIndex, player, world);
                break;
            case Actions::useRoom:
                break;
            case Actions::goToLibrary:
                break;
            case Actions::goToGym:
                break;
            case Actions::goToCircuitTrack:
                break;
            case Actions::goToBedroom:
                break;
            case Actions::goToMainHall:
                break;
            case Actions::makeFriends:
                break;
            case Actions::offerMission:
                break;
            case Actions::pickUpItem:
                break;
            case Actions::dropItem:
                break;
            case Actions::evade:
                player[playerIndex].narrative = "evade";
                break;
            case Actions::noAction:
                break;
        }
    }
}

void Act(int playerIndex, int frame, Player player[], World &world)
{
    Actions action = player[playerIndex].action;
    if (player[playerIndex].attacked && action != Actions::attack && action != Actions::evade)
    {
        player[playerIndex].narrative = "attempted action " + ActionToString(action) + " but was attacked and lost their turn.";
        player[playerIndex].aiController.lastActionSucceeded = false;
        return;
    }
    
    switch(action)
    {
        case Actions::attack:
            break;
        case Actions::evade:
            break;
        case Actions::goToBedroom:
            if (player[playerIndex].locationClass.location == Locations::bedroom)
            {
                player[playerIndex].narrative = "tries to go to the bedroom, but is already there!";
            } else
            {
                if (player[playerIndex].locationClass.location == Locations::mainHall)
                {
                    player[playerIndex].narrative = "goes to the bedroom.";
                    player[playerIndex].locationClass.location = Locations::bedroom;
                } else
                {
                    player[playerIndex].narrative = "tries to go to the bedroom, but is too far away.";
                }
            }
            break;
        case Actions::goToCircuitTrack:
            if (player[playerIndex].locationClass.location == Locations::circuitTrack)
            {
                player[playerIndex].narrative = "tries to go to the circuit track, but is already there!";
            } else
            {
                if (player[playerIndex].locationClass.location == Locations::mainHall)
                {
                    player[playerIndex].narrative = "goes to the circuit track.";
                    player[playerIndex].locationClass.location = Locations::circuitTrack;
                } else
                {
                    player[playerIndex].narrative = "tries to go to the circuit track, but is too far away.";
                }
            }
            break;
        case Actions::goToGym:
            if (player[playerIndex].locationClass.location == Locations::gym)
            {
                player[playerIndex].narrative = "tries to go to the gym, but is already there!";
            } else
            {
                if (player[playerIndex].locationClass.location == Locations::mainHall)
                {
                    player[playerIndex].narrative = "goes to the gym.";
                    player[playerIndex].locationClass.location = Locations::gym;
                } else
                {
                    player[playerIndex].narrative = "tries to go to the gym, but is too far away.";
                }
            }
            break;
        case Actions::goToLibrary:
            if (player[playerIndex].locationClass.location == Locations::library)
            {
                player[playerIndex].narrative = "tries to go to the library, but is already there!";
            } else
            {
                if (player[playerIndex].locationClass.location == Locations::mainHall)
                {
                    player[playerIndex].narrative = "goes to the library.";
                    player[playerIndex].locationClass.location = Locations::library;
                } else
                {
                    player[playerIndex].narrative = "tries to go to the library, but is too far away.";
                }
            }
            break;
        case Actions::goToMainHall:
            if (player[playerIndex].locationClass.location == Locations::mainHall)
            {
                player[playerIndex].narrative = "tries to go to the main hall, but is already there!";
            } else
            {
                player[playerIndex].narrative = "goes to the main hall.";
                player[playerIndex].locationClass.location = Locations::mainHall;
            }
            break;
        case Actions::useRoom:
            UseRoomAction(playerIndex, player, world);
            break;
        case Actions::makeFriends:
            MakeFriendsAction(playerIndex, player, world);
            break;
        case Actions::offerMission:
            OfferMissionAction(playerIndex, player, world);
            break;
        case Actions::pickUpItem:
            PickUpItemAction(playerIndex, player, world);
            break;
        case Actions::dropItem:
            DropItemAction(playerIndex, player, world);
            break;
        case Actions::noAction:
            player[playerIndex].narrative = "ERROR NO ACTION.";
            player[playerIndex].aiController.lastActionSucceeded = false;
            break;
    }
}

void Display(Player player[], int frame)
{
    for (int playerIndex=0; playerIndex<c_playerCount; playerIndex++)
    {
        std::cout << frame << ": " << player[playerIndex].name << " tries to " << ActionToString(player[playerIndex].action) << " while in the " << player[playerIndex].lastLocationClass.ToString() << ": " << player[playerIndex].narrative << "\n";
    }
}

void AggroCooldown(Player player[])
{
    for (int i = 0; i < c_playerCount; i++)
    {
        for (int j = 0; j < c_playerCount; j++)
        {
            player[i].rel[j].deltaAggro(-c_aggroCooldown);
        }
    }
}

void CleanUpFrame(Player player[])
{
    for (int playerIndex=0; playerIndex<c_playerCount; playerIndex++)
    {
        player[playerIndex].narrative = "";
        player[playerIndex].attacked = false;
        player[playerIndex].lastAction = player[playerIndex].action;
        player[playerIndex].lastLocationClass.location = player[playerIndex].locationClass.location;
    }
}

void FullDisplay(Player player[], World &world)
{
    std::cout << "\n";
    world.PrintWorld(player);
    
    for (int playerIndex = 0; playerIndex < c_playerCount; playerIndex++)
    {
        player[playerIndex].PrintPlayer();
    }
    
    //display rels
    for (int i=0; i < c_playerCount; i++)
    {
        for (int j=0; j < c_playerCount; j++)
        {
            if (i!=j)
                player[i].rel[j].PrintRel(player[i].name, player[j].name);
        }
    }
}

void Simulate()
{
    // Setup
    Player player[c_playerCount];
    for (int playerIndex = 0; playerIndex < c_playerCount; playerIndex++)
    {
        player[playerIndex].m_playerIndex = playerIndex;
    }
    World world;
    player[0].name = "Thomas";
    player[1].name = "Vita";
    player[2].name = "Zog";
    player[0].aiController = AIController(AI::humanAI);
    player[1].aiController = AIController(AI::htnAI);
    player[2].aiController = AIController(AI::htnAI);
    for (int playerIndex = 0; playerIndex < c_playerCount; playerIndex++)
    {
        player[playerIndex].missionClass = CreateNewMission(player,playerIndex);
    }
    
    // loop one time step at a time
    for (int frame=0; frame<15; frame++)
    {
        CleanUpFrame(player);
        world.Clean();
        for (int playerIndex=0; playerIndex < c_playerCount; playerIndex++)
        {
            player[playerIndex].action = player[playerIndex].aiController.ChooseAction(playerIndex, player, world);
        };
        PriorityActions(frame, player, world); //mainly for resolving clashes and attacks, ie conflict.
        for (int playerIndex=0; playerIndex < c_playerCount; playerIndex++)
        {
            Act(playerIndex, frame, player, world);
        };
        world.WorldEffects(player, frame);
        AggroCooldown(player);
        for (int playerIndex=0; playerIndex < c_playerCount; playerIndex++)
        {
            player[playerIndex].UpdateMissions(player);
        }
        Display(player, frame);
    }
    world.Clean();
    FullDisplay(player, world);
}

int main(int argc, char **argv)
{    
    unsigned int randomSeed = static_cast<unsigned int>(time(NULL));
    randomSeed = 1536439609;
    srand(randomSeed);
    std::cout << "Random seed = " << randomSeed << "\n";
    Simulate();
    //char s1[50];
    //std::cin >> s1;
    return 0;
}