#include "PlayerData.h"
#include "Missions.h"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "pLog.h"

std::string UPlayerData::CharacterName()
{
	return abstractPlayerData.m_playerName;
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
	ss << "missionOffer=";
	if (missionOffer.get() != nullptr) {
		ss << missionOffer->MissionNarrative() << "\n";
	} else {
		ss << "NULLPTR\n";
	}
    ss << "cash=" << cash << "\n";
    ss << "sentence=" << sentence << "\n";
	ss << "m_key=" << abstractPlayerData.m_key << "\n";
    ss << "\n";
	pLog(ss);
//    pStats.PrintStats();
	abstractPlayerData.PrintPlayer();
}

void UPlayerData::UpdateMissions(USimWorld &world)
{
    MissionClass* tempMissionClass = static_cast<MissionClass*>(abstractPlayerData.missionClass.get());
    if (tempMissionClass->IsMissionComplete(world))
    {
		std::stringstream ss;
		ss << " has completed his mission to " << abstractPlayerData.missionClass->MissionName() << " and now has sanity=" << FormatDouble(abstractPlayerData.pStats.getSanity()) << "!";
		pLog(ss, true);
		abstractPlayerData.pStats.deltaSanity(5);
        abstractPlayerData.missionClass = std::make_shared<MissionClass>(&(this->abstractPlayerData));
		pLog(tempMissionClass->MissionNarrative(), true);
    }
}

bool UPlayerData::IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType)
{
	return relMap.find(requestedPlayer->abstractPlayerData.m_key)->second->isRequestedRecently;
}

void UPlayerData::SetRequested(UPlayerData* requestedPlayer)
{
	relMap.find(requestedPlayer->abstractPlayerData.m_key)->second->SetRecentlyRequested();
}

UPlayerData::UPlayerData()
{
    cash = 0;
    sentence = 5;
	itemPtr = nullptr;
    abstractPlayerData.action = std::make_shared<BaseAction>(EActions::goToGym);
    missionOffer = nullptr;
    abstractPlayerData.missionClass = std::make_shared<MissionClass>(&abstractPlayerData);
	pLog("Constructing UPlayerData");
}

bool OtherInReach(AbstractPlayerData& playerPtr, AbstractPlayerData& otherPlayerPtr)
{
    if (otherPlayerPtr.locationClass.location == playerPtr.locationClass.location) {
        return true;
    } else {
        return false;
    }
}