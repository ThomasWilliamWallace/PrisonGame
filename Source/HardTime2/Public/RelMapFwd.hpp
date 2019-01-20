#pragma once

#include <map>
#include "Runtime/Core/Public/Containers/Map.h"

class Relationship;

typedef std::map<int, Relationship*> RelMap;
typedef TMap<int, Relationship*> RelMap2;
typedef std::pair<int, Relationship*> IntRelPair;