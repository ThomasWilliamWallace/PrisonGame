#include "PlatformSpecific.h"
#include "HTNPlanner.h"
#include "ActorItem.h"
#include "Locations.h"
#include "PlayerData.h"

HTNPrimitive* GetRaw(HTNPrimitivePtr ptr)
{
    return ptr.get();
}

HTNCompound* GetRaw(HTNCompoundPtr ptr)
{
    return ptr.get();
}

HTNNode* GetRaw(HTNNodePtr ptr)
{
    return ptr.get();
}

HTNMethod* GetRaw(HTNMethodPtr ptr)
{
    return ptr.get();
}

HTNPrimitivePtr CastNodeToPrimitive(HTNNodePtr htnNodePtr)
{
    return std::static_pointer_cast<HTNPrimitive>(htnNodePtr);
}

HTNCompoundPtr CastNodeToCompound(HTNNodePtr htnNodePtr)
{
    return std::static_pointer_cast<HTNCompound>(htnNodePtr);
}

HTNMethodPtr CastNodeToMethod(HTNNodePtr htnNodePtr)
{
    return std::static_pointer_cast<HTNMethod>(htnNodePtr);
}

StackNodePtr MakeSharedStackNodePtr(HTNNodePtr htnNodePtr, bool isOr)
{
    return std::make_shared<StackNode>(htnNodePtr, isOr);
}

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound)
{
    return HTNNodePtr(&htnCompound);
}

#ifdef TEXT_ONLY_HTN

SimActorItem* GetRaw(SimActorItemPtr ptr)
{
    return ptr.get();
}

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
    return std::make_shared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

#else

#include "ActorItem.h"

SimActorItem* GetRaw(SimActorItemPtr ptr)
{
    return ptr.Get();
}

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
	return MakeShared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

#endif
