#include "Actions.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "Item.h"
#include "Missions.h"

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap)
{
    if ((otherPlayerPtr->locationClass.location == playerPtr->locationClass.location) && (otherPlayerPtr != playerPtr))
        return true;
    else
        return false;
}

void DoAttackAction(UPlayerData* attackingPlayerPtr, PlayerMap &playerMap, USimWorld &world)
{
    AttackAction* action = dynamic_cast<AttackAction*>(attackingPlayerPtr->action.get());
    UPlayerData* defendingPlayerPtr = action->m_targetPlayer;
    RelMap relMap = defendingPlayerPtr->relMap;
    int key = attackingPlayerPtr->m_key;
    URelationship* rel = relMap[key];
    URelationship* defendToAttackRelPtr = rel;
    if (defendingPlayerPtr == nullptr)
    {
        ThrowException("ERROR: tried to attack NULLPTR player.");
        attackingPlayerPtr->narrative = "ERROR: tried to attack NULLPTR player.";
        return;
    }
    if (defendingPlayerPtr == attackingPlayerPtr)
    {
        ThrowException("ERROR: attacker failed to specify a valid target. Target is self.");
        attackingPlayerPtr->narrative = "ERROR: attacker failed to specify a valid target. Target is self.";
        return;
    }
    if (attackingPlayerPtr->locationClass.location == defendingPlayerPtr->locationClass.location)
    {
        defendToAttackRelPtr->deltaAggro(15);
        defendToAttackRelPtr->deltaPlotImportance(1);
        defendToAttackRelPtr->deltaFriendliness(-1);
        if ((defendingPlayerPtr->action->m_action == EActions::evade && rand()%100 < 90) || (defendingPlayerPtr->lastAction->m_action == EActions::evade && rand()%100 < 40))
        {
            defendToAttackRelPtr->deltaFear(-0.01);
            defendToAttackRelPtr->deltaThreat(0.2);
            attackingPlayerPtr->narrative = "tried to attack player " + defendingPlayerPtr->m_playerName + " but failed because he fled.";
        } else
        {
            defendingPlayerPtr->pStats.deltaHealth(-1);
            defendingPlayerPtr->pStats.deltaSanity(-0.5);
            defendToAttackRelPtr->deltaFear(0.1);
            defendToAttackRelPtr->deltaThreat(1);
            defendingPlayerPtr->attacked = true;
            attackingPlayerPtr->narrative = "attacks player " + defendingPlayerPtr->m_playerName + " who now has " + FormatDouble(defendingPlayerPtr->pStats.getHealth()) + " health";
            attackingPlayerPtr->aiController.lastActionSucceeded = true;
        }
    } else
    {
        attackingPlayerPtr->narrative = "tries to attack player " + defendingPlayerPtr->m_playerName + " who is not even in the same room.";
    }
}

void DoWeightliftAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.weightsOccupied == nullptr)
    {
        world.weightsOccupied = playerPtr;
        playerPtr->narrative = "uses the gym";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->narrative = "attempts to weightlift, but the weights are already in use; strength = " + FormatDouble(playerPtr->pStats.getStrength());
    }
}

void DoCircuitsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.circuitsOccupied == nullptr)
    {
        world.circuitsOccupied = playerPtr;
        playerPtr->narrative = "uses the circuit track";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->narrative = "attempts to do circuits, but the track is already in use; agility = " + FormatDouble(playerPtr->pStats.getAgility());
    }
}

void DoStudyAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.studyOccupied == nullptr)
    {
        world.studyOccupied = playerPtr;
        playerPtr->narrative = "uses the library";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->narrative = "attempts to study, but the library seat is already taken; intelligence = " + FormatDouble(playerPtr->pStats.getIntelligence());
    }
}

void DoSleepAction(UPlayerData* playerPtr, PlayerMap& playerMap, USimWorld &world)
{
    if (world.bedOccupied == nullptr)
    {
        world.bedOccupied = playerPtr;
        playerPtr->narrative = "tries to use the bedroom";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->narrative = "tried to sleep, but the bed was occupied; health = " + FormatDouble(playerPtr->pStats.getHealth());
    }
}

void DoUseRoomAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    switch (playerPtr->locationClass.location)
    {
        case ELocations::bedroom:
            DoSleepAction(playerPtr, playerMap, world);
            break;
        case ELocations::gym:
            DoWeightliftAction(playerPtr, playerMap, world);
            break;
        case ELocations::circuitTrack:
            DoCircuitsAction(playerPtr, playerMap, world);
            break;
        case ELocations::library:
            DoStudyAction(playerPtr, playerMap, world);
            break;
        case ELocations::mainHall:
            playerPtr->narrative = "tries to use the main hall, but there's nothing here to use.";
            break;
    }
}

void DoOfferMissionAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    OfferMissionAction* action = dynamic_cast<OfferMissionAction*>(playerPtr->action.get());
    UPlayerData* targetPlayer = dynamic_cast<UPlayerData*>(action->m_targetPlayer);
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to offer a mission to an invalid player index.");
        playerPtr->narrative = "ERROR: tried to offer a mission to an invalid player index.";
    } else if (playerPtr == targetPlayer)
    {
        ThrowException("ERROR: tried to offer a mission to himself.");
        playerPtr->narrative = "ERROR: tried to offer a mission to himself.";
    } else if (OtherInReach(playerPtr, targetPlayer, playerMap))
    {
        targetPlayer->missionClass = action->m_offeredMission;
        playerPtr->narrative = "offers a mission to " + targetPlayer->missionClass->MissionName() + " to " + targetPlayer->m_playerName;
        playerPtr->aiController.lastActionSucceeded = true;
    } else
        playerPtr->narrative = "tries to offer a mission to " + targetPlayer->m_playerName + ", but he's not here.";
}

void DoMakeFriendsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    MakeFriendsAction* action = dynamic_cast<MakeFriendsAction*>(playerPtr->action.get());
    UPlayerData* targetPlayer = dynamic_cast<UPlayerData*>(action->m_targetPlayer);
    URelationship* receipientToYouRelPtr = targetPlayer->relMap[playerPtr->m_key];
    URelationship* youToRecipientRelPtr = playerPtr->relMap[targetPlayer->m_key];
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to make friends with an an invalid player index.");
        playerPtr->narrative = "ERROR: tried to make friends with an an invalid player index.";
    } else if (playerPtr == targetPlayer)
    {
        ThrowException("ERROR: tried to make friends with himself.");
        playerPtr->narrative = "ERROR: tried to make friends with himself.";
    } else if (OtherInReach(playerPtr, targetPlayer, playerMap))
    {
        if (receipientToYouRelPtr->getAggro() + 50 < RandPercent())
        {
            receipientToYouRelPtr->deltaFriendliness(30);
            youToRecipientRelPtr->deltaFriendliness(30);
            playerPtr->narrative = "makes friends with " + targetPlayer->m_playerName + ": Friendliness = " + FormatDouble(receipientToYouRelPtr->getFriendliness());
            playerPtr->aiController.lastActionSucceeded = true;
        } else
        {
            playerPtr->narrative = "tries to make friends with " + targetPlayer->m_playerName + " but is rejected";
        }
    } else
        playerPtr->narrative = "tries to make friends with " + targetPlayer->m_playerName + ", but he's not here.";
}

void DoPickUpItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    PickUpItemByPtrAction* action = dynamic_cast<PickUpItemByPtrAction*>(playerPtr->action.get());
    Item* targetItem = dynamic_cast<Item*>(action->m_itemFocusPtr);
    if (playerPtr->itemPtr != nullptr)
    {
        ThrowException("ERROR: tried to pick up an item, but was already carrying something.");
        playerPtr->narrative = "ERROR: tried to pick up an item, but was already carrying something.";
        return;
    }
    
    if (targetItem != nullptr)
    {
        if (playerPtr->locationClass.location == action->m_itemFocusPtr->m_locationClass.location)
        {
            if (action->m_itemFocusPtr->m_carryingPlayer == nullptr)
            {
                playerPtr->itemPtr = targetItem;
                action->m_itemFocusPtr->m_carryingPlayer = playerPtr;
                playerPtr->narrative = "picked up a " + targetItem->ToString() + " in the " + targetItem->m_locationClass.ToString() + ".";
                playerPtr->aiController.lastActionSucceeded = true;
            } else {
                playerPtr->narrative = "ERROR: tried to pick up a " + targetItem->ToString() + " but " + targetItem->m_carryingPlayer->m_playerName + " was already carrying it.";
            }
        } else {
            ThrowException("ERROR: tried to pick up a " + targetItem->ToString() + " but it was in the " + targetItem->m_locationClass.ToString() + " while he was in the " + playerPtr->locationClass.ToString() + ".");
            playerPtr->narrative = "ERROR: tried to pick up a " + targetItem->ToString() + " but it was in the " + targetItem->m_locationClass.ToString() + " while he was in the " + playerPtr->locationClass.ToString() + ".";
        }
    } else {
        ThrowException("ERROR: tried to pick up an item, but didn't specify which.");
        playerPtr->narrative = "ERROR: tried to pick up an item, but didn't specify which.";
    }
}

void DoDropItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (playerPtr->itemPtr != nullptr)
    {
        playerPtr->itemPtr->m_locationClass.location = playerPtr->locationClass.location;
        playerPtr->narrative = "Dropped a " + playerPtr->itemPtr->ToString() + " in the " + playerPtr->itemPtr->m_locationClass.ToString() + ".";
        playerPtr->itemPtr->m_carryingPlayer = nullptr;
        playerPtr->itemPtr = nullptr;
        playerPtr->aiController.lastActionSucceeded = true;
    } else {
        ThrowException("ERROR: tried to drop up an item, but no item is being carried.");
        playerPtr->narrative = "ERROR: tried to drop up an item, but no item is being carried.";
    }
}

void DoRequestItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    RequestItemAction* action = dynamic_cast<RequestItemAction*>(playerPtr->action.get());
    UPlayerData* targetPlayer = action->m_targetPlayer;
    if (targetPlayer == playerPtr)
    {
        ThrowException("ERROR: " + playerPtr->m_playerName + " tried to request an item from himself.");
        playerPtr->narrative = "ERROR: " + playerPtr->m_playerName + " tried to request an item from himself.";
        return;
    }
    if (playerPtr->itemPtr != nullptr)
    {
        ThrowException("ERROR: tried to request an item but is already carrying a " + playerPtr->itemPtr->ToString() + ".");
        playerPtr->narrative = "ERROR: tried to request an item but is already carrying a " + playerPtr->itemPtr->ToString() + ".";
        return;
    }
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to request an item but didn't specify who to ask.");
        playerPtr->narrative = "ERROR: tried to request an item but didn't specify who to ask.";
        return;
    }
    if (targetPlayer->locationClass.location != playerPtr->locationClass.location)
    {
        playerPtr->narrative = "ERROR: tried to request an item from " + targetPlayer->m_playerName + ", but he isn't even in the same room.";
        return;
    }
    if (targetPlayer->itemPtr == nullptr)
    {
        playerPtr->narrative = "ERROR: tried to request an item from " + targetPlayer->m_playerName + ", but " + targetPlayer->m_playerName + " is not carrying anything.";
        return;
    }
    playerPtr->narrative = "Says: 'Hey " + targetPlayer->m_playerName + ", can I have that " + targetPlayer->itemPtr->ToString() + " you're carrying?'\n";
    if (targetPlayer->aiController.RespondToOffer(*targetPlayer, world, playerPtr->m_key))
    {
        targetPlayer->itemPtr->m_carryingPlayer = playerPtr;
        playerPtr->itemPtr = targetPlayer->itemPtr;
        targetPlayer->itemPtr = nullptr;
        playerPtr->narrative += "Request success! " + targetPlayer->m_playerName + " has given " + playerPtr->m_playerName + " the " + playerPtr->itemPtr->ToString() + ".";
        playerPtr->aiController.lastActionSucceeded = true;
    } else {
        playerPtr->narrative += "Request was declined.";
    }
}