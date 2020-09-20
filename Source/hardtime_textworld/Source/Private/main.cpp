#include <time.h>
#include <iomanip> // setprecision
#include <sstream>
#include "Constants.h"
#include "AbstractPlayerData.h"
#include "Missions.h"
#include "Actions.h"
#include "Locations.h"
#include "SimWorld.h"
#include "BasicAI.h"
#include "HTNPlanner.h"
#include "pLog.h"
#include "PlayerRegistry.h"

void PriorityActions(int frame, PlayerMap &playerMap, USimWorld &world)
{
    EActions action;
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
        playerData->aiController.lastActionSucceeded = false;
        action = playerData->abstractPlayerData.action->m_action;
        
        switch(action)
        {
            case EActions::attack:
                DoAttackAction(playerData, playerMap, world);
                break;
            case EActions::useRoom:
                break;
            case EActions::goToLibrary:
                break;
            case EActions::goToGym:
                break;
            case EActions::goToCircuitTrack:
                break;
            case EActions::goToBedroom:
                break;
            case EActions::goToMainHall:
                break;
            case EActions::makeFriends:
                break;
            case EActions::offerMission:
                break;
            case EActions::pickUpItemByPtr:
                break;
            case EActions::pickUpItemByType:
                break;
            case EActions::dropItem:
                break;
            case EActions::evade:
                playerData->abstractPlayerData.narrative = "evade";
                break;
            case EActions::requestItem:
                break;
            case EActions::acceptRequest:
                break;
            case EActions::declineRequest:
                break;
            case EActions::noAction:
                break;
        }
    }
}

