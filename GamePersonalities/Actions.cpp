//
//  Actions.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Actions.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Constants.hpp"

bool OtherInReach(int playerIndex, int otherPlayer, Player player[])
{
    if ((player[otherPlayer].locationClass.location == player[playerIndex].locationClass.location) && (otherPlayer != playerIndex))
        return true;
    else
        return false;
}

std::string ActionToString(Actions action)
{
    switch(action)
    {
        case Actions::evade:
            return "Evade";
        case Actions::attack:
            return "Attack";
        case Actions::useRoom:
            return "UseRoom";
        case Actions::goToGym:
            return "GoToGym";
        case Actions::goToBedroom:
            return "GoToBedroom";
        case Actions::goToLibrary:
            return "GoToLibrary";
        case Actions::goToMainHall:
            return "GoToMainHall";
        case Actions::goToCircuitTrack:
            return "GoToCircuitTrack";
        case Actions::makeFriends:
            return "MakeFriends";
        case Actions::offerMission:
            return "OfferMission";
        case Actions::pickUpItem:
            return "PickUpItem";
        case Actions::dropItem:
            return "DropItem";
        case Actions::requestItem:
            return "RequestItem";
        case Actions::acceptRequest:
            return "acceptRequest";
        case Actions::declineRequest:
            return "declineRequest";
        case Actions::noAction:
            return "ERROR NO ACTION";
    }
    return "ERROR UnrecognisedAction";
}

void AttackAction(int attackerIndex, Player player[], World &world)
{
    int defenderIndex = player[attackerIndex].playerTarget;
    if (playerIndexOutOfBounds(defenderIndex))
    {
        player[attackerIndex].narrative = "ERROR: tried to attack a player with an an invalid player index.";
        return;
    }
    if (defenderIndex == c_empty)
    {
        player[attackerIndex].narrative = "ERROR: attacker failed to specify a valid target. Target is empty.";
        return;
    }
    if (defenderIndex == attackerIndex)
    {
        player[attackerIndex].narrative = "ERROR: attacker failed to specify a valid target. Target is self.";
        return;
    }
    if (player[attackerIndex].locationClass.location == player[defenderIndex].locationClass.location)
    {
        player[defenderIndex].rel[attackerIndex].deltaAggro(15);
        player[defenderIndex].rel[attackerIndex].deltaPlotImportance(1);
        player[defenderIndex].rel[attackerIndex].deltaFriendliness(-1);
        if ((player[defenderIndex].action == Actions::evade && rand()%100 < 90) || (player[defenderIndex].lastAction == Actions::evade && rand()%100 < 40))
        {
            player[defenderIndex].rel[attackerIndex].deltaFear(-0.01);
            player[defenderIndex].rel[attackerIndex].deltaThreat(0.2);
            player[attackerIndex].narrative = "tried to attack player " + player[defenderIndex].name + " but failed because he fled.";
        } else
        {
            player[defenderIndex].stats.deltaHealth(-1);
            player[defenderIndex].stats.deltaSanity(-0.5);
            player[defenderIndex].rel[attackerIndex].deltaFear(0.1);
            player[defenderIndex].rel[attackerIndex].deltaThreat(1);
            player[defenderIndex].attacked = true;
            player[attackerIndex].narrative = "attacks player " + player[defenderIndex].name + " who now has " + FormatDouble(player[defenderIndex].stats.getHealth()) + " health";
            player[attackerIndex].aiController.lastActionSucceeded = true;
        }
    } else
    {
        player[attackerIndex].narrative = "tries to attack player " + player[defenderIndex].name + " who is not even in the same room.";
    }
}

