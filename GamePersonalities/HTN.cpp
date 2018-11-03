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

void HTNPrimitive::PointToRealItems(HTNWorldState &htnWorldState){}

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
    if (c_debug)
    {
        std::cout << "Try to plan " + htnCompound.ToString() + ", containing methods:\n";
        for (auto &htnMethod : htnCompound.m_methods)
        {
            std::cout << "Method: ";
            for (auto &task : htnMethod->m_taskList)
            {
                std::cout << task->ToString() << ",";
            }
            std::cout << "\n";
        }
    }

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
                    for (auto &subtask : subplan)
                    {
                        htnPlan.push_back(subtask);
                    }
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
            if (c_debug)
            {
                std::cout << "Successfully planned an htnMethod for compound " + htnCompound.ToString() + ":";
                for (auto &htn : htnPlan)
                {
                    std::cout << htn->ToString() << ", ";
                }
                std::cout << "\n";
            }
            return htnPlan;
        }
    }
    
    HTNPrimitiveList htnPlan3;
    return htnPlan3; //return failure state of empty plan
}