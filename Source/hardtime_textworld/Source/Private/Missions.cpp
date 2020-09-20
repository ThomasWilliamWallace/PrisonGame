#include "Missions.h"
#include "PlayerData.h"
#include "SimWorld.h"
#include "Constants.h"


MissionClass::MissionClass(EMissions mission, AbstractPlayerData* owner, double objective):
	AbstractMission(mission, owner, objective)
{}

MissionClass::MissionClass(EMissions mission, AbstractPlayerData* owner, EItemType itemType, ELocations location):
	AbstractMission(mission, owner, itemType, location)
{}

MissionClass::MissionClass(const MissionClass& missionClass):
	AbstractMission(missionClass.m_mission, missionClass.m_owner, missionClass.m_objective)
{
	m_itemType = missionClass.m_itemType;
	m_locationClass = missionClass.m_locationClass;
}

MissionClass::MissionClass(AbstractPlayerData* owner):
	AbstractMission(RandomMission::CreateRandomMission, owner)
{}

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
