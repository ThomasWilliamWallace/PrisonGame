#pragma once

#include "HTNWorldState.h"

class UPlayerData;
class USimWorld;
class PlayerRegistry;

std::unique_ptr<HTNWorldState> TranslateToHTNWorldState(UPlayerData* playerPtr, USimWorld& simworld, PlayerMap& playerMap, UPlayerData* requester);