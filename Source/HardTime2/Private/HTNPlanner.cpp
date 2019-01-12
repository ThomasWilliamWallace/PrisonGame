#include "HTNPlanner.hpp"
#include "HTNDomain.hpp"
#include "pLog.hpp"
#include <sstream>
#include <stack>

//*******************************************************************
HTNNode::HTNNode(std::string name, HTNType htnType) : m_name(name), m_HTNType(htnType) {}

std::string HTNNode::ToString()
{
	return m_name;
}

//*******************************************************************
HTNPrimitive::HTNPrimitive(std::string name): HTNNode(name, HTNType::Primitive) {}

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
HTNCompound::HTNCompound(std::string name): HTNNode(name, HTNType::Compound), m_alreadyCreatedMethods(false) {}

void HTNCompound::AddMethod(HTNMethod* htnMethod)
{
    m_methods.push_back(HTNMethodPtr(htnMethod));
}

HTNMethodList& HTNCompound::GetMethods()
{
    if (!m_alreadyCreatedMethods)
    {
        CreateMethods();
        m_alreadyCreatedMethods = true;
    }
    return m_methods;
}

//*******************************************************************
HTNMethod::HTNMethod(std::string name): HTNNode(name, HTNType::Method), m_alreadyCreatedTasks(false) {}

bool HTNMethod::Preconditions(HTNWorldState &htnWorldState)
{
    return true; //Note: Preconditions should always use the Preconditions htnWorldState parameter, rather than the constructor m_htnWorldState parameter.
}

void HTNMethod::AddTask(HTNPrimitive* htnPrimitive)
{
    m_nodeList.push_back(HTNPrimitivePtr(htnPrimitive));
}

void HTNMethod::AddTask(HTNCompound* htnCompound)
{
    m_nodeList.push_back(HTNCompoundPtr(htnCompound));
}

HTNNodeList& HTNMethod::GetTasks()
{
    if (!m_alreadyCreatedTasks)
    {
        CreateTasks();
        m_alreadyCreatedTasks = true;
    }
    return m_nodeList;
}

//*******************************************************************
constexpr int c_MaxSearchDepth = 50;

struct DecompositionFrame
{
    int m_stackCounter;
    int m_worldStateStackCounter;
    DecompositionFrame(int s, int w) : m_stackCounter(s), m_worldStateStackCounter(w) {}
};

void PrintHTNPlanStack(std::deque<HTNPrimitivePtr> htnPlanStack)
{
    std::stringstream ss;
    ss << "htnPlanStack size = " << htnPlanStack.size() << ": [";
    for (std::deque<HTNPrimitivePtr> dump = htnPlanStack; !dump.empty(); dump.pop_front())
        ss << dump.front()->ToString() << ", ";
    ss << "]";
    pLog(ss);
}

void PrintWorldStateStack(std::stack<HTNWorldState*> worldStateStack)
{
    std::stringstream ss;
    ss << "WorldStateStack size = " << worldStateStack.size();
    pLog(ss);
    pLog("WorldStateStack: ");
    for (std::stack<HTNWorldState*> dump = worldStateStack; !dump.empty(); dump.pop())
        worldStateStack.top()->Print();
}

void PrintNodeStack(std::stack< StackNodePtr > nodeStack)
{
    std::stringstream ss;
    ss << "NodeStack size = " << nodeStack.size() << ": [";
    for (std::stack< StackNodePtr > dump = nodeStack; !dump.empty(); dump.pop())
        ss << "(" << dump.top()->m_htnNode->m_name << ":" << (dump.top()->m_isOr ? "||": "&&") << "), ";
    ss << "]";
    pLog(ss);
}

void PrintDecompositions(std::stack< DecompositionFrame > decompositions)
{
    std::stringstream ss;
    ss << "Decompositions size = " << decompositions.size() << ": [";
    for (std::stack< DecompositionFrame > dump = decompositions; !dump.empty(); dump.pop())
        ss <<  "(" << dump.top().m_stackCounter << ":" << dump.top().m_worldStateStackCounter << "), ";
    ss << "]";
    pLog(ss);
}

