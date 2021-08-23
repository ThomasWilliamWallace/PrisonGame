#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include "HTNWorldState.h"
#include "PlatformSpecific.h"
#include "AbstractAction.h"

typedef std::deque< HTNPrimitivePtr > HTNPrimitiveList;
typedef std::vector< HTNCompoundPtr > HTNCompoundList;
typedef std::vector< HTNNodePtr > HTNNodeList;
typedef std::vector< HTNMethodPtr > HTNMethodList;

class HTNWorldState;

enum class HTNType
{
    Primitive,
    Compound,
    Method
};

class HTNNode
{
public:
    std::string m_name;
    HTNType m_HTNType;
    HTNNode(std::string name, HTNType htnType);
    virtual ~HTNNode() = default;
    std::string ToString();
};

class HTNPrimitive : public HTNNode
{
public:
    HTNPrimitive(std::string name);
    virtual bool Preconditions(HTNWorldState const& htnWorldState); //must be true before this task can occur in the plan.
    virtual void Effect(HTNWorldState &htnWorldState); //simplified, predicted effect of taking this action. Will be applied to the simulated world during planning.
    virtual std::shared_ptr<BaseAction> Operate(UPlayerData* playerData);  //actual code that will be run to control the player when taking this action. Sets the player registers, and returns an action.
    virtual ~HTNPrimitive() override = default;
};

class HTNCompound : public HTNNode
{
private:
    bool m_alreadyCreatedMethods;
protected:
    virtual void CreateMethods(HTNWorldState const& htnWorldState) = 0;
public:
    HTNMethodList m_methods;  //Vector of methods. Each method is a vector of tasks.
    HTNCompound(std::string name);
    void AddMethod(HTNMethod* htnMethod);
    HTNMethodList& GetMethods(HTNWorldState const& htnWorldState);
    virtual ~HTNCompound() override = default;
};

//list of either primitive or compound tasks
class HTNMethod : public HTNNode
{
private:
    bool m_alreadyCreatedTasks;
protected:
    virtual void CreateTasks(HTNWorldState const& htnWorldState) = 0; //constructs tasks
public:
    HTNNodeList m_nodeList; //To complete this HTNCompound task, all the tasks in a method must be completed. All in this list are Primitive Tasks or Compound Tasks.
    HTNMethod(std::string name);
    virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
    HTNNodeList& GetTasks(HTNWorldState const& htnWorldState); //returns tasks
    void AddTask(HTNPrimitive* htnPrimitive);
    void AddTask(HTNCompound* htnCompound);
    virtual ~HTNMethod() override = default;
};

struct StackNode //represents 'm_htnNode &&' or 'm_htnNode ||'
{
    HTNNodePtr m_htnNode;
    bool m_isOr;
    StackNode(HTNNodePtr htnNode, bool isOr): m_htnNode(htnNode), m_isOr(isOr) {};
};

HTNPrimitiveList HTNIterative(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth);
