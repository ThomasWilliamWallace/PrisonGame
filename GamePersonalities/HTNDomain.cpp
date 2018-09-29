//
//  HTNDomain.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "HTNDomain.hpp"
#include "Locations.hpp"

//Start HTNtasks*****************************************************
//***********************************************************
void Study::Effect(HTNWorldState &htnWorldState)
{
    htnWorldState.m_v.at(WorldE::intelligence) += 1;
    return;
}

void Study::Operator()
{
    return;
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

void Sleep::Operator()
{
    return;
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

void UseGym::Operator()
{
    return;
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

void RunCircuits::Operator()
{
    return;
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

void GoToGym::Operator()
{
    return;
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

void GoToLibrary::Operator()
{
    return;
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

void GoToBedroom::Operator()
{
    return;
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

void GoToCircuitTrack::Operator()
{
    return;
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

void GoToMainHall::Operator()
{
    return;
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

void Drink::Operator()
{
    return;
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

void Punch::Operator()
{
    return;
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