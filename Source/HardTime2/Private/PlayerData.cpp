#include "PlayerData.h"
#include "Missions.h"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "HardTime2Character.h"
#include "ActorItem.h"
#include "pLog.h"

std::string UPlayerData::CharacterName()
{
	std::string string_name = TCHAR_TO_UTF8(*(m_playerName.ToString()));
	return string_name;
}

void UPlayerData::PrintPlayer()
{
	std::stringstream ss;
    ss << "*** PLAYER " << CharacterName() << " ***\n";
    ss << "playerTargetPtr=" << playerTargetPtr << "\n";
    ss << "item=";
    if (itemPtr != nullptr)
        ss << itemPtr->ToString() << "\n";
    else
        ss << "null\n";
    ss << "itemFocus=";
    if (itemFocusPtr != nullptr)
        ss << itemFocusPtr->ToString() << "\n";
    else
        ss << "null\n";
	ss << "missionOffer=";
	if (missionOffer.get() != nullptr) {
		ss << missionOffer->MissionNarrative() << "\n";
	}
	else {
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
	return (*(relMap.Find(requestedPlayer->abstractPlayerData.m_key)))->isRequestedRecently;
}

void UPlayerData::SetRequested(UPlayerData* requestedPlayer)
{
	(*(relMap.Find(requestedPlayer->abstractPlayerData.m_key)))->SetRecentlyRequested();
}

UPlayerData::UPlayerData()
{
	itemPtr = nullptr;
	itemFocusPtr = nullptr;
    abstractPlayerData.action = std::make_shared<BaseAction>(EActions::goToGym);
	pLog("Constructing UPlayerData");
}

UPlayerData::UPlayerData(const FObjectInitializer& ObjectInitializer)
{
	pLog("Constructing UPlayerData with FObjectInitializer");

	itemPtr = nullptr;
	itemFocusPtr = nullptr;
    abstractPlayerData.action = std::make_shared<BaseAction>(EActions::goToGym);
}

class UWorld* UPlayerData::GetWorld() const
{
	if (!IsValid(this))
	{
		pLog("!IsValid(this) inside UPlayerData::GetWorld()", true);
		return nullptr;
	}

	if (!IsValid(physicalCharacter))
	{
		pLog("!IsValid(physicalCharacter) inside UPlayerData::GetWorld()", true);
		return nullptr;
	}

	if (nullptr == physicalCharacter->GetWorld())
	{
		pLog("nullptr == physicalCharacter->GetWorld() inside UPlayerData::GetWorld()", true);
		return nullptr;
	}

	return physicalCharacter->GetWorld();
}

bool OtherInReach(AbstractPlayerData& playerPtr, AbstractPlayerData& otherPlayerPtr, PlayerMap& playerMap)
{
    if ((otherPlayerPtr.locationClass.location == playerPtr.locationClass.location) && (&otherPlayerPtr != &playerPtr))
        return true;
    else
        return false;
}