#include "HTNPlanner.hpp"
#include "HTNDomain.hpp"
#include "AICharacterC.h"
#include "Engine/GameEngine.h"

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

Actions HTNPrimitive::Operate(AAICharacterC* aiCharacterC)
{
	return Actions::noAction;
}

bool HTNPrimitive::LastActionSucceeded(HTNWorldState &htnWorldState, AAICharacterC* aiCharacterC)
{
	return true;
}

//*******************************************************************
HTNCompound::HTNCompound(std::string name) : HTNTask(name, false) {}

void HTNCompound::AddMethod(HTNMethodPtr htnMethod)
{
    m_methods.push_back(HTNMethodPtr(htnMethod));
}

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
				HTNPrimitivePtr pPtr = static_cast<HTNPrimitive*>(htnTask);
				if (pPtr->Preconditions(ws2))
				{
					pPtr->Effect(ws2);
					htnPlan.push_back(pPtr);
				}
				else {
					planningFailed = true;
				}
			}
			else {
				HTNCompoundPtr cPtr = static_cast<HTNCompound*>(htnTask);
				HTNPrimitiveList subplan = HTNdfs(ws2, *cPtr, searchDepth + 1);
				if (static_cast<int>(subplan.size()) > 0)
				{
					for (auto &subtask : subplan)
					{
						htnPlan.push_back(subtask);
					}
				}
				else {
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

Actions htnAIChooseAction(AAICharacterC* aiCharacterC) //TODO capitalise
{
	UE_LOG(LogTemp, Warning, TEXT("Entering htnAIChooseAction"));
	//update worldstate from real world
	HTNWorldState htnWorldState(aiCharacterC);

	bool hasValidPlan = false;
	// check if next step of the plan is valid.

	if ((aiCharacterC->lastPrimitiveAction != nullptr) && !(aiCharacterC->lastPrimitiveAction->LastActionSucceeded(htnWorldState, aiCharacterC)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Last Action did not succeed"));
		hasValidPlan = false;
	}
	else if (aiCharacterC->htnPlan.size() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Check Precondition of plan primitive step"));
		hasValidPlan = (aiCharacterC->htnPlan).at(0)->Preconditions(htnWorldState);
	}
	
	//If plan is not valid, abandon it and try to make a new plan
	if (!hasValidPlan)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid plan exists! Try to replan."));
		//make new plan
		HTNWorldState htnWorldStateDFSCopy(htnWorldState);
		HTNCompound* missionPtr = new PrisonerBehaviourCompound(htnWorldStateDFSCopy);
		aiCharacterC->htnPlan = HTNdfs(htnWorldStateDFSCopy, *missionPtr, 0);

		//once again, check if next step of the plan is valid.
		if ((aiCharacterC->htnPlan).size() > 0)
		{
			hasValidPlan = (aiCharacterC->htnPlan).at(0)->Preconditions(htnWorldState);
		}
	}

	if (!hasValidPlan)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid plan exists! Leaving htnAIChooseAction #1"));
		return Actions::noAction; //If next step of the plan is still not valid, then return failure state
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Valid plan found!"));
		//continue with current plan
		for (auto &prim : aiCharacterC->htnPlan)
		{
			FString b = (prim->ToString().c_str());
			UE_LOG(LogTemp, Warning, TEXT("Plan step: %s"), *b);
			//if (GEngine)
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, b);
		}
		HTNPrimitivePtr currentPlanStep = (aiCharacterC->htnPlan).front();
		aiCharacterC->lastPrimitiveAction = currentPlanStep;
		(aiCharacterC->htnPlan).pop_front();
		UE_LOG(LogTemp, Warning, TEXT("Leaving htnAIChooseAction #2"));
		return currentPlanStep->Operate(aiCharacterC);
	}
	UE_LOG(LogTemp, Warning, TEXT("Leaving htnAIChooseAction #3"));
	return Actions::noAction;
}
