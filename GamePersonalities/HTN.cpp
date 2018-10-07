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
HTNTask::HTNTask():m_htnPrimitive(0), m_htnCompound(0), m_isPrimitive(false){}

HTNTask::HTNTask(HTNPrimitivePtr htnPrimitive):m_htnPrimitive(htnPrimitive), m_htnCompound(0), m_isPrimitive(true){}

HTNTask::HTNTask(HTNCompoundPtr htnCompound):m_htnPrimitive(0), m_htnCompound(htnCompound), m_isPrimitive(false){}

//*******************************************************************
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

std::string HTNPrimitive::ToString()
{
    std::string name = "NAME_NOT_SET";
    return name;
}

void HTNPrimitive::PointToRealItems(){}

//*******************************************************************
bool HTNMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

void HTNMethod::AddTask(HTNPrimitivePtr htnPrimitive)
{
    m_taskList.push_back(HTNTaskPtr(new HTNTask(htnPrimitive)));
}

void HTNMethod::AddTask(HTNCompoundPtr htnCompound)
{
    m_taskList.push_back(HTNTaskPtr(new HTNTask(htnCompound)));
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
                if (htnTask->m_htnPrimitive->Preconditions(ws2))
                {
                    htnTask->m_htnPrimitive->Effect(ws2);
                    htnPlan.push_back(htnTask->m_htnPrimitive);
                } else {
                    planningFailed = true;
                }
            } else {
                HTNPrimitiveList subplan = HTNdfs(ws2, *(htnTask->m_htnCompound), searchDepth + 1);
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