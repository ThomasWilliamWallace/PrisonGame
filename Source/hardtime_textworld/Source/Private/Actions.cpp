#include "Actions.h"
#include "AbstractPlayerData.h"
#include "SimWorld.h"
#include "Item.h"

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap)
{
    if ((otherPlayerPtr->abstractPlayerData.locationClass.location == playerPtr->abstractPlayerData.locationClass.location) && (otherPlayerPtr != playerPtr))
        return true;
    else
        return false;
}

void DoAttackAction(UPlayerData* attackingPlayerPtr, PlayerMap &playerMap, USimWorld &world)
{
    AttackAction* action = dynamic_cast<AttackAction*>(attackingPlayerPtr->abstractPlayerData.action.get());
    UPlayerData* defendingPlayerPtr = action->m_targetPlayer->m_parentPlayerData;
    RelMap relMap = defendingPlayerPtr->relMap;
    int key = attackingPlayerPtr->abstractPlayerData.m_key;
    URelationship* rel = relMap[key];
    URelationship* defendToAttackRelPtr = rel;
    if (defendingPlayerPtr == nullptr)
    {
        ThrowException("ERROR: tried to attack NULLPTR player.");
        attackingPlayerPtr->abstractPlayerData.narrative = "ERROR: tried to attack NULLPTR player.";
        return;
    }
    if (defendingPlayerPtr == attackingPlayerPtr)
    {
        ThrowException("ERROR: attacker failed to specify a valid target. Target is self.");
        attackingPlayerPtr->abstractPlayerData.narrative = "ERROR: attacker failed to specify a valid target. Target is self.";
        return;
    }
    if (attackingPlayerPtr->abstractPlayerData.locationClass.location == defendingPlayerPtr->abstractPlayerData.locationClass.location)
    {
        defendToAttackRelPtr->deltaAggro(15);
        defendToAttackRelPtr->deltaPlotImportance(1);
        defendToAttackRelPtr->deltaFriendliness(-1);
        if ((defendingPlayerPtr->abstractPlayerData.action->m_action == EActions::evade && rand()%100 < 90) || (defendingPlayerPtr->abstractPlayerData.lastAction->m_action == EActions::evade && rand()%100 < 40))
        {
            defendToAttackRelPtr->deltaFear(-0.01);
            defendToAttackRelPtr->deltaThreat(0.2);
            attackingPlayerPtr->abstractPlayerData.narrative = "tried to attack player " + defendingPlayerPtr->abstractPlayerData.m_playerName + " but failed because he fled.";
        } else
        {
            defendingPlayerPtr->abstractPlayerData.pStats.deltaHealth(-1);
            defendingPlayerPtr->abstractPlayerData.pStats.deltaSanity(-0.5);
            defendToAttackRelPtr->deltaFear(0.1);
            defendToAttackRelPtr->deltaThreat(1);
            defendingPlayerPtr->abstractPlayerData.attacked = true;
            attackingPlayerPtr->abstractPlayerData.narrative = "attacks player " + defendingPlayerPtr->abstractPlayerData.m_playerName + " who now has " + FormatDouble(defendingPlayerPtr->abstractPlayerData.pStats.getHealth()) + " health";
            attackingPlayerPtr->aiController.lastActionSucceeded = true;
        }
    } else
    {
        attackingPlayerPtr->abstractPlayerData.narrative = "tries to attack player " + defendingPlayerPtr->abstractPlayerData.m_playerName + " who is not even in the same room.";
    }
}

void DoWeightliftAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.weightsOccupied == nullptr)
    {
        world.weightsOccupied = playerPtr;
        playerPtr->abstractPlayerData.narrative = "uses the gym";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->abstractPlayerData.narrative = "attempts to weightlift, but the weights are already in use; strength = " + FormatDouble(playerPtr->abstractPlayerData.pStats.getStrength());
    }
}

void DoCircuitsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.circuitsOccupied == nullptr)
    {
        world.circuitsOccupied = playerPtr;
        playerPtr->abstractPlayerData.narrative = "uses the circuit track";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->abstractPlayerData.narrative = "attempts to do circuits, but the track is already in use; agility = " + FormatDouble(playerPtr->abstractPlayerData.pStats.getAgility());
    }
}

void DoStudyAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (world.studyOccupied == nullptr)
    {
        world.studyOccupied = playerPtr;
        playerPtr->abstractPlayerData.narrative = "uses the library";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->abstractPlayerData.narrative = "attempts to study, but the library seat is already taken; intelligence = " + FormatDouble(playerPtr->abstractPlayerData.pStats.getIntelligence());
    }
}

