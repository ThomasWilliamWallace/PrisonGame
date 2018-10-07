//
//  HTN.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTN.hpp"
#include "HTNDomain.hpp"

//*******************************************************************
//HTNTask::HTNTask():m_name("TASK_NAME_NOT_SET"), m_htnPrimitive(0), m_htnCompound(0), m_isPrimitive(false) {}

//HTNTask::HTNTask(HTNPrimitivePtr htnPrimitive):m_name("TASK_NAME_NOT_SET"), m_htnPrimitive(htnPrimitive), m_htnCompound(0), m_isPrimitive(true) {}

//HTNTask::HTNTask(HTNCompoundPtr htnCompound):m_name("TASK_NAME_NOT_SET"), m_htnPrimitive(0), m_htnCompound(htnCompound), m_isPrimitive(false) {}

HTNTask::HTNTask(std::string name, bool isPrimitive) : m_name(name), m_isPrimitive(isPrimitive) {}

std::string HTNTask::ToString()
{
    return m_name;
}

//*******************************************************************
HTNPrimitive::HTNPrimitive(std::string name): HTNTask(name, true) {}

bool HTNPrimitive::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void HTNPrimitive::Effect(HTNWorldState &htnWorldState)
{
    return;
}

Actions HTNPrimitive::Operator(int playerIndex, Player player[], World &world)
{
    return Actions::noAction;
}

void HTNPrimitive::PointToRealItems(){}

//*******************************************************************
HTNCompound::HTNCompound(std::string name): HTNTask(name, false) {}

//*******************************************************************
bool HTNMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void HTNMethod::AddTask(HTNPrimitivePtr htnPrimitivePtr)
{
    m_taskList.push_back(htnPrimitivePtr);
}

void HTNMethod::AddTask(HTNCompoundPtr htnCompoundPtr)
{
    m_taskList.push_back(htnCompoundPtr);
}

//*******************************************************************
constexpr int c_MaxSearchDepth = 50;

HTNPrimitiveList HTNdfs(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth)
{    
    if (searchDepth > c_MaxSearchDepth)
    {
        HTNPrimitiveList htnPlan2;
        return htnPlan2; //return failure state of empty plan
    }
    
    for (auto &htnMethod : htnCompound.m_methods)
    {
        if (!htnMethod->Preconditions(htnWorldState))
        {
            continue;
        }
        HTNPrimitiveList htnPlan;
        HTNWorldState ws2(htnWorldState);
        bool planningFailed = false;
        //try the next htnMethod from htnCompound
        for (auto &htnTask : htnMethod->m_taskList)
        {
            if (htnTask->m_isPrimitive)
            {
                HTNPrimitivePtr pPtr( std::dynamic_pointer_cast<HTNPrimitive>(htnTask) );
                if (pPtr->Preconditions(ws2))
                {
                    pPtr->Effect(ws2);
                    htnPlan.push_back(pPtr);
                } else {
                    planningFailed = true;
                }
            } else {
                HTNCompoundPtr cPtr( std::dynamic_pointer_cast<HTNCompound>(htnTask) );
                HTNPrimitiveList subplan = HTNdfs(ws2, *cPtr, searchDepth + 1);
                if (static_cast<int>(subplan.size()) > 0)
                {
                    std::cout << "Returning plan:";
                    for (auto &subtask : subplan)
                    {
                        std::cout << subtask->ToString() << ", ";
                        htnPlan.push_back(subtask);
                    }
                    std::cout << "\n";
                } else {
                    planningFailed = true;
                }
            }
            
            if (planningFailed)  //if planning for htnTask failed, then skip to next iteration of htnMethod.
            {
                break;
            }
        }
        
        if (!planningFailed)
        {
            //an htnMethod of htnCompound has been successfully planned
            //copy the planned htnWorldState back into the parameter htnWorldState
            htnWorldState.CopyFrom(ws2);
            return htnPlan;
        }
    }
    
    HTNPrimitiveList htnPlan3;
    return htnPlan3; //return failure state of empty plan
}