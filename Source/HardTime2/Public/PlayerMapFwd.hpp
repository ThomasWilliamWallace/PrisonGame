#pragma once

#include <map>
#include "Runtime/Core/Public/Containers/Map.h"

class UPlayerData;

typedef std::map<int, UPlayerData*> PlayerMap;
typedef TMap<int, UPlayerData*> PlayerMap2;
typedef std::pair<int, UPlayerData*> IntPlayerPair;