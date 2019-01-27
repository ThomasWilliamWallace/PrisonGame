#include "PlatformSpecific.hpp"
#include "HTNPlanner.hpp"
#include "ActorItem.h"
#include "Locations.h"
#include "PlayerData.h"

#ifdef TEXT_ONLY_HTN

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

SimActorItem* GetRaw(SimActorItemPtr ptr)
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

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
    return std::make_shared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound)
{
    return HTNNodePtr(&htnCompound);
}

#else

#include "ActorItem.h"

HTNPrimitive* GetRaw(HTNPrimitivePtr ptr)
{
    return ptr.Get();
}

HTNCompound* GetRaw(HTNCompoundPtr ptr)
{
    return ptr.Get();
}

HTNNode* GetRaw(HTNNodePtr ptr)
{
    return ptr.Get();
}

HTNMethod* GetRaw(HTNMethodPtr ptr)
{
    return ptr.Get();
}

SimActorItem* GetRaw(SimActorItemPtr ptr)
{
    return ptr.Get();
}

HTNPrimitivePtr CastNodeToPrimitive(HTNNodePtr htnNodePtr)
{
    return StaticCastSharedPtr<HTNPrimitive>(htnNodePtr);
}

HTNCompoundPtr CastNodeToCompound(HTNNodePtr htnNodePtr)
{
    return StaticCastSharedPtr<HTNCompound>(htnNodePtr);
}

HTNMethodPtr CastNodeToMethod(HTNNodePtr htnNodePtr)
{
    return StaticCastSharedPtr<HTNMethod>(htnNodePtr);
}

StackNodePtr MakeSharedStackNodePtr(HTNNodePtr htnNodePtr, bool isOr)
{
    return MakeShared<StackNode>(htnNodePtr, isOr);
}

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
	return MakeShared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound)
{
    return MakeShareable(&htnCompound);
}

#endif