void Act(UPlayerData* playerPtr, int frame, PlayerMap &playerMap, USimWorld &world)
{
    EActions action = playerPtr->abstractPlayerData.action->m_action;
    if (playerPtr->abstractPlayerData.attacked && action != EActions::attack && action != EActions::evade)
    {
        playerPtr->abstractPlayerData.narrative = "attempted action " + ActionToString(action) + " but was attacked and lost their turn.";
        return;
    }
    
    switch(action)
    {
        case EActions::attack:
            break;
        case EActions::evade:
            break;
        case EActions::goToBedroom:
            if (playerPtr->abstractPlayerData.locationClass.location == ELocations::bedroom)
            {
                playerPtr->abstractPlayerData.narrative = "tries to go to the bedroom, but is already there!";
            } else
            {
                if (playerPtr->abstractPlayerData.locationClass.location == ELocations::mainHall)
                {
                    playerPtr->abstractPlayerData.narrative = "goes to the bedroom.";
                    playerPtr->abstractPlayerData.locationClass.location = ELocations::bedroom;
                    playerPtr->aiController.lastActionSucceeded = true;
                } else
                {
                    playerPtr->abstractPlayerData.narrative = "tries to go to the bedroom, but is too far away.";
                }
            }
            break;
        case EActions::goToCircuitTrack:
            if (playerPtr->abstractPlayerData.locationClass.location == ELocations::circuitTrack)
            {
                playerPtr->abstractPlayerData.narrative = "tries to go to the circuit track, but is already there!";
            } else
            {
                if (playerPtr->abstractPlayerData.locationClass.location == ELocations::mainHall)
                {
                    playerPtr->abstractPlayerData.narrative = "goes to the circuit track.";
                    playerPtr->abstractPlayerData.locationClass.location = ELocations::circuitTrack;
                    playerPtr->aiController.lastActionSucceeded = true;
                } else
                {
                    playerPtr->abstractPlayerData.narrative = "tries to go to the circuit track, but is too far away.";
                }
            }
            break;
        case EActions::goToGym:
            if (playerPtr->abstractPlayerData.locationClass.location == ELocations::gym)
            {
                playerPtr->abstractPlayerData.narrative = "tries to go to the gym, but is already there!";
            } else
            {
                if (playerPtr->abstractPlayerData.locationClass.location == ELocations::mainHall)
                {
                    playerPtr->abstractPlayerData.narrative = "goes to the gym.";
                    playerPtr->abstractPlayerData.locationClass.location = ELocations::gym;
                    playerPtr->aiController.lastActionSucceeded = true;
                } else
                {
                    playerPtr->abstractPlayerData.narrative = "tries to go to the gym, but is too far away.";
                }
            }
            break;
        case EActions::goToLibrary:
            if (playerPtr->abstractPlayerData.locationClass.location == ELocations::library)
            {
                playerPtr->abstractPlayerData.narrative = "tries to go to the library, but is already there!";
            } else
            {
                if (playerPtr->abstractPlayerData.locationClass.location == ELocations::mainHall)
                {
                    playerPtr->abstractPlayerData.narrative = "goes to the library.";
                    playerPtr->abstractPlayerData.locationClass.location = ELocations::library;
                    playerPtr->aiController.lastActionSucceeded = true;
                } else
                {
                    playerPtr->abstractPlayerData.narrative = "tries to go to the library, but is too far away.";
                }
            }
            break;
        case EActions::goToMainHall:
            if (playerPtr->abstractPlayerData.locationClass.location == ELocations::mainHall)
            {
                playerPtr->abstractPlayerData.narrative = "tries to go to the main hall, but is already there!";
            } else
            {
                playerPtr->abstractPlayerData.narrative = "goes to the main hall.";
                playerPtr->abstractPlayerData.locationClass.location = ELocations::mainHall;
                playerPtr->aiController.lastActionSucceeded = true;
            }
            break;
        case EActions::useRoom:
            DoUseRoomAction(playerPtr, playerMap, world);
            break;
        case EActions::makeFriends:
            DoMakeFriendsAction(playerPtr, playerMap, world);
            break;
        case EActions::offerMission:
            DoOfferMissionAction(playerPtr, playerMap, world);
            break;
        case EActions::pickUpItemByPtr:
            DoPickUpItemAction(playerPtr, playerMap, world);
            break;
        case EActions::pickUpItemByType:
            ThrowException("Textworld handling not implemented for Actions::pickUpItemByType");
            break;
        case EActions::dropItem:
            DoDropItemAction(playerPtr, playerMap, world);
            break;
        case EActions::requestItem:
            DoRequestItemAction(playerPtr, playerMap, world);
            break;
        case EActions::acceptRequest:
            ThrowException("ERROR: 'ACCEPT REQUEST' IS NOT AN MAIN TURN ACTION");
            playerPtr->abstractPlayerData.narrative = "ERROR: 'ACCEPT REQUEST' IS NOT AN MAIN TURN ACTION";
            playerPtr->aiController.lastActionSucceeded = false;
            break;
        case EActions::declineRequest:
            ThrowException("ERROR: 'DECLINE REQUEST' IS NOT AN MAIN TURN ACTION");
            playerPtr->abstractPlayerData.narrative = "ERROR: 'DECLINE REQUEST' IS NOT AN MAIN TURN ACTION";
            playerPtr->aiController.lastActionSucceeded = false;
            break;
        case EActions::noAction:
            ThrowException("ERROR NO ACTION.");
            playerPtr->abstractPlayerData.narrative = "ERROR NO ACTION.";
            playerPtr->aiController.lastActionSucceeded = false;
            break;
    }
}

void Display(PlayerMap &playerMap, int frame)
{
    std::stringstream ss;
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
        ss << frame << ": " << playerData->abstractPlayerData.m_playerName << " tries to " << playerData->abstractPlayerData.action->ToString() << " while in the " << playerData->abstractPlayerData.lastLocationClass.ToString() << ": " << playerData->abstractPlayerData.narrative << "\n";
    }
    pLog(ss, true);
}

void AggroCooldown(PlayerMap &playerMap)
{
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
        for(auto relIter = playerData->relMap.cbegin(); relIter != playerData->relMap.cend(); ++relIter)
        {
            URelationship* rel = relIter->second;
            if (rel != nullptr) {
                rel->deltaAggro(-c_aggroCooldown);
            }
        }
    }
}

void CleanUpFrame(const PlayerMap &playerMap)
{
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
        playerData->abstractPlayerData.narrative = "";
        playerData->abstractPlayerData.attacked = false;
        playerData->abstractPlayerData.lastAction = playerData->abstractPlayerData.action;
        playerData->abstractPlayerData.lastLocationClass.location = playerData->abstractPlayerData.locationClass.location;
    }
}

