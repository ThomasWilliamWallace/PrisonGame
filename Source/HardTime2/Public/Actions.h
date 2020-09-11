#pragma once

#include <iostream>
#include "PlatformSpecific.h"
#include "EActions.h"

bool OtherInReach(UPlayerData* playerPtr, UPlayerData* otherPlayerPtr, PlayerMap &playerMap);
std::string ActionToString(EActions action);
