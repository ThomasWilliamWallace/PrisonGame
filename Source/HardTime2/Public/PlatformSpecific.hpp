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

template <typename Iterator>
int GetKey(Iterator &iterator)
{
	return iterator.first;
};

template <typename Iterator>
UPlayerData* GetPlayer(Iterator &iterator)
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
Relationship* GetRel(Iterator &iterator)
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
