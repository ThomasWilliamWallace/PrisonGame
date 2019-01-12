#include "PlatformSpecific.hpp"
#include "HTNPlanner.hpp"

#ifdef TEXT_ONLY_HTN

HTNPrimitivePtr GetRaw(HTNPrimitivePtr ptr)
{
    return ptr;
}

HTNCompoundPtr GetRaw(HTNCompoundPtr ptr)
{
    return ptr;
}

HTNNodePtr GetRaw(HTNNodePtr ptr)
{
    return ptr;
}

HTNMethodPtr GetRaw(HTNMethodPtr ptr)
{
    return ptr;
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

#else
#include "ActorItem.h"
SimActorItem* GetRaw(SimActorItemPtr ptr)
{
	return ptr.Get();
}

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

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound)
{
    return MakeShareable(&htnCompound);
}

#endif
