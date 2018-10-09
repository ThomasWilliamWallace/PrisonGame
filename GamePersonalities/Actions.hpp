//
//  Actions.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef Actions_hpp
#define Actions_hpp

#include <iostream>
#include "Stats.hpp"
#include "Constants.hpp"

class World;
class Player;

bool OtherInReach(int playerIndex, int otherPlayer, Player player[]);
std::string ActionToString(Actions action);

void AttackAction(int attackerIndex, Player player[], World &world);
void WeightliftAction(int playerIndex, Player player[], World &world);
void CircuitsAction(int playerIndex, Player player[], World &world);
void StudyAction(int playerIndex, Player player[], World &world);
void SleepAction(int playerIndex, Player player[], World &world);
void UseRoomAction(int playerIndex, Player player[], World &world);
void OfferMissionAction(int playerIndex, Player player[], World &world);
void MakeFriendsAction(int playerIndex, Player player[], World &world);
void PickUpItemAction(int playerIndex, Player player[], World &world);
void DropItemAction(int playerIndex, Player player[], World &world);

#endif /* Actions_hpp */
