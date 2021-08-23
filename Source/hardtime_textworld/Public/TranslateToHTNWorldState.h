#pragma once

#include "HTNWorldState.h"

class UPlayerData;
class USimWorld;
class PlayerRegistry;

HTNWorldState TranslateToHTNWorldState(UPlayerData* playerPtr, USimWorld& simworld, PlayerMap& playerMap, UPlayerData* requester);
