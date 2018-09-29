//
//  HTN.hpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#ifndef HTN_hpp
#define HTN_hpp
#include <vector>
#include <iostream>
#include "HTNWorldState.hpp"

class HTNPrimitive;
class HTNCompound;
class HTNWorldState;

class HTNTask
{
public:
    HTNPrimitive* m_htnPrimitive;
    HTNCompound* m_htnCompound;
    bool m_isPrimitive;
    HTNTask();
    HTNTask(HTNPrimitive* htnPrimitive);
    HTNTask(HTNCompound* htnCompound);
};

typedef std::vector< HTNTask* > HTNTaskList;

class HTNPrimitive
{
public:
    virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
    virtual void Effect(HTNWorldState &htnWorldState); //simplified, predicted effect of taking this action. Will be applied to the simulated world during planning.
    void Operator();  //actual code that will be run to control the player when taking this action
    virtual std::string ToString();
};

typedef std::vector< HTNPrimitive* > HTNPrimitiveList;

class HTNMethod
{
public:
    virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
    HTNTaskList m_taskList; //To complete this HTNCompound task, all the tasks in a method must be completed.
    void AddTask(HTNPrimitive* htnPrimitive);
    void AddTask(HTNCompound* htnCompound);
};

typedef std::vector< HTNMethod* > HTNMethodList;

//subtasks //list of either primitive or compound tasks
class HTNCompound
{
public:
    HTNMethodList m_methods;  //Vector of methods. Each method is a vector of tasks.  //TODO instantiate separate HTNMethods, each with their own preconditions. Remove preconditions from the HTNCompound
};

typedef std::vector< HTNCompound* > HTNCompoundList;

class HTNPlan
{
public:
    HTNPrimitiveList m_list;
    //list of primitive tasks, with variables filled in? //TODO store variables
};

HTNPrimitiveList HTNdfs(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth);

void ComposeHTNPlan();

#endif /* HTN_hpp */