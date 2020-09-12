#include "Missions.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "Constants.h"

std::string MissionClass::MissionName()
{
	switch (m_mission)
	{
	case (EMissions::increaseAgility):
		return "increase agility";
	case (EMissions::increaseStrength):
		return "increase strength";
	case (EMissions::increaseIntelligence):
		return "increase intelligence";
	case (EMissions::bringItemToRoom):
		return "bring item to room";
	case (EMissions::noMission):
		return "no mission";
	}
	return "UnrecognisedMission";
}

std::string MissionClass::MissionNarrative()
{
    switch (m_mission)
    {
        case EMissions::noMission:
            return "No Mission\n";
        case EMissions::increaseAgility:
            return "Mission: must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getAgility()) + ")";
        case EMissions::increaseStrength:
            return "Mission: must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getStrength()) + ")";
        case EMissions::increaseIntelligence:
            return "Mission: must " + MissionName() + " to " + FormatDouble(m_objective) + ". (current=" + FormatDouble(m_owner->pStats.getIntelligence()) + ")";
        case EMissions::bringItemToRoom:
            return "Mission: must bring a " + ItemTypeToString(m_itemType) + " to the " + m_locationClass.ToString() + ".";
    }
    return "ERROR: MISSION TYPE NOT RECOGNISED";
}

MissionClass::MissionClass(EMissions mission, AbstractPlayerData* owner, double objective):
	m_mission(mission),
	m_owner(owner),
	m_objective(objective)
{}

MissionClass::MissionClass(EMissions mission, AbstractPlayerData* owner, EItemType itemType, ELocations location):
	m_mission(mission),
	m_owner(owner),
	m_itemType(itemType),
	m_locationClass(location)
{}

MissionClass::MissionClass():
	m_mission(EMissions::noMission),
	m_owner(nullptr)
{}

MissionClass::MissionClass(const MissionClass& missionClass) :
	m_mission(missionClass.m_mission),
	m_owner(missionClass.m_owner),
	m_objective(missionClass.m_objective),
	m_itemType(missionClass.m_itemType),
	m_locationClass(missionClass.m_locationClass)
{}

MissionClass::MissionClass(AbstractPlayerData* owner):
	m_mission(GetRandomMission()),
	m_owner(owner)
{
	m_mission = EMissions::bringItemToRoom;
	m_itemType = EItemType::ball;
	m_locationClass = ELocations::mainHall; // GetRandomLocation();
	return;
	switch (m_mission)
	{
	case EMissions::noMission:
		break;
	case EMissions::increaseAgility:
		m_objective = m_owner->pStats.getAgility();
		break;
	case EMissions::increaseStrength:
		m_objective = m_owner->pStats.getStrength();
		break;
	case EMissions::increaseIntelligence:
		m_objective = m_owner->pStats.getIntelligence();
		break;
	case EMissions::bringItemToRoom:
		m_itemType = GetRandomItemType();
		m_locationClass = GetRandomLocation();
		break;
	}
	m_objective += 3; //todo ensure that the mission is achievable, ie 100 or below
}

bool MissionClass::IsMissionComplete(USimWorld &world)
{
	switch (m_mission)
	{
	case EMissions::increaseAgility:
		return (m_objective <= m_owner->pStats.getAgility());
	case EMissions::increaseStrength:
		return (m_objective <= m_owner->pStats.getStrength());
	case EMissions::increaseIntelligence:
		return (m_objective <= m_owner->pStats.getIntelligence());
	case EMissions::bringItemToRoom:
		for (auto &item : world.items)
		{
			if ((item->m_itemType == m_itemType) &&
			    (item->m_locationClass.location == m_locationClass.location) &&
                	    (item->m_carryingPlayer == nullptr))
			{
				return true;
			}
		}
		return false;
	case EMissions::noMission:
		return false;
	}
	return false;
}
