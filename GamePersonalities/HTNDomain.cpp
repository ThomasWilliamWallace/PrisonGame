//
//  HTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNDomain.hpp"
#include "Locations.hpp"
#include "Player.hpp"

//Start HTNtasks*****************************************************
//***********************************************************
void Study::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::intelligence) += 1;
    return;
}

Actions Study::Operator(int playerIndex, Player player[])
{
    return Actions::useRoom;
}

bool Study::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::library;
}

std::string Study::ToString()
{
    std::string name = "Study";
    return name;
}

//***********************************************************
void Sleep::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::health) += 1;
    return;
}

Actions Sleep::Operator(int playerIndex, Player player[])
{
    return Actions::useRoom;
}

bool Sleep::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::bedroom;
}

std::string Sleep::ToString()
{
    std::string name = "Sleep";
    return name;
}

//***********************************************************
void UseGym::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::strength) += 1;
    return;
}

Actions UseGym::Operator(int playerIndex, Player player[])
{
    return Actions::useRoom;
}

bool UseGym::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::gym;
}

std::string UseGym::ToString()
{
    std::string name = "UseGym";
    return name;
}

//***********************************************************
void RunCircuits::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::agility) += 1;
    return;
}

Actions RunCircuits::Operator(int playerIndex, Player player[])
{
    return Actions::useRoom;
}

bool RunCircuits::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::circuitTrack;
}

std::string RunCircuits::ToString()
{
    std::string name = "RunCircuits";
    return name;
}

//***********************************************************
void GoToGym::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::gym);
    return;
}

Actions GoToGym::Operator(int playerIndex, Player player[])
{
    return Actions::goToGym;
}

bool GoToGym::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

std::string GoToGym::ToString()
{
    std::string name = "GoToGym";
    return name;
}

//***********************************************************
void GoToLibrary::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::library);
    return;
}

Actions GoToLibrary::Operator(int playerIndex, Player player[])
{
    return Actions::goToLibrary;
}

bool GoToLibrary::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

std::string GoToLibrary::ToString()
{
    std::string name = "GoToLibrary";
    return name;
}

//***********************************************************
void GoToBedroom::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::bedroom);
    return;
}

Actions GoToBedroom::Operator(int playerIndex, Player player[])
{
    return Actions::goToBedroom;
}

bool GoToBedroom::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

std::string GoToBedroom::ToString()
{
    std::string name = "GoToBedroom";
    return name;
}

//***********************************************************
void GoToCircuitTrack::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::circuitTrack);
    return;
}

Actions GoToCircuitTrack::Operator(int playerIndex, Player player[])
{
    return Actions::goToCircuitTrack;
}

bool GoToCircuitTrack::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) == Locations::mainHall;
}

std::string GoToCircuitTrack::ToString()
{
    std::string name = "GoToCircuitTrack";
    return name;
}

//***********************************************************
void GoToMainHall::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::location) = static_cast<int>(Locations::mainHall);
    return;
}

Actions GoToMainHall::Operator(int playerIndex, Player player[])
{
    return Actions::goToMainHall;
}

bool GoToMainHall::Preconditions(HTNWorldState &htnWorldState)
{
    return static_cast<Locations>(htnWorldState.m_v.at(WorldE::location)) != Locations::mainHall;
}

std::string GoToMainHall::ToString()
{
    std::string name = "GoToMainHall";
    return name;
}

//***********************************************************
void Drink::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::intelligence) -= 1;
    return;
}

Actions Drink::Operator(int playerIndex, Player player[])
{
    return Actions::noAction;
}

bool Drink::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

std::string Drink::ToString()
{
    std::string name = "Drink";
    return name;
}

//***********************************************************
void Punch::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::punches) += 1;
}

Actions Punch::Operator(int playerIndex, Player player[])
{
    //TODO pass in target player during planning
    player[playerIndex].playerTarget = 0;
    return Actions::attack;
}

bool Punch::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

std::string Punch::ToString()
{
    std::string name = "Punch";
    return name;
}

//***********************************************************
IncreaseIntelligenceMethod1::IncreaseIntelligenceMethod1()
{
    AddTask(new Study());
}

bool IncreaseIntelligenceMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
IncreaseIntelligenceMethod2::IncreaseIntelligenceMethod2()
{
    AddTask(new GoToLibraryCompound());
    AddTask(new Study());
}

bool IncreaseIntelligenceMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
IncreaseIntelligenceMethod3::IncreaseIntelligenceMethod3()
{
    AddTask(new Drink());
    AddTask(new AttackCompound());
}

bool IncreaseIntelligenceMethod3::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
IncreaseIntelligenceCompound::IncreaseIntelligenceCompound()
{
    m_methods.push_back(new IncreaseIntelligenceMethod1());
    m_methods.push_back(new IncreaseIntelligenceMethod2());
    m_methods.push_back(new IncreaseIntelligenceMethod3());
}

//***********************************************************
GoToLibraryMethod1::GoToLibraryMethod1()
{
    AddTask(new GoToLibrary());
}

bool GoToLibraryMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
GoToLibraryMethod2::GoToLibraryMethod2()
{
    AddTask(new GoToMainHall());
    AddTask(new GoToLibrary());
}

bool GoToLibraryMethod2::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
GoToLibraryCompound::GoToLibraryCompound()
{
    m_methods.push_back(new GoToLibraryMethod1());
    m_methods.push_back(new GoToLibraryMethod2());
}

//***********************************************************
AttackMethod1::AttackMethod1()
{
    AddTask(new Punch());
    AddTask(new Punch());
}

bool AttackMethod1::Preconditions(HTNWorldState &htnWorldState)
{
    return true;
}

//***********************************************************
AttackCompound::AttackCompound()
{
    m_methods.push_back(new AttackMethod1());
}
//End HTNtasks*****************************************************