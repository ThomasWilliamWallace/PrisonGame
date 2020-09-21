#include "BasicAI.h"
#include "AbstractPlayerData.h"
#include <stdexcept>
#include "HTNDomain.h"
#include "RequestHTNDomain.h"
#include "SimWorld.h"
#include "AbstractAction.h"
#include <sstream>
#include "pLog.h"
#include "Constants.h"
#include <vector>
#include "TranslateToHTNWorldState.h"
#include <limits>

EActions AIController::ChooseRoom(AbstractPlayerData& player)
{
    if (player.locationClass.location == ELocations::mainHall)
    {
        int random = RandPercent();
        if (random < 25)
        {
            return EActions::goToLibrary;
        }
        if (random < 50)
        {
            return EActions::goToGym;
        }
        if (random < 75)
        {
            return EActions::goToCircuitTrack;
        }
        return EActions::goToBedroom;
    } else
    {
        return EActions::goToMainHall;
    }
}

std::shared_ptr<BaseAction> AIController::ChooseAction(UPlayerData& player, USimWorld& world)
{
    int playerCount = world.playerRegistry.m_playerMap.size();
    bool playersInReach[playerCount];
    int countPlayersInReach = 0;
    
    for (int i = 0; i < playerCount; i++)
    {
        if (OtherInReach(player.abstractPlayerData, world.playerRegistry.m_playerMap[i]->abstractPlayerData))
        {
            playersInReach[i] = true;
            countPlayersInReach += 1;
        } else
            playersInReach[i] = false;
    }
    
    switch(player.aiController.algo)
    {
        case(AI::doNothingAI):
            return DoNothingAIChooseAction(player, world, playersInReach, countPlayersInReach);
        case(AI::randomAI):
            return RandomAIChooseAction(player, world, playersInReach, countPlayersInReach);
        case(AI::aggroAI):
            return aggroAIChooseAction(player, world, playersInReach, countPlayersInReach);
        case(AI::humanAI):
            return humanAIChooseAction(player, world, playersInReach, countPlayersInReach);
        case(AI::htnAI):
            return htnAIChooseAction(player, world, playersInReach, countPlayersInReach);
		default:
            ThrowException("Selected an invalid AI controller type.");
    }
	return RandomAIChooseAction(player, world, playersInReach, countPlayersInReach);
}

void AIController::CreateMissionOffer(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    double random = RandPercent();
    int target = 0;
    int playerCount = playerMap.size();
    for (int i=0; i < playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                player.missionOffer = std::make_shared<MissionClass>(&(player.abstractPlayerData));
                return;
            }
            target += 1;
        }
    }
}

int AIController::TargetForMakeFriend(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    double random = RandPercent();
    int target = 0;
    int playerCount = playerMap.size();
    for (int i=0; i < playerCount; i++)
    {
        if (playersInReach[i] == true)
        {
            if (random <= (100 * (target + 1) / countPlayersInReach))
            {
                return i;
            }
            target += 1;
        }
    }
    ThrowException("Failed to pick a player in reach to make friends with.");
}

std::shared_ptr<BaseAction> AIController::DoNothingAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    return std::make_shared<BaseAction>(EActions::noAction);
}

std::shared_ptr<BaseAction> AIController::RandomAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    int playerCount = world.playerRegistry.m_playerMap.size();
    if (countPlayersInReach > 0)
    {
        if (RandPercent() < player.abstractPlayerData.pStats.aggression)
        {
            // attack --a random target in the room
            int target = 0;
            double random = RandPercent();
            for (int i = 0; i < playerCount; i++)
            {
                if (playersInReach[i] == true)
                {
                    if (random <= (100 * (target + 1) / countPlayersInReach))
                    {
                        return std::make_shared<AttackAction>(&(playerMap[i]->abstractPlayerData));
                    }
                    target += 1;
                }
            }
            ThrowException("ERROR: FAILED TO FIND ANY TARGET TO RANDOMLY ATTACK");
        } else if (RandPercent() < 25)
        {
            return std::make_shared<BaseAction>(EActions::evade);
        } else if (RandPercent() < 35)
        {
            return std::make_shared<MakeFriendsAction>(&(playerMap[TargetForMakeFriend(player, world, playersInReach, countPlayersInReach)]->abstractPlayerData));
        } else if (RandPercent() < 50)
        {
            return std::make_shared<OfferMissionAction>(&(player.abstractPlayerData), std::make_shared<MissionClass>(&(player.abstractPlayerData)));
        } else
        {
            return std::make_shared<BaseAction>(ChooseRoom(player.abstractPlayerData));
        }
    } else if (RandPercent() < 80) {
        return std::make_shared<BaseAction>(EActions::useRoom);
    } else
    {
        return std::make_shared<BaseAction>(ChooseRoom(player.abstractPlayerData));
    }
    return std::make_shared<BaseAction>(EActions::noAction);
}

