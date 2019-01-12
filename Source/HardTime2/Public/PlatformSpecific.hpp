#pragma once
#include <memory>

class HTNNode;
class HTNPrimitive;
class HTNCompound;
class HTNMethod;
struct StackNode;

#ifdef TEXT_ONLY_HTN
typedef std::shared_ptr<HTNPrimitive> HTNPrimitivePtr;
typedef std::shared_ptr<HTNCompound> HTNCompoundPtr;
typedef std::shared_ptr<HTNNode> HTNNodePtr;
typedef std::shared_ptr<HTNMethod> HTNMethodPtr;

typedef std::shared_ptr<StackNode> StackNodePtr;
#else
typedef TSharedPtr<HTNPrimitive> HTNPrimitivePtr;
typedef TSharedPtr<HTNCompound> HTNCompoundPtr;
typedef TSharedPtr<HTNNode> HTNNodePtr;
typedef TSharedPtr<HTNMethod> HTNMethodPtr;

typedef TSharedPtr<StackNode> StackNodePtr;
#endif

HTNPrimitive* GetRaw(HTNPrimitivePtr ptr);
HTNCompound* GetRaw(HTNCompoundPtr ptr);
HTNNode* GetRaw(HTNNodePtr ptr);
HTNMethod* GetRaw(HTNMethodPtr ptr);

HTNPrimitivePtr CastNodeToPrimitive(HTNNodePtr htnNodePtr);
HTNCompoundPtr CastNodeToCompound(HTNNodePtr htnNodePtr);
HTNMethodPtr CastNodeToMethod(HTNNodePtr htnNodePtr);

HTNNodePtr MakeShareableCompound(HTNCompound &htnCompound);

StackNodePtr MakeSharedStackNodePtr(HTNNodePtr htnNodePtr, bool isOr);
