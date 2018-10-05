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
#include <deque>
#include <iostream>
#include "HTNWorldState.hpp"
#include "Actions.hpp"

class HTNPrimitive;
class HTNCompound;

class World;

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
    virtual Actions Operator(int playerIndex, Player player[], World &world);  //actual code that will be run to control the player when taking this action. Sets the player registers, and returns an action.
    virtual std::string ToString();
    virtual void PointToRealItems();  //updates pointers and references to point to items existing in the players perceived HTNWorldState, rather than the simulated, predicted HTNWorldState.
};

typedef std::deque< HTNPrimitive* > HTNPrimitiveList;

class HTNMethod
{
public:
    virtual bool Preconditions(HTNWorldState &htnWorldState); //must be true before this task can occur in the plan.
    HTNTaskList m_taskList; //To complete this HTNCompound task, all the tasks in a method must be completed.
    void AddTask(HTNPrimitive* htnPrimitive);
    void AddTask(HTNCompound* htnCompound);
};

typedef std::vector< HTNMethod* > HTNMethodList;

//list of either primitive or compound tasks
class HTNCompound
{
public:
    HTNMethodList m_methods;  //Vector of methods. Each method is a vector of tasks.
};

typedef std::vector< HTNCompound* > HTNCompoundList;

class HTNPlan
{
public:
    HTNPrimitiveList m_list;
    //list of primitive tasks
};

HTNPrimitiveList HTNdfs(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth);

HTNPrimitiveList ComposeHTNPlan();

#endif /* HTN_hpp */