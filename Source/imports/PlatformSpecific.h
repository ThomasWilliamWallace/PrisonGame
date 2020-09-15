#pragma once
#include <memory>

class HTNNode;
class HTNPrimitive;
class HTNCompound;
class HTNMethod;
struct StackNode;
class AbstractItem;
class SimItem;
class AbstractPlayerData;

typedef std::shared_ptr<HTNPrimitive> HTNPrimitivePtr;
typedef std::shared_ptr<HTNCompound> HTNCompoundPtr;
typedef std::shared_ptr<HTNNode> HTNNodePtr;
typedef std::shared_ptr<HTNMethod> HTNMethodPtr;
typedef std::shared_ptr<StackNode> StackNodePtr;

typedef std::shared_ptr<AbstractItem> AbstractItemPtr;
typedef std::shared_ptr<SimItem> SimItemPtr;

#ifdef TEXT_ONLY_HTN
typedef uint8_t uint8;
#endif

enum class EItemType : uint8;
enum class ELocations : uint8;

#ifdef TEXT_ONLY_HTN

// Allow Unreal-specific macros to evaluate to nothing
#define UENUM(...)
#define UMETA(DisplayName, ...)

#include <map>

class Relationship;

typedef std::map<int, AbstractPlayerData*> PlayerMap;
typedef std::pair<int, AbstractPlayerData*> IntPlayerPair;
typedef std::map<int, Relationship*> RelMap;
typedef std::pair<int, Relationship*> IntRelPair;

template <typename Iterator>
int GetKey(Iterator &iterator)
{
	return iterator.first;
};

template <typename Iterator>
AbstractPlayerData* GetPlayer(Iterator &iterator)
{
	return iterator.second;
};

template <typename Iterator>
Relationship* GetRel(Iterator &iterator)
{
	return iterator.second;
};

template <typename Container>
bool Contains(Container &container, int key)
{
	return container.find(key) != container.end();
};

template <typename Container, typename Element>
void Add(Container &container, int addKey, Element addElem)
{
	container.insert(typename Container::value_type(addKey, addElem));
};

template <typename Container>
void Remove(Container &container, int removeKey)
{
	container.erase(removeKey);
};

template <typename Container, typename Iterator>
void RemoveCurrent(Container &container, Iterator iter)
{
	iter = container.erase(iter);
};

typedef AbstractItem RealItemType;

#else

#include "Runtime/Core/Public/Containers/Map.h"

class UPlayerData;
class URelationship;

typedef TMap<int, UPlayerData*> PlayerMap;
typedef TPair<int, UPlayerData*> IntPlayerPair;
typedef TMap<int, URelationship*> RelMap;
typedef TPair<int, URelationship*> IntRelPair;

template <typename Iterator>
int GetKey(Iterator &iterator)
{
	return iterator.Key;
};

template <typename Iterator>
UPlayerData* GetPlayer(Iterator &iterator)
{
	return iterator.Value;
};

template <typename Iterator>
URelationship* GetRel(Iterator &iterator)
{
	return iterator.second;
};

template <typename Container>
bool Contains(Container &container, int key)
{
	return container.Contains(key);
};

template <typename Container, typename Element>
void Add(Container &container, int addKey, Element addElem)
{
	container.Add(addKey, addElem);
};

template <typename Container>
void Remove(Container &container, int removeKey)
{
	container.Remove(removeKey);
};

template <typename Container, typename Iterator>
void RemoveCurrent(Container &container, Iterator iter)
{
	iter.RemoveCurrent();
};

class AActorItem;

typedef AActorItem RealItemType;

#endif

HTNPrimitive* GetRaw(HTNPrimitivePtr ptr);
HTNCompound* GetRaw(HTNCompoundPtr ptr);
HTNNode* GetRaw(HTNNodePtr ptr);
HTNMethod* GetRaw(HTNMethodPtr ptr);
AbstractItem* GetRaw(AbstractItemPtr ptr);
SimItem* GetRaw(SimItemPtr ptr);

HTNPrimitivePtr CastNodeToPrimitive(HTNNodePtr htnNodePtr);
HTNCompoundPtr CastNodeToCompound(HTNNodePtr htnNodePtr);
HTNMethodPtr CastNodeToMethod(HTNNodePtr htnNodePtr);

StackNodePtr MakeSharedStackNodePtr(HTNNodePtr htnNodePtr, bool isOr);
HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound);

AbstractItemPtr MakeSharedAbstractItemPtr(EItemType itemType, ELocations location, AbstractPlayerData* carryingPlayer);
SimItemPtr MakeSharedSimItemPtr(RealItemType* realItem, EItemType itemType, ELocations location, AbstractPlayerData* carryingPlayer);

// Encapsulated because Unreal Engine uses a different exception system
[[noreturn]] void ThrowException(const std::string& errorMessage);
