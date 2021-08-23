#include "PlayerData.h"
#include "Missions.h"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "pLog.h"

std::string UPlayerData::CharacterName()
{
	return m_playerName;
}

void UPlayerData::PrintPlayer()
{
	std::stringstream ss;
    ss << "*** PLAYER " << CharacterName() << " ***\n";
    ss << "item=";
    if (itemPtr != nullptr) {
        ss << itemPtr->ToString() << "\n";
    } else {
        ss << "null\n";
    }
    if (missionClass.get() != nullptr) {
        ss << missionClass->MissionNarrative() << "\n";
    }
    else {
        ss << "NULLPTR\n";
    }
	ss << "missionOffer=";
	if (missionOffer.get() != nullptr) {
		ss << missionOffer->MissionNarrative() << "\n";
	} else {
		ss << "NULLPTR\n";
	}
    ss << "cash=" << cash << "\n";
    ss << "sentence=" << sentence << "\n";
	ss << "m_key=" << m_key << "\n";
    ss << "action=" << action->ToString() << "\n";
    ss << "lastAction=" << lastAction->ToString() << "\n";
    ss << "location=" << locationClass.ToString() << "\n";
    ss << "lastLocation=" << lastLocationClass.ToString() << "\n";
    ss << "attacked=" << BoolToString(attacked) << "\n";
    ss << "narrative=" << narrative << "\n";
    ss << "\n";
	pLog(ss);
    pStats.PrintStats();
}

void UPlayerData::UpdateMissions(USimWorld &world)
{
    MissionClass* tempMissionClass = static_cast<MissionClass*>(missionClass.get());
    if (tempMissionClass->IsMissionComplete(world))
    {
		std::stringstream ss;
		ss << CharacterName() << " has completed his mission to " << missionClass->MissionName() << " and now has sanity=" << FormatDouble(pStats.getSanity()) << "!";
		pLog(ss, true);
		pStats.deltaSanity(5);
        missionClass = std::make_shared<MissionClass>(this);
		pLog(missionClass->MissionNarrative(), true);
    }
}

bool UPlayerData::IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType)
{
	return relMap.find(requestedPlayer->m_key)->second->isRequestedRecently;
}

void UPlayerData::SetRequested(UPlayerData* requestedPlayer)
{
	relMap.find(requestedPlayer->m_key)->second->SetRecentlyRequested();
}


// Member variables set in constructor to work with Unreal Engine.
UPlayerData::UPlayerData()
{
	pLog("Constructing UPlayerData");
    cash = 0;
    sentence = 5;
	itemPtr = nullptr;
    action = std::make_shared<BaseAction>(EActions::useRoom);
    missionOffer = nullptr;
    missionClass = std::make_shared<MissionClass>(this);
    lastAction = std::make_shared<BaseAction>(EActions::useRoom);
    attacked = false;
    narrative = "Narrative not set";
    m_playerName = "No-name";
}

bool UPlayerData::OtherInReach(UPlayerData& otherPlayerPtr)
{
    if (otherPlayerPtr.locationClass.location == locationClass.location) {
        return true;
    } else {
        return false;
    }
}
