#include "Missions.hpp"
#include "Player.hpp"
#include "World.hpp"

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

std::string MissionClass::MissionNarrative()
{
    switch (m_mission)
    {
        case Missions::noMission:
            return "No Mission\n";
        case Missions::increaseAgility:
            return "Mission: " + m_owner->name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getAgility()) + ")\n";
        case Missions::increaseStrength:
            return "Mission: " + m_owner->name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getStrength()) + ")\n";
        case Missions::increaseIntelligence:
            return "Mission: " + m_owner->name + " must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getIntelligence()) + ")\n";
        case Missions::bringItemToRoom:
            return "Mission: " + m_owner->name + " must bring a " + ItemTypeToString(m_itemType) + " to the " + m_locationClass.ToString() + ".\n";
    }
    return "ERROR: MISSION TYPE NOT RECOGNISED";
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

MissionClass::MissionClass(Missions mission, Player* owner, double objective):
	m_mission(mission),
	m_owner(owner),
	m_objective(objective)
{}

MissionClass::MissionClass(Missions mission, Player* owner, EItemType itemType, Locations location):
	m_mission(mission),
	m_owner(owner),
	m_itemType(itemType),
	m_locationClass(location)
{}

MissionClass::MissionClass():
	m_mission(Missions::noMission),
	m_owner(nullptr)
{}

MissionClass::MissionClass(const MissionClass& missionClass) :
	m_mission(missionClass.m_mission),
	m_owner(missionClass.m_owner),
	m_objective(missionClass.m_objective),
	m_itemType(missionClass.m_itemType),
	m_locationClass(missionClass.m_locationClass)
{}

MissionClass::MissionClass(Player* owner):
	m_mission(GetRandomMission()),
	m_owner(owner)
{
	m_mission = Missions::bringItemToRoom;
	m_itemType = EItemType::sword;
	m_locationClass = LocationClass(Locations::bedroom);
	return;
	switch (m_mission)
	{
	case Missions::noMission:
		break;
	case Missions::increaseAgility:
		m_objective = m_owner->pStats.getAgility();
		break;
	case Missions::increaseStrength:
		m_objective = m_owner->pStats.getStrength();
		break;
	case Missions::increaseIntelligence:
		m_objective = m_owner->pStats.getIntelligence();
		break;
	case Missions::bringItemToRoom:
		m_itemType = GetRandomItemType();
		m_locationClass = GetRandomLocation();
		break;
	}
	m_objective += 3; //todo ensure that the mission is achievable, ie 100 or below
}

bool MissionClass::IsMissionComplete(World &world)
{
	switch (m_mission)
	{
	case Missions::increaseAgility:
		return (m_objective <= m_owner->pStats.getAgility());
	case Missions::increaseStrength:
		return (m_objective <= m_owner->pStats.getStrength());
	case Missions::increaseIntelligence:
		return (m_objective <= m_owner->pStats.getIntelligence());
	case Missions::bringItemToRoom:
		for (auto &item : world.items)
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