std::shared_ptr<BaseAction> AIController::aggroAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    int playerCount = world.playerRegistry.m_playerMap.size();
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    if (countPlayersInReach > 0)
    {
        double aggros[playerCount];
        for (int i = 0; i < playerCount; i++)
        {
            aggros[i] = player.relMap[i]->getAggro() * player.abstractPlayerData.pStats.aggression/100;
        }
        
        double fears[playerCount];
        for (int i = 0; i < playerCount; i++)
        {
            fears[i] = player.relMap[i]->getFear() * (1-(player.abstractPlayerData.pStats.proud/100));
        }
        
        double friendlinesses[playerCount];
        for (int i = 0; i < playerCount; i++)
        {
            friendlinesses[i] = player.relMap[i]->getFriendliness(); // multiply by a friendliness personality constant?
        }
        
        double max_aggro = -1;
        int max_aggro_index = -1;
        double aggroTemp;
        // Choose the most aggro/hostile character to attack
        for (int i = 0; i < playerCount; i++)
        {
            aggroTemp = aggros[i] * (100 - fears[i]) * (100 - friendlinesses[i]) / (100 * 100); // willingness to attack this character. Increases with aggro, decreases with fear.
         //   std::cout << "aggro[" << i << "]=" << aggros[i] << ", fears[" << i << "]=" << fears[i] << ", friendlinesses[" << i << "]=" << friendlinesses[i] << ", aggroTemp=" << aggroTemp << "\n";
            if (aggroTemp > max_aggro)
            {
                max_aggro = aggroTemp;
                max_aggro_index = i;
            }
        }

        if (RandPercent() < (c_aggro_scale * max_aggro * player.abstractPlayerData.pStats.aggression / 100))
        {
			if (RandPercent() < 25)
			{
				return std::make_shared<BaseAction>(EActions::evade);
			} else
			{
				return std::make_shared<AttackAction>(&(playerMap[max_aggro_index]->abstractPlayerData));
			}
        } else if (RandPercent() < 20)
        {
            return std::make_shared<MakeFriendsAction>(&(playerMap[TargetForMakeFriend(player, world, playersInReach, countPlayersInReach)]->abstractPlayerData));
        } else if (RandPercent() < 60)
        {
            return std::make_shared<OfferMissionAction>(&(player.abstractPlayerData), std::make_shared<MissionClass>(&(player.abstractPlayerData)));
        } else
        {
            return std::make_shared<BaseAction>(ChooseRoom(player.abstractPlayerData));
        }
    } else if (RandPercent() < 80)
    {
        return std::make_shared<BaseAction>(EActions::useRoom);
    } else
    {
        return std::make_shared<BaseAction>(ChooseRoom(player.abstractPlayerData));
    }
    return std::make_shared<BaseAction>(EActions::noAction);
}

std::shared_ptr<BaseAction> AIController::htnAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    //update worldstate from real world
    HTNWorldState htnWorldState = TranslateToHTNWorldState(&player, world, world.playerRegistry.m_playerMap, nullptr);
    
    bool hasValidPlan = false;
    // check if next step of the plan is valid.
    
    if (!lastActionSucceeded)
    {
        hasValidPlan = false;
    } else if (htnPlan.size() > 0)
    {
        hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
    }
    
    //If plan is not valid, abandon it and try to make a new plan
    if (!hasValidPlan)
    {
        //make new plan
        std::cout << player.abstractPlayerData.m_playerName << ": Make a new plan:\n";
        HTNWorldState htnWorldStateDFSCopy(htnWorldState);
        HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);
        
        htnPlan = HTNIterative(htnWorldStateDFSCopy, *missionPtr, 0);
        for (auto &htnPrimitive : htnPlan)
        {
            std::cout << htnPrimitive->ToString() << ", ";
        }
        std::cout << "\n";
        
        //once again, check if next step of the plan is valid.
        if (htnPlan.size() > 0)
        {
            hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
        }
    }
    
    if (!hasValidPlan)
    {
        std::cout << player.abstractPlayerData.m_playerName << ": Give up and return noAction\n";
        return std::make_shared<BaseAction>(EActions::noAction); //If next step of the plan is still not valid, then return failure state
    } else {
        //continue with current plan
        HTNPrimitivePtr currentPlanStep = htnPlan.front();
        htnPlan.pop_front();
        return currentPlanStep->Operate(&(player.abstractPlayerData));
    }
}

void resetInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::shared_ptr<BaseAction> AIController::humanAIChooseAction(UPlayerData& player, USimWorld& world, bool playersInReach[], int countPlayersInReach)
{
    int playerCount = world.playerRegistry.m_playerMap.size();
    std::string input;
    int targetPlayer;
    int itemsInRoom;
    int playersInRoom;
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    while (true)
    {
        std::cout << "Choose action:";
        if (!(std::cin >> input)) {
            resetInput();
            std::cout << "Invalid action!\n";
        } else {
            switch(input[0]){
            case 'v':
                std::cout << "Room contains:\n";
                playersInRoom = 0;
                for (int i = 0; i < playerCount; i++)
                {
                    if (playerMap[i]->abstractPlayerData.locationClass.location == player.abstractPlayerData.locationClass.location)
                    {
                        std::cout << "Player \"" << playerMap[i]->abstractPlayerData.m_playerName << "\", (index=" << i << ")\n";
                        playersInRoom += 1;
                    }
                }
                if (playersInRoom == 0)
                {
                    std::cout << "No players in room.\n";
                }
                itemsInRoom = 0;
                for (auto &item : world.items)
                {
                    if (item->m_locationClass.location == player.abstractPlayerData.locationClass.location && item->m_carryingPlayer == nullptr)
                    {
                        std::cout << "Item \"" << item->ToString() << "\", (index=" << itemsInRoom << ")\n";
                        itemsInRoom += 1;
                    }
                }
                if (itemsInRoom == 0)
                {
                    std::cout << "No items in room.\n";
                }
                std::cout << "\n";
                break;
            case 'q':
                exit(0);
            case 'h':
                std::cout << "Commands:\n";
                std::cout << "v: view room\n";
                std::cout << "a: " << ActionToString(EActions::attack) << "\n";
                std::cout << "e: " << ActionToString(EActions::evade) << "\n";
                std::cout << "b: " << ActionToString(EActions::goToBedroom) << "\n";
                std::cout << "c: " << ActionToString(EActions::goToCircuitTrack) << "\n";
                std::cout << "g: " << ActionToString(EActions::goToGym) << "\n";
                std::cout << "l: " << ActionToString(EActions::goToLibrary) << "\n";
                std::cout << "m: " << ActionToString(EActions::goToMainHall) << "\n";
                std::cout << "p: " << ActionToString(EActions::pickUpItemByPtr) << "\n";
                std::cout << "d: " << ActionToString(EActions::dropItem) << "\n";
                std::cout << "f: " << ActionToString(EActions::makeFriends) << "\n";
                std::cout << "o: " << ActionToString(EActions::offerMission) << "\n";
                std::cout << "u: " << ActionToString(EActions::useRoom) << "\n";
                std::cout << "r: " << ActionToString(EActions::requestItem) << "\n";
                std::cout << "h: display help\n";
                std::cout << "q: quit\n";
                break;
            case 'a':
                while (true)
                {
                    std::cout << "Choose target player:";
                    if (!(std::cin >> targetPlayer)) {
                        resetInput();
                        std::cout << "Invalid target player!\n";
                    } else {
                        return std::make_shared<AttackAction>(&(playerMap[targetPlayer]->abstractPlayerData));
                    }
                }
            case 'e': return std::make_shared<BaseAction>(EActions::evade);
            case 'b': return std::make_shared<BaseAction>(EActions::goToBedroom);
            case 'c': return std::make_shared<BaseAction>(EActions::goToCircuitTrack);
            case 'g': return std::make_shared<BaseAction>(EActions::goToGym);
            case 'l': return std::make_shared<BaseAction>(EActions::goToLibrary);
            case 'm': return std::make_shared<BaseAction>(EActions::goToMainHall);
            case 'p': 
                while (true)
                {
                    int targetItem;
                    std::cout << "Choose target item:";
                    if (!(std::cin >> targetItem)) {
                        resetInput();
                        std::cout << "Invalid target item!\n";
                    } else {
                        int itemCountInRoom = 0;
                        int itemIndex = 0;
                        for (auto &item : world.items)
                        {
                            if (item->m_locationClass.location == player.abstractPlayerData.locationClass.location && item->m_carryingPlayer == nullptr)
                            {
                                if (itemCountInRoom == targetItem)
                                {
                                    return std::make_shared<PickUpItemByPtrAction>(world.items.at(itemIndex));
                                }
                                itemCountInRoom += 1;
                            }
                            itemIndex += 1;
                        }
                        std::cout << "ERROR: invalid target item index. Please enter a new action:\n";
                        break;
                    }
                }
                break;
            case 'd': return  std::make_shared<BaseAction>(EActions::dropItem);
            case 'f':
                while (true)
                {
                    std::cout << "Choose target player:";
                    if (!(std::cin >> targetPlayer)) {
                        resetInput();
                        std::cout << "Invalid target player!\n";
                    } else {
                        return std::make_shared<MakeFriendsAction>(&(playerMap[targetPlayer]->abstractPlayerData));
                    }
                }
            case 'o':
                while (true)
                {
                    std::cout << "Choose target player:";
                    if (!(std::cin >> targetPlayer)) {
                        resetInput();
                        std::cout << "Invalid target player!\n";
                    } else {
                        return std::make_shared<OfferMissionAction>(&(playerMap[targetPlayer]->abstractPlayerData), std::make_shared<MissionClass>(&(player.abstractPlayerData)));
                    }
                }
            case 'r':
                while (true)
                {
                    std::cout << "Which player do you request from? ";
                    if (!(std::cin >> targetPlayer)) {
                        resetInput();
                        std::cout << "Invalid target player!\n";
                    } else {
                        UPlayerData* playerData = playerMap[targetPlayer];
                        if (playerData != nullptr) {
                            return std::make_shared<RequestItemAction>(&(playerData->abstractPlayerData));
                        } else {
                            std::cout << "Invalid- target player is nullptr";
                        }
                    }
                }
            case 'u': return std::make_shared<BaseAction>(EActions::useRoom);
            }
        }
    }
    return std::make_shared<BaseAction>(EActions::noAction);
}

