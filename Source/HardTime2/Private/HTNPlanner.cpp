#include "HTNPlanner.hpp"
#include "HTNDomain.hpp"
#include "pLog.hpp"
#include <sstream>

//*******************************************************************
HTNTask::HTNTask(std::string name, bool isPrimitive) : m_name(name), m_isPrimitive(isPrimitive) {}

std::string HTNTask::ToString()
{
	return m_name;
}

//*******************************************************************
HTNPrimitive::HTNPrimitive(std::string name) : HTNTask(name, true) {}

bool HTNPrimitive::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void HTNPrimitive::Effect(HTNWorldState &htnWorldState)
{
	return;
}

Actions HTNPrimitive::Operate(UPlayerData* playerData, USimWorld &world)
{
	return Actions::noAction;
}

bool HTNPrimitive::LastActionSucceeded(HTNWorldState &htnWorldState)
{
	return true;
}

//*******************************************************************
HTNCompound::HTNCompound(std::string name) : HTNTask(name, false) {}

void HTNCompound::AddMethod(HTNMethod* htnMethod)
{
    m_methods.push_back(HTNMethodPtr(htnMethod));
}

//*******************************************************************
bool HTNMethod::Preconditions(HTNWorldState &htnWorldState)
{
	return true;
}

void HTNMethod::AddTask(HTNPrimitive* htnPrimitive)
{
	m_taskList.push_back(HTNPrimitivePtr(htnPrimitive));
}

void HTNMethod::AddTask(HTNCompound* htnCompound)
{
	m_taskList.push_back(HTNCompoundPtr(htnCompound));
}

//*******************************************************************
constexpr int c_MaxSearchDepth = 50;

HTNPrimitiveList HTNdfs(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth)
{
    std::stringstream ss;
    ss << "Try to plan " + htnCompound.ToString() + ", containing methods:\n";
    for (auto &htnMethod : htnCompound.m_methods)
    {
        ss << "Method: ";
        for (auto &task : htnMethod->m_taskList)
        {
            ss << task->ToString() << ",";
        }
    }
    pLog(ss);

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
				HTNPrimitivePtr pPtr = StaticCastSharedPtr<HTNPrimitive>(htnTask);
				if (pPtr->Preconditions(ws2))
				{
					pPtr->Effect(ws2);
					htnPlan.push_back(pPtr);
                		} else {
					planningFailed = true;
				}
			} else {
				HTNCompoundPtr cPtr = StaticCastSharedPtr<HTNCompound>(htnTask);
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
            std::stringstream ss2;
            ss2 << "Successfully planned an htnMethod for compound " + htnCompound.ToString() + ":";
            for (auto &htn : htnPlan)
            {
            	ss2 << htn->ToString() << ", ";
            }
            pLog(ss2);
			return htnPlan;
		}
	}

	HTNPrimitiveList htnPlan3;
	return htnPlan3; //return failure state of empty plan
}
