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
class Relationship;

#ifdef TEXT_ONLY_HTN

#include <map>
typedef std::shared_ptr<HTNPrimitive> HTNPrimitivePtr;
typedef std::shared_ptr<HTNCompound> HTNCompoundPtr;
typedef std::shared_ptr<HTNNode> HTNNodePtr;
typedef std::shared_ptr<HTNMethod> HTNMethodPtr;

typedef std::shared_ptr<StackNode> StackNodePtr;

typedef std::shared_ptr<SimActorItem> SimActorItemPtr;

typedef uint8_t uint8;

typedef std::map<int, UPlayerData*> PlayerMap;
typedef std::pair<int, UPlayerData*> IntPlayerPair;
typedef std::map<int, Relationship*> RelMap;
typedef std::pair<int, Relationship*> IntRelPair;
#else

#include "Runtime/Core/Public/Containers/Map.h"
typedef TSharedPtr<HTNPrimitive> HTNPrimitivePtr;
typedef TSharedPtr<HTNCompound> HTNCompoundPtr;
typedef TSharedPtr<HTNNode> HTNNodePtr;
typedef TSharedPtr<HTNMethod> HTNMethodPtr;

typedef TSharedPtr<StackNode> StackNodePtr;

typedef TSharedPtr<SimActorItem> SimActorItemPtr;

typedef TMap<int, UPlayerData*> PlayerMap;
typedef TPair<int, UPlayerData*> IntPlayerPair;
typedef TMap<int, Relationship*> RelMap;
typedef TPair<int, Relationship*> IntRelPair;
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

//TODO make PlayerMap and RelMap into classes?
bool Contains(PlayerMap &playerMap, int key);
bool Contains(RelMap &relMap, int key);
void Add(PlayerMap &playerMap, int addKey, UPlayerData* addPlayerData);
void Add(RelMap &relMap, int addKey, Relationship* relationship);
void Remove(PlayerMap &playerMap, int removeKey);
void Remove(RelMap &relMap, int removeKey);