HTNPrimitiveList HTNIterative(HTNWorldState &htnWorldState, HTNCompound &htnRoot, int searchDepth)
{
    std::stringstream ss;
    ss << "Entering HTNIterative, root node = " + htnRoot.ToString() + ", containing methods:\n";
    for (auto &htnMethod : htnRoot.m_methods)
    {
        ss << "Method: ";
        for (auto &task : htnMethod->m_nodeList)
        {
            ss << task->ToString() << ", ";
        }
    }
    pLog(ss);
    
    std::deque<HTNPrimitivePtr> htnPlanStack;
    std::stack<HTNWorldState*> worldStateStack;
    std::stack< StackNodePtr > nodeStack;
    std::stack< DecompositionFrame > decompositions; // std::stack< stackCounter, worldStateCounter>

    worldStateStack.push(&htnWorldState);
    nodeStack.push( MakeSharedStackNodePtr(MakeShareableCompound(htnRoot), false) );
    bool lastTaskPrecon = true;
    
    StackNodePtr currentNode = nodeStack.top();
    
    while (searchDepth <= c_MaxSearchDepth && static_cast<int>(nodeStack.size()) > 0)
    {
        if (c_debug)
        {
            pLog("");
            PrintNodeStack(nodeStack);
            PrintDecompositions(decompositions);
            PrintHTNPlanStack(htnPlanStack);
            PrintWorldStateStack(worldStateStack);
            pLog("");
        }

        currentNode = nodeStack.top(); // y takes the form (htnNode, &&) or (htnNode, ||), where htnNode is one of HTNPrimitive, HTNCompound or HTNMethod
        nodeStack.pop();
        
        //process the node at the front of the nodeStack
        if ((currentNode->m_isOr && !lastTaskPrecon) || (!(currentNode->m_isOr) && lastTaskPrecon))
        // if node is of form 'htnNode || false' or 'htnNode && true', then decompose and evaluate htnNode.
        // Else, simply discard htnNode and continue
        {
            switch (currentNode->m_htnNode->m_HTNType)
            {
                case HTNType::Method:
                {
                    pLog("Processing HTNType::Method");
                    HTNMethodPtr htnMethod = CastNodeToMethod(currentNode->m_htnNode);
                    
                    lastTaskPrecon = htnMethod->Preconditions(*worldStateStack.top());
                    if (lastTaskPrecon)
                    {
                        pLog("lastTaskPrecon == true");
                        //construct the tasks of this method, and push them onto the nodeStack. The first task should be at the top of the nodeStack
                        HTNNodeList taskList = htnMethod->GetTasks();
                        for (auto task = taskList.rbegin(); task != taskList.rend(); ++task)
                        {
                            nodeStack.push(MakeSharedStackNodePtr(*task, false));
                        }
                    } else {
                        pLog("lastTaskPrecon == false");
                    }
                    break;
                }
                case HTNType::Primitive:
                {
                    pLog("Processing HTNType::Primitive");
                    HTNPrimitivePtr htnPrimitive = CastNodeToPrimitive(currentNode->m_htnNode);
                    lastTaskPrecon = htnPrimitive->Preconditions(*worldStateStack.top());
                    if (lastTaskPrecon)
                    {
                        pLog("lastTaskPrecon == true");
                        worldStateStack.push(new HTNWorldState(*worldStateStack.top()));
                        htnPrimitive->Effect(*worldStateStack.top()); // simulate the effect of this primitive on the current worldState.
                        htnPlanStack.push_back(htnPrimitive);
                    }
                    else
                        pLog("lastTaskPrecon == false");
                    break;
                }
                case HTNType::Compound:
                {
                    pLog("Processing HTNType::Compound");
                    HTNCompoundPtr htnCompound = CastNodeToCompound(currentNode->m_htnNode);
                    
                    // record the current worldState and plan. This will allow us to backtrack planning this task fails.
                    decompositions.push(DecompositionFrame(static_cast<int>(nodeStack.size()), static_cast<int>(htnPlanStack.size())));
                    
                    //construct methods of this task, and push them onto the nodeStack. The highest priority method should be at the top of the nodeStack.
                    HTNMethodList methodList = htnCompound->GetMethods();
                    for (auto method = methodList.rbegin(); method != methodList.rend(); ++method)
                    {
                        nodeStack.push(MakeSharedStackNodePtr(*method, true));
                    }
                    
                    lastTaskPrecon = false;
                    break;
                }
            }
        } else {
            pLog("Consume, no action");
        }
        
        //backtrack as necessary, using the decomposition markers
        if (!lastTaskPrecon && !(decompositions.empty()))
        {
            pLog("Task preconditions failed. Backtrack?");
            while (static_cast<int>(nodeStack.size()) <= decompositions.top().m_stackCounter)
            {
                while (static_cast<int>(htnPlanStack.size()) > decompositions.top().m_worldStateStackCounter)
                {
                    pLog("pop from worldStateStack, pop from htnPlanStack");
                    delete worldStateStack.top();
                    worldStateStack.pop();
                    htnPlanStack.pop_back();
                }
                pLog("pop from decompositions");
                decompositions.pop();
            }
        }
        
        if (lastTaskPrecon && !(decompositions.empty()))
        {
            pLog("Task preconditions succeeded.");
            //clear any finished decompositions from the decompositions stack.
            while (static_cast<int>(nodeStack.size()) < decompositions.top().m_stackCounter)
            {
                pLog("pop from decompositions");
                decompositions.pop();
            }
        }
        
        searchDepth += 1;
    }
    
    if (worldStateStack.size() > 0)
    {
        //copy the planned htnWorldState back into the parameter htnWorldState
        htnWorldState = (*worldStateStack.top());
    }
    
    return htnPlanStack;
}