void WeightliftAction(int playerIndex, Player player[], World &world)
{
    if (world.weightsOccupied == c_empty)
    {
        world.weightsOccupied = playerIndex;
        player[playerIndex].narrative = "uses the gym";
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else
    {
        player[playerIndex].narrative = "attempts to weightlift, but the weights are already in use; strength = " + FormatDouble(player[playerIndex].stats.getStrength());
    }
}

void CircuitsAction(int playerIndex, Player player[], World &world)
{
    if (world.circuitsOccupied == c_empty)
    {
        world.circuitsOccupied = playerIndex;
        player[playerIndex].narrative = "uses the circuit track";
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else
    {
        player[playerIndex].narrative = "attempts to do circuits, but the track is already in use; agility = " + FormatDouble(player[playerIndex].stats.getAgility());
    }
}

void StudyAction(int playerIndex, Player player[], World &world)
{
    if (world.studyOccupied == c_empty)
    {
        world.studyOccupied = playerIndex;
        player[playerIndex].narrative = "uses the library";
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else
    {
        player[playerIndex].narrative = "attempts to study, but the library seat is already taken; intelligence = " + FormatDouble(player[playerIndex].stats.getIntelligence());
    }
}

void SleepAction(int playerIndex, Player player[], World &world)
{
    if (world.bedOccupied == c_empty)
    {
        world.bedOccupied = playerIndex;
        player[playerIndex].narrative = "tries to use the bedroom";
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else
    {
        player[playerIndex].narrative = "tried to sleep, but the bed was occupied; health = " + FormatDouble(player[playerIndex].stats.getHealth());
    }
}

void UseRoomAction(int playerIndex, Player player[], World &world)
{
    switch (player[playerIndex].locationClass.location)
    {
        case Locations::bedroom:
            SleepAction(playerIndex, player, world);
            break;
        case Locations::gym:
            WeightliftAction(playerIndex, player, world);
            break;
        case Locations::circuitTrack:
            CircuitsAction(playerIndex, player, world);
            break;
        case Locations::library:
            StudyAction(playerIndex, player, world);
            break;
        case Locations::mainHall:
            player[playerIndex].narrative = "tries to use the main hall, but there's nothing here to use.";
            break;
    }
}

void OfferMissionAction(int playerIndex, Player player[], World &world)
{
    if (playerIndexOutOfBounds(player[playerIndex].playerTarget))
    {
        player[playerIndex].narrative = "ERROR: tried to offer a mission to an invalid player index.";
    } else if (playerIndex == player[playerIndex].playerTarget)
    {
        player[playerIndex].narrative = "ERROR: tried to offer a mission to himself.";
    } else if (OtherInReach(playerIndex, player[playerIndex].playerTarget, player))
    {
        player[player[playerIndex].playerTarget].missionClass = player[playerIndex].missionOffer;
        player[playerIndex].narrative = "offers a mission to " + player[player[playerIndex].playerTarget].missionClass.MissionName() + " to " + player[player[playerIndex].playerTarget].name;
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else
        player[playerIndex].narrative = "tries to offer a mission to " + player[player[playerIndex].playerTarget].name + ", but he's not here.";
}

void MakeFriendsAction(int playerIndex, Player player[], World &world)
{
    if (playerIndexOutOfBounds(player[playerIndex].playerTarget))
    {
        player[playerIndex].narrative = "ERROR: tried to make friends with an an invalid player index.";
    } else if (playerIndex == player[playerIndex].playerTarget)
    {
        player[playerIndex].narrative = "ERROR: tried to make friends with himself.";
    } else if (OtherInReach(playerIndex, player[playerIndex].playerTarget, player))
    {
        if (player[player[playerIndex].playerTarget].rel[playerIndex].getAggro() + 50 < RandPercent())
        {
            player[player[playerIndex].playerTarget].rel[playerIndex].deltaFriendliness(30);
            player[playerIndex].rel[player[playerIndex].playerTarget].deltaFriendliness(30);
            player[playerIndex].narrative = "makes friends with " + player[player[playerIndex].playerTarget].name + ": Friendliness = " + FormatDouble(player[player[playerIndex].playerTarget].rel[playerIndex].getFriendliness());
            player[playerIndex].aiController.lastActionSucceeded = true;
        } else
        {
            player[playerIndex].narrative = "tries to make friends with " + player[player[playerIndex].playerTarget].name + " but is rejected";
        }
    } else
        player[playerIndex].narrative = "tries to make friends with " + player[player[playerIndex].playerTarget].name + ", but he's not here.";
}

void PickUpItemAction(int playerIndex, Player player[], World &world)
{
    if (player[playerIndex].itemPtr != nullptr)
    {
        player[playerIndex].narrative = "ERROR: tried to pick up an item, but was already carrying something.";
        return;
    }
    
    if (player[playerIndex].itemFocusPtr != nullptr)
    {
        if (player[playerIndex].locationClass.location == (player[playerIndex].itemFocusPtr)->m_locationClass.location)
        {
            if (player[playerIndex].itemFocusPtr->m_carryingPlayer == nullptr)
            {
                player[playerIndex].itemPtr = player[playerIndex].itemFocusPtr;
                player[playerIndex].itemPtr->m_carryingPlayer = &(player[playerIndex]);
                player[playerIndex].narrative = "picked up a " + player[playerIndex].itemPtr->ToString() + " in the " + player[playerIndex].itemPtr->m_locationClass.ToString() + ".";
                player[playerIndex].aiController.lastActionSucceeded = true;
            } else {
                player[playerIndex].narrative = "ERROR: tried to pick up a " + player[playerIndex].itemFocusPtr->ToString() + " but " + (player[playerIndex].itemFocusPtr->m_carryingPlayer)->name + " was already carrying it.";
            }
        } else {
            player[playerIndex].narrative = "ERROR: tried to pick up a " + player[playerIndex].itemFocusPtr->ToString() + " but it was in the " + (player[playerIndex].itemFocusPtr)->m_locationClass.ToString() + " while he was in the " + player[playerIndex].locationClass.ToString() + ".";
        }
    } else {
        player[playerIndex].narrative = "ERROR: tried to pick up an item, but didn't specify which.";
    }
}

void DropItemAction(int playerIndex, Player player[], World &world)
{
    if (player[playerIndex].itemPtr != nullptr)
    {
        player[playerIndex].itemPtr->m_locationClass.location = player[playerIndex].locationClass.location;
        player[playerIndex].narrative = "Dropped a " + player[playerIndex].itemPtr->ToString() + " in the " + player[playerIndex].itemPtr->m_locationClass.ToString() + ".";
        player[playerIndex].itemPtr->m_carryingPlayer = nullptr;
        player[playerIndex].itemPtr = nullptr;
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else {
        player[playerIndex].narrative = "ERROR: tried to drop up an item, but no item is being carried.";
    }
}

void RequestItemAction(int playerIndex, Player player[], World &world)
{
    if (player[playerIndex].playerTarget == playerIndex)
    {
        player[playerIndex].narrative = "ERROR: " + player[playerIndex].name + " tried to request an item from himself.";
        return;
    }
    if (player[playerIndex].itemPtr != nullptr)
    {
        player[playerIndex].narrative = "ERROR: tried to request an item but is already carrying a " + player[playerIndex].itemPtr->ToString() + ".";
        return;
    }
    if (playerIndexOutOfBounds(player[playerIndex].playerTarget))
    {
        player[playerIndex].narrative = "ERROR: tried to request an item but didn't specify who to ask.";
        return;
    }
    if (player[player[playerIndex].playerTarget].locationClass.location != player[playerIndex].locationClass.location)
    {
        player[playerIndex].narrative = "ERROR: tried to request an item from " + player[player[playerIndex].playerTarget].name + ", but he isn't even in the same room.";
        return;
    }
    if (player[player[playerIndex].playerTarget].itemPtr == nullptr)
    {
        player[playerIndex].narrative = "ERROR: tried to request an item from " + player[player[playerIndex].playerTarget].name + ", but " + player[player[playerIndex].playerTarget].name + " is not carrying anything.";
        return;
    }
    player[playerIndex].narrative = "Says: 'Hey " + player[player[playerIndex].playerTarget].name + ", can I have that " + player[player[playerIndex].playerTarget].itemPtr->ToString() + " you're carrying?'\n";
    if (player[player[playerIndex].playerTarget].aiController.RespondToOffer(playerIndex))
    {
        player[player[playerIndex].playerTarget].itemPtr->m_carryingPlayer = &player[playerIndex];
        player[playerIndex].itemPtr = player[player[playerIndex].playerTarget].itemPtr;
        player[player[playerIndex].playerTarget].itemPtr = nullptr;
        player[playerIndex].narrative += "Request success! " + player[player[playerIndex].playerTarget].name + " has given " + player[playerIndex].name + " the " + player[playerIndex].itemPtr->ToString() + ".";
        player[playerIndex].aiController.lastActionSucceeded = true;
    } else {
        player[playerIndex].narrative += "Request was declined.";
    }
}