#include "PlatformSpecific.h"
#include "HTNPlanner.h"
#include "Locations.h"

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

AbstractItem* GetRaw(AbstractItemPtr ptr)
{
    return ptr.get();
}

SimItem* GetRaw(SimItemPtr ptr)
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

AbstractItemPtr MakeSharedAbstractItemPtr(EItemType itemType, ELocations location, AbstractPlayerData* carryingPlayer)
{
    return std::make_shared<AbstractItem>(itemType, location, carryingPlayer);
}

SimItemPtr MakeSharedSimItemPtr(AbstractItem* realItem, EItemType itemType, ELocations location, AbstractPlayerData* carryingPlayer)
{
    return std::make_shared<SimItem>(realItem, itemType, location, carryingPlayer);
}

#ifdef TEXT_ONLY_HTN
// Default case

[[noreturn]] void ThrowException(const std::string& errorMessage)
{    
    throw errorMessage;
}

#else
// Unreal engine case

#include "Engine/GameEngine.h"

    // TODO split the platform specific code into separate cpp files. The PlatformSpecific.cpp file can then be included from the appropriate location for different builds.
    // The TEXT_ONLY_HTN flag can then be done away with.

[[noreturn]] void ThrowException(const std::string& errorMessage)
{
    FString fStringErrorMessage = FString(errorMessage.c_str());
    UE_LOG(LogTemp, Fatal, TEXT("%s"), *fStringErrorMessage);
}

#endif
