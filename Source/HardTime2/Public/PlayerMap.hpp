#pragma once

#include "Runtime/Core/Public/Containers/Map.h"

class UPlayerData;

typedef TMap<int, UPlayerData*> PlayerMap;
typedef TPair<int, UPlayerData*> IntPlayerPair;