void DoSleepAction(UPlayerData* playerPtr, PlayerMap& playerMap, USimWorld &world)
{
    if (world.bedOccupied == nullptr)
    {
        world.bedOccupied = playerPtr;
        playerPtr->abstractPlayerData.narrative = "tries to use the bedroom";
        playerPtr->aiController.lastActionSucceeded = true;
    } else
    {
        playerPtr->abstractPlayerData.narrative = "tried to sleep, but the bed was occupied; health = " + FormatDouble(playerPtr->abstractPlayerData.pStats.getHealth());
    }
}

void DoUseRoomAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    switch (playerPtr->abstractPlayerData.locationClass.location)
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
            playerPtr->abstractPlayerData.narrative = "tries to use the main hall, but there's nothing here to use.";
            break;
    }
}

void DoOfferMissionAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    OfferMissionAction* action = dynamic_cast<OfferMissionAction*>(playerPtr->abstractPlayerData.action.get());
    UPlayerData* targetPlayer = dynamic_cast<UPlayerData*>(action->m_targetPlayer);
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to offer a mission to an invalid player index.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to offer a mission to an invalid player index.";
    } else if (playerPtr == targetPlayer)
    {
        ThrowException("ERROR: tried to offer a mission to himself.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to offer a mission to himself.";
    } else if (OtherInReach(playerPtr, targetPlayer, playerMap))
    {
        targetPlayer->abstractPlayerData.missionClass = action->m_offeredMission;
        playerPtr->abstractPlayerData.narrative = "offers a mission to " + targetPlayer->abstractPlayerData.missionClass->MissionName() + " to " + targetPlayer->abstractPlayerData.m_playerName;
        playerPtr->aiController.lastActionSucceeded = true;
    } else
        playerPtr->abstractPlayerData.narrative = "tries to offer a mission to " + targetPlayer->abstractPlayerData.m_playerName + ", but he's not here.";
}

void DoMakeFriendsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    MakeFriendsAction* action = dynamic_cast<MakeFriendsAction*>(playerPtr->abstractPlayerData.action.get());
    UPlayerData* targetPlayer = dynamic_cast<UPlayerData*>(action->m_targetPlayer);
    URelationship* receipientToYouRelPtr = targetPlayer->relMap[playerPtr->abstractPlayerData.m_key];
    URelationship* youToRecipientRelPtr = playerPtr->relMap[targetPlayer->abstractPlayerData.m_key];
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to make friends with an an invalid player index.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to make friends with an an invalid player index.";
    } else if (playerPtr == targetPlayer)
    {
        ThrowException("ERROR: tried to make friends with himself.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to make friends with himself.";
    } else if (OtherInReach(playerPtr, targetPlayer, playerMap))
    {
        if (receipientToYouRelPtr->getAggro() + 50 < RandPercent())
        {
            receipientToYouRelPtr->deltaFriendliness(30);
            youToRecipientRelPtr->deltaFriendliness(30);
            playerPtr->abstractPlayerData.narrative = "makes friends with " + targetPlayer->abstractPlayerData.m_playerName + ": Friendliness = " + FormatDouble(receipientToYouRelPtr->getFriendliness());
            playerPtr->aiController.lastActionSucceeded = true;
        } else
        {
            playerPtr->abstractPlayerData.narrative = "tries to make friends with " + targetPlayer->abstractPlayerData.m_playerName + " but is rejected";
        }
    } else
        playerPtr->abstractPlayerData.narrative = "tries to make friends with " + targetPlayer->abstractPlayerData.m_playerName + ", but he's not here.";
}

void DoPickUpItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    PickUpItemByPtrAction* action = dynamic_cast<PickUpItemByPtrAction*>(playerPtr->abstractPlayerData.action.get());
    Item* targetItem = dynamic_cast<Item*>(action->m_itemFocusPtr);
    if (playerPtr->itemPtr != nullptr)
    {
        ThrowException("ERROR: tried to pick up an item, but was already carrying something.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to pick up an item, but was already carrying something.";
        return;
    }
    
    if (targetItem != nullptr)
    {
        if (playerPtr->abstractPlayerData.locationClass.location == action->m_itemFocusPtr->m_locationClass.location)
        {
            if (action->m_itemFocusPtr->m_carryingPlayer == nullptr)
            {
                playerPtr->itemPtr = targetItem;
                action->m_itemFocusPtr->m_carryingPlayer = &(playerPtr->abstractPlayerData);
                playerPtr->abstractPlayerData.narrative = "picked up a " + targetItem->ToString() + " in the " + targetItem->m_locationClass.ToString() + ".";
                playerPtr->aiController.lastActionSucceeded = true;
            } else {
                playerPtr->abstractPlayerData.narrative = "ERROR: tried to pick up a " + targetItem->ToString() + " but " + targetItem->m_carryingPlayer->m_playerName + " was already carrying it.";
            }
        } else {
            ThrowException("ERROR: tried to pick up a " + targetItem->ToString() + " but it was in the " + targetItem->m_locationClass.ToString() + " while he was in the " + playerPtr->abstractPlayerData.locationClass.ToString() + ".");
            playerPtr->abstractPlayerData.narrative = "ERROR: tried to pick up a " + targetItem->ToString() + " but it was in the " + targetItem->m_locationClass.ToString() + " while he was in the " + playerPtr->abstractPlayerData.locationClass.ToString() + ".";
        }
    } else {
        ThrowException("ERROR: tried to pick up an item, but didn't specify which.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to pick up an item, but didn't specify which.";
    }
}

void DoDropItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    if (playerPtr->itemPtr != nullptr)
    {
        playerPtr->itemPtr->m_locationClass.location = playerPtr->abstractPlayerData.locationClass.location;
        playerPtr->abstractPlayerData.narrative = "Dropped a " + playerPtr->itemPtr->ToString() + " in the " + playerPtr->itemPtr->m_locationClass.ToString() + ".";
        playerPtr->itemPtr->m_carryingPlayer = nullptr;
        playerPtr->itemPtr = nullptr;
        playerPtr->aiController.lastActionSucceeded = true;
    } else {
        ThrowException("ERROR: tried to drop up an item, but no item is being carried.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to drop up an item, but no item is being carried.";
    }
}

void DoRequestItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world)
{
    RequestItemAction* action = dynamic_cast<RequestItemAction*>(playerPtr->abstractPlayerData.action.get());
    UPlayerData* targetPlayer = action->m_targetPlayer->m_parentPlayerData;
    if (targetPlayer == playerPtr)
    {
        ThrowException("ERROR: " + playerPtr->abstractPlayerData.m_playerName + " tried to request an item from himself.");
        playerPtr->abstractPlayerData.narrative = "ERROR: " + playerPtr->abstractPlayerData.m_playerName + " tried to request an item from himself.";
        return;
    }
    if (playerPtr->itemPtr != nullptr)
    {
        ThrowException("ERROR: tried to request an item but is already carrying a " + playerPtr->itemPtr->ToString() + ".");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to request an item but is already carrying a " + playerPtr->itemPtr->ToString() + ".";
        return;
    }
    if (targetPlayer == nullptr)
    {
        ThrowException("ERROR: tried to request an item but didn't specify who to ask.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to request an item but didn't specify who to ask.";
        return;
    }
    if (targetPlayer->abstractPlayerData.locationClass.location != playerPtr->abstractPlayerData.locationClass.location)
    {
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to request an item from " + targetPlayer->abstractPlayerData.m_playerName + ", but he isn't even in the same room.";
        return;
    }
    if (targetPlayer->itemPtr == nullptr)
    {
        ThrowException("ERROR: tried to request an item from " + targetPlayer->abstractPlayerData.m_playerName + ", but " + targetPlayer->abstractPlayerData.m_playerName + " is not carrying anything.");
        playerPtr->abstractPlayerData.narrative = "ERROR: tried to request an item from " + targetPlayer->abstractPlayerData.m_playerName + ", but " + targetPlayer->abstractPlayerData.m_playerName + " is not carrying anything.";
        return;
    }
    playerPtr->abstractPlayerData.narrative = "Says: 'Hey " + targetPlayer->abstractPlayerData.m_playerName + ", can I have that " + targetPlayer->itemPtr->ToString() + " you're carrying?'\n";
    if (targetPlayer->aiController.RespondToOffer(*targetPlayer, world, playerPtr->abstractPlayerData.m_key))
    {
        targetPlayer->itemPtr->m_carryingPlayer = &(playerPtr->abstractPlayerData);
        playerPtr->itemPtr = targetPlayer->itemPtr;
        targetPlayer->itemPtr = nullptr;
        playerPtr->abstractPlayerData.narrative += "Request success! " + targetPlayer->abstractPlayerData.m_playerName + " has given " + playerPtr->abstractPlayerData.m_playerName + " the " + playerPtr->itemPtr->ToString() + ".";
        playerPtr->aiController.lastActionSucceeded = true;
    } else {
        playerPtr->abstractPlayerData.narrative += "Request was declined.";
    }
}