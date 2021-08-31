#include "PlatformSpecific.h"
#include "Locations.h"

AbstractItemPtr MakeSharedAbstractItemPtr(EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
    return std::make_shared<AbstractItem>(itemType, location, carryingPlayer);
}

SimItemPtr MakeSharedSimItemPtr(RealItemType* realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
    return std::make_shared<SimItem>(realItem, itemType, location, carryingPlayer);
}

#ifdef TEXT_ONLY_HTN
// Default case

#else
// Unreal engine case

#include "ActorItem.h"

#endif
