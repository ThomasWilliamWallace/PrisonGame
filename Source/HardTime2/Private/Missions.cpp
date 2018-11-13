//
//  Missions.cpp
//  GamePersonalities
//
//  Created by VITALIJA STEPUSAITYTE on 25/08/2018.
//  Copyright © 2018 Thomas. All rights reserved.
//

#include "Missions.hpp"
#include "AICharacterC.h"

std::string MissionClass::MissionName()
{
	switch (m_mission)
	{
	case (Missions::increaseAgility):
		return "increase agility";
	case (Missions::increaseStrength):
		return "increase strength";
	case (Missions::increaseIntelligence):
		return "increase intelligence";
	case (Missions::bringItemToRoom):
		return "bring item to room";
	case (Missions::noMission):
		return "no mission";
	}
	return "UnrecognisedMission";
}

Missions GetRandomMission()
{
	int random = rand() % 100;
	if (random<25)
	    return Missions::increaseStrength;
	else if (random<50)
	    return Missions::increaseAgility;
	else if (random<75)
	    return Missions::increaseIntelligence;
	else
		return Missions::bringItemToRoom;
}

MissionClass::MissionClass(Missions mission, double objective, AAICharacterC* owner) : m_mission(mission), m_objective(objective), m_owner(owner) {}

MissionClass::MissionClass(Missions mission, AAICharacterC* owner, ItemType itemType, Locations location) : m_mission(mission), m_owner(owner), m_itemType(itemType), m_locationClass(location) {}

MissionClass::MissionClass() : m_mission(Missions::noMission), m_objective(101), m_targetPlayerIndex(-1) {}

MissionClass::MissionClass(const MissionClass& missionClass) :
	m_mission(missionClass.m_mission),
	m_objective(missionClass.m_objective),
	m_targetPlayerIndex(missionClass.m_targetPlayerIndex),
	m_itemType(missionClass.m_itemType),
	m_locationClass(missionClass.m_locationClass)
{}

MissionClass::MissionClass(AAICharacterC* aiCharacterC) : m_mission(GetRandomMission()), m_owner(aiCharacterC)
{
	m_mission = Missions::bringItemToRoom;
	m_itemType = ItemType::sword;
	m_locationClass = LocationClass(Locations::bedroom);
	return;
	switch (m_mission)
	{
	case Missions::noMission:
		break;
	case Missions::increaseAgility:
		m_objective = aiCharacterC->agility;
		break;
	case Missions::increaseStrength:
		m_objective = aiCharacterC->strength;
		break;
	case Missions::increaseIntelligence:
		m_objective = aiCharacterC->intelligence;
		break;
	case Missions::bringItemToRoom:
		m_itemType = GetRandomItemType();
		m_locationClass = GetRandomLocation();
		break;
	}
	m_objective += 3; //todo ensure that the mission is achievable, ie 100 or below
}

bool MissionClass::IsMissionComplete()
{
	switch (m_mission)
	{
	case Missions::increaseAgility:
		return (m_objective <= m_owner->agility);
	case Missions::increaseStrength:
		return (m_objective <= m_owner->strength);
	case Missions::increaseIntelligence:
		return (m_objective <= m_owner->intelligence);
	case Missions::bringItemToRoom:
		for (auto &item : m_owner->m_items)
		{
			if ((item->m_itemType == m_itemType) && (item->m_locationClass.location == m_locationClass.location))
			{
				return true;
			}
		}
		return false;
	case Missions::noMission:
		return false;
	}
	return false;
}