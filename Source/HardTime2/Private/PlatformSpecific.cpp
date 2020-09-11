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
// Default case

[[noreturn]] void ThrowException(const std::string& errorMessage)
{    
    throw errorMessage;
}

SimActorItem* GetRaw(SimActorItemPtr ptr)
{
    return ptr.get();
}

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
    return std::make_shared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

#else
// Unreal engine case

#include "ActorItem.h"
#include "Engine/GameEngine.h"

SimActorItem* GetRaw(SimActorItemPtr ptr)
{
    return ptr.Get();
}

SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer)
{
	return MakeShared<SimActorItem>(realItem, itemType, location, carryingPlayer);
}

    // TODO split the platform specific code into separate cpp files. The PlatformSpecific.cpp file can then be included from the appropriate location for different builds.
    // The TEXT_ONLY_HTN flag can then be done away with.

[[noreturn]] void ThrowException(const std::string& errorMessage)
{
    FString fStringErrorMessage = FString(errorMessage.c_str());
    UE_LOG(LogTemp, Fatal, TEXT("%s"), *fStringErrorMessage);
}

#endif