AIController::AIController(AI _algo)
{
    algo = _algo;
}

AIController::AIController()
{
    algo = AI::randomAI;
}

bool AIController::RespondToOffer(UPlayerData& player, USimWorld& world, int requesterIndex)
{
    PlayerMap& playerMap = world.playerRegistry.m_playerMap;
    if (algo == AI::humanAI)
    {
        while (true)
        {
            std::string input;
            std::cout << "Y/N? ";
            std::cin >> input;
            switch(input[0])
            {
                case 'Y':
                case 'y':
                    return true;
                case 'N':
                case 'n':
                    return false;
                default:
                    break;
            }
        }
    } else {
        //lastActionSucceeded = false;
        std::cout << player.abstractPlayerData.m_playerName << ": Asked for item, make a new plan:\n";
        
        //update worldstate from real world
        HTNWorldState htnWorldState = TranslateToHTNWorldState(&player, world, world.playerRegistry.m_playerMap, playerMap[requesterIndex]);
        HTNCompound* missionPtr = new StartCompound(htnWorldState);
        
        htnPlan = HTNIterative(htnWorldState, *missionPtr, 0);
        for (auto &htnPrimitive : htnPlan)
        {
            std::cout << htnPrimitive->ToString() << ", ";
        }
        std::cout << "\n";
        
        //check if next step of the plan is valid.
//        bool hasValidPlan = false;
//        if (htnPlan.size() > 0)
//        {
//            hasValidPlan = htnPlan.at(0)->Preconditions(htnWorldState);
//        }

//        if (!hasValidPlan)
//        {
//            std::cout << player[playerIndex].name << "ERROR: Give up and return noAction (from RespondToOffer)\n";
//            exit(0); //If next step of the plan is still not valid, then return failure state
//        } else {
            //continue with current plan
            HTNPrimitivePtr currentPlanStep = htnPlan.back();
            htnPlan.pop_back();
            std::shared_ptr<BaseAction> responseAction = currentPlanStep->Operate(&(player.abstractPlayerData));
            switch(responseAction->m_action)
            {
                case EActions::acceptRequest:
                    return true;
                case EActions::declineRequest:
                    return false;
                default:
                    ThrowException("ERROR: INVALID ACTION '" + ActionToString(responseAction->m_action) + "' GIVEN IN RESPONSE TO AN ITEM REQUEST");
//            }
        }
        return false;
    }
}