void Simulate()
{
    // Setup
    USimWorld world;  // TODO world.playerRegistry.m_playerMap.size != 0.  Looks like it somehow isn't getting constructed / initialized.
    UPlayerRegistry& registry = world.playerRegistry;
    PlayerMap& map = registry.m_playerMap;
    int map_size = map.size();
    world.items.push_back(new Item(EItemType::extinguisher, ELocations::mainHall));
    int map_size2 = map.size();
    world.items.push_back(new Item(EItemType::bottle      , ELocations::mainHall));
    int map_size3 = map.size();
    world.items.push_back(new Item(EItemType::hammer      , ELocations::circuitTrack));
    int map_size4 = map.size();
    world.items.push_back(new Item(EItemType::ball        , ELocations::mainHall));
    int map_size5 = map.size();
    world.items.push_back(new Item(EItemType::mirror      , ELocations::bedroom));
    int map_size6 = map.size();
    world.items.push_back(new Item(EItemType::rock        , ELocations::library));
    int map_size7 = map.size();
    
    //Add players
    {
        UPlayerData* player;

        player = new UPlayerData();
        player->aiController = AIController(AI::htnAI);
        player->abstractPlayerData.missionClass = std::make_shared<MissionClass>(&(player->abstractPlayerData));
        world.playerRegistry.RegisterPlayer(player);
        map_size = map.size();
        
        player = new UPlayerData();
        player->abstractPlayerData.m_playerName = "Thomas";
        player->aiController = AIController(AI::humanAI);
        player->abstractPlayerData.missionClass = std::make_shared<MissionClass>(&(player->abstractPlayerData));
        world.playerRegistry.RegisterPlayer(player);
        map_size2 = map.size();
        
        player = new UPlayerData();
        player->aiController = AIController(AI::htnAI);
        player->abstractPlayerData.missionClass = std::make_shared<MissionClass>(&(player->abstractPlayerData));
        world.playerRegistry.RegisterPlayer(player);
        map_size3 = map.size();
    }
    map_size4 = map.size();

    std::cout << "map_size=" << map_size << ", map_size2"<< map_size2 << ", map_size3"<< map_size3 << ", map_size4"<< map_size4 << ", map_size5"<< map_size5 << ", map_size6"<< map_size6 << ", map_size7"<< map_size7 << "\n";
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    
    //print initial missions
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        UPlayerData* player = dynamic_cast<UPlayerData*>(playerIter->second);
        pLog(player->abstractPlayerData.missionClass->MissionNarrative(), true);
    }
    
    // loop one time step at a time
    for (int frame=0; true; frame++)
    {
        CleanUpFrame(playerMap);
        
        world.Clean();
        
        for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
        {
            UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
            playerData->abstractPlayerData.action = playerData->aiController.ChooseAction(*playerData, world);
        }
        
        PriorityActions(frame, playerMap, world); //mainly for resolving clashes and attacks, ie conflict.
        
        for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
        {
            UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
            Act(playerData, frame, playerMap, world);
        }
        
        world.WorldEffects();
        AggroCooldown(playerMap);
        
        for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
        {
            UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
            playerData->UpdateMissions(world);
        }
        
        Display(playerMap, frame);
    }
    world.Clean();
    world.FullDisplay();
    
    for(auto playerIter = playerMap.cbegin(); playerIter != playerMap.cend(); ++playerIter)
    {
        int key = playerIter->first;
        UPlayerData* playerData = dynamic_cast<UPlayerData*>(playerIter->second);
        world.playerRegistry.DeregisterPlayer(key);
        delete playerData;
    }
    
    PlayerMap::iterator iter = playerMap.begin();
    while (iter != playerMap.end()) {
       PlayerMap::iterator toErase = iter;
       ++iter;
       playerMap.erase(toErase);
    }
}

int main(int argc, char **argv)
{
    unsigned int randomSeed = static_cast<unsigned int>(time(NULL));
    randomSeed = 1536439609;
    srand(randomSeed);
    std::stringstream ss;
    ss << "Random seed = " << randomSeed << "\n";
    pLog(ss);
    Simulate();
    return 0;
}