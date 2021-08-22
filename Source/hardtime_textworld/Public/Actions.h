#pragma once

#include <algorithm>
#include "PlatformSpecific.h"
#include "AbstractAction.h"

class USimWorld;
class UPlayerData;

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap);

void DoAttackAction(UPlayerData* attackingPlayerPtr, PlayerMap &playerMap, USimWorld &world);
void DoWeightliftAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoCircuitsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoStudyAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoSleepAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoUseRoomAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoOfferMissionAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoMakeFriendsAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoPickUpItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoDropItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
void DoRequestItemAction(UPlayerData* playerPtr, PlayerMap &playerMap, USimWorld &world);
