#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <memory>
#include "HTNWorldState.hpp"
#include "Actions.hpp"

class HTNTask;
class HTNPrimitive;
class HTNCompound;
class HTNMethod;

class AAICharacterC;

typedef HTNPrimitive* HTNPrimitivePtr;
typedef HTNCompound* HTNCompoundPtr;
typedef HTNTask* HTNTaskPtr;
typedef HTNMethod* HTNMethodPtr;

typedef std::deque< HTNPrimitivePtr > HTNPrimitiveList;
typedef std::vector< HTNCompoundPtr > HTNCompoundList;
typedef std::vector< HTNTaskPtr > HTNTaskList;
typedef std::vector< HTNMethodPtr > HTNMethodList;

class HTNTask
{
public:
	std::string m_name;
	bool m_isPrimitive;
	HTNTask(std::string name, bool isPrimitive);
	virtual ~HTNTask() = default; //TODO write proper destructors
	std::string ToString();
};

class HTNPrimitive : public HTNTask
{
public:
	HTNPrimitive(std::string name);
	virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
	virtual void Effect(HTNWorldState &htnWorldState); //simplified, predicted effect of taking this action. Will be applied to the simulated world during planning.
	virtual Actions Operate(AAICharacterC* aiCharacterC); //actual code that will be run to control the player when taking this action. Sets the player registers, and returns an action.
	virtual bool LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC); //returns true if this operator appears to have succeeded. Is called after calling the 'Operate' function.
	virtual ~HTNPrimitive() = default;
};

class HTNCompound : public HTNTask
{
public:
	HTNCompound(std::string name);
	HTNMethodList m_methods;  //Vector of methods. Each method is a vector of tasks.
	virtual ~HTNCompound() = default;
};

//list of either primitive or compound tasks
class HTNMethod
{
public:
	virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
	HTNTaskList m_taskList; //To complete this HTNCompound task, all the tasks in a method must be completed.
	void AddTask(HTNPrimitivePtr htnPrimitivePtr);
	void AddTask(HTNCompoundPtr htnCompoundPtr);
	virtual ~HTNMethod() = default;
};

class HTNPlan
{
public:
	//list of primitive tasks
	HTNPrimitiveList m_list;
};

HTNPrimitiveList HTNdfs(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth);

Actions htnAIChooseAction(AAICharacterC* aiCharacterC);