#pragma once
#include <memory>

class HTNNode;
class HTNPrimitive;
class HTNCompound;
class HTNMethod;
struct StackNode;
class SimActorItem;
class AActorItem;
class UPlayerData;

#ifdef TEXT_ONLY_HTN
typedef std::shared_ptr<HTNPrimitive> HTNPrimitivePtr;
typedef std::shared_ptr<HTNCompound> HTNCompoundPtr;
typedef std::shared_ptr<HTNNode> HTNNodePtr;
typedef std::shared_ptr<HTNMethod> HTNMethodPtr;

typedef std::shared_ptr<StackNode> StackNodePtr;

typedef std::shared_ptr<SimActorItem> SimActorItemPtr;

typedef uint8_t uint8;
#else
typedef TSharedPtr<HTNPrimitive> HTNPrimitivePtr;
typedef TSharedPtr<HTNCompound> HTNCompoundPtr;
typedef TSharedPtr<HTNNode> HTNNodePtr;
typedef TSharedPtr<HTNMethod> HTNMethodPtr;

typedef TSharedPtr<StackNode> StackNodePtr;

typedef TSharedPtr<SimActorItem> SimActorItemPtr;
#endif

enum class EItemType : uint8;
enum class ELocations : uint8;

HTNPrimitive* GetRaw(HTNPrimitivePtr ptr);
HTNCompound* GetRaw(HTNCompoundPtr ptr);
HTNNode* GetRaw(HTNNodePtr ptr);
HTNMethod* GetRaw(HTNMethodPtr ptr);
SimActorItem* GetRaw(SimActorItemPtr ptr);

HTNPrimitivePtr CastNodeToPrimitive(HTNNodePtr htnNodePtr);
HTNCompoundPtr CastNodeToCompound(HTNNodePtr htnNodePtr);
HTNMethodPtr CastNodeToMethod(HTNNodePtr htnNodePtr);

StackNodePtr MakeSharedStackNodePtr(HTNNodePtr htnNodePtr, bool isOr);
SimActorItemPtr MakeSharedSimActorItemPtr(AActorItem& realItem, EItemType itemType, ELocations location, UPlayerData* carryingPlayer);

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound);
