#include "HTNPlanner.hpp"
#include "HTNDomain.hpp"
#include "pLog.hpp"
#include <sstream>
#include <stack>
#include <memory>

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
HTNCompound::HTNCompound(std::string name): HTNNode(name, HTNType::Compound) {}

void HTNCompound::AddMethod(HTNMethod* htnMethod)
{
    m_methods.push_back(HTNMethodPtr(htnMethod));
}

//*******************************************************************
HTNMethod::HTNMethod(std::string name): HTNNode(name, HTNType::Method) {}

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

//*******************************************************************
constexpr int c_MaxSearchDepth = 50;

struct DecompositionFrame
{
    int m_stackCounter;
    int m_worldStateStackCounter;
    DecompositionFrame(int s, int w) : m_stackCounter(s), m_worldStateStackCounter(w) {}
};

struct StackNode //represents 'm_htnNode &&' or 'm_htnNode ||'
{
    HTNNodePtr m_htnNode;
    bool m_isOr;
    StackNode(HTNNodePtr htnNode, bool isOr): m_htnNode(htnNode), m_isOr(isOr) {};
};

typedef std::shared_ptr<StackNode> StackNodePtr;

HTNPrimitiveList HTNIterative(HTNWorldState &htnWorldState, HTNCompound &htnCompound, int searchDepth)
{
    std::stringstream ss;
    ss << "Entering HTNIterative, root HTNCompound node = " + htnCompound.ToString() + ", containing methods:\n";
    for (auto &htnMethod : htnCompound.m_methods)
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
    worldStateStack.push(&htnWorldState);
    std::stack< StackNodePtr > nodeStack;
    nodeStack.push( std::shared_ptr<StackNode>(new StackNode(HTNNodePtr(&htnCompound), false) ) );
    std::stack< DecompositionFrame > decompositions; // std::stack< stackCounter, worldStateCounter>
    bool lastTaskPrecon = true;
    
    StackNodePtr currentNode = nodeStack.top();
    
    while (searchDepth <= c_MaxSearchDepth && static_cast<int>(nodeStack.size()) > 0)
    {
        currentNode = nodeStack.top(); // y takes the form (htnNode, &&) or (htnNode, ||), where htnNode is one of HTNPrimitive, HTNCompound or HTNMethod
        std::stringstream ss;
        ss << "currentNode->" << currentNode->m_htnNode->m_name << ", " << currentNode->m_isOr;
        pLog(ss);
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
                    HTNMethodPtr htnMethod = StaticCastSharedPtr<HTNMethod>(currentNode->m_htnNode);
                    
                    lastTaskPrecon = htnMethod->Preconditions(*worldStateStack.top());
                    if (lastTaskPrecon)
                    {
                        pLog("lastTaskPrecon == true");
                        //construct the tasks of this method, and push them onto the nodeStack. The first task should be at the top of the nodeStack
                        std::stack< StackNodePtr > tempNodeStack;
                        for (auto &t : htnMethod->GetTasks())
                        {
                            tempNodeStack.push(std::shared_ptr<StackNode>(new StackNode(t, false)));
                        }
                        while (!(tempNodeStack.empty()))
                        {
                            std::stringstream ss3;
                            ss3 << "Adding task to stack: " << tempNodeStack.top()->m_htnNode->ToString();
                            pLog(ss3);
                            nodeStack.push(tempNodeStack.top());
                            tempNodeStack.pop();
                        }
                    } else {
                        pLog("lastTaskPrecon == false");
                    }
                    break;
                }
                case HTNType::Primitive:
                {
                    pLog("Processing HTNType::Primitive");
                    HTNPrimitivePtr htnPrimitive = StaticCastSharedPtr<HTNPrimitive>(currentNode->m_htnNode);
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
                    HTNCompoundPtr htnCompound = StaticCastSharedPtr<HTNCompound>(currentNode->m_htnNode);
                    
                    // record the current worldState and plan. This will allow us to backtrack planning this task fails.
                    decompositions.push(DecompositionFrame(static_cast<int>(nodeStack.size()), static_cast<int>(worldStateStack.size())));
                    
                    //construct methods of this task, and push them onto the nodeStack. The highest priority method should be at the top of the nodeStack.
                    std::stack< StackNodePtr > tempNodeStack2;
                    for (auto &m : htnCompound->GetMethods())
                    {
                        tempNodeStack2.push(std::shared_ptr<StackNode>(new StackNode(m, true)));
                    }
                    while (!(tempNodeStack2.empty()))
                    {
                        std::stringstream ss1;
                        ss1 << "Adding method to stack: " << tempNodeStack2.top()->m_htnNode->ToString();
                        pLog(ss1);
                        nodeStack.push(tempNodeStack2.top());
                        tempNodeStack2.pop();
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
            std::stringstream ss5;
            ss5 << "nodeStack.size()=" << static_cast<int>(nodeStack.size()) << "\n";
            ss5 << "decompositions.size()=" << static_cast<int>(decompositions.size()) << "\n";
            ss5 << "worldStateStack.size()=" << static_cast<int>(worldStateStack.size()) << "\n";
            ss5 << "htnPlanStack.size()=" << static_cast<int>(htnPlanStack.size());
            pLog(ss5);
            while (static_cast<int>(nodeStack.size()) < decompositions.top().m_stackCounter)
            {
                std::stringstream ss4;
                ss4 << "decompositions.top()=[" << decompositions.top().m_stackCounter << ", " << decompositions.top().m_worldStateStackCounter << "]";
                pLog(ss4);
                while (static_cast<int>(worldStateStack.size()) > decompositions.top().m_worldStateStackCounter)
                {
                    pLog("pop from worldStateStack, pop from htnPlanStack");
                    delete worldStateStack.top();
                    worldStateStack.pop();
                    htnPlanStack.pop_back();
                }
                decompositions.pop();
            }
        }
        
        if (lastTaskPrecon && !(decompositions.empty()))
        {
            //clear any finished decompositions from the decompositions stack.
            while (static_cast<int>(nodeStack.size()) < decompositions.top().m_stackCounter)
            {
                decompositions.pop();
            }
        }
        
        searchDepth += 1;
    }
    
    if (worldStateStack.size() > 0)
    {
        //copy the planned htnWorldState back into the parameter htnWorldState
        htnWorldState.CopyFrom(*worldStateStack.top());
    }
    
    return htnPlanStack;
}
