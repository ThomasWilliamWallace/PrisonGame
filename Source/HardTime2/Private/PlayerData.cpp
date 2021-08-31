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
    if (itemPtr != nullptr) {
        ss << itemPtr->ToString() << "\n";
    } else {
        ss << "null\n";
    }
    ss << "itemFocus=";
    if (itemFocusPtr != nullptr) {
        ss << itemFocusPtr->ToString() << "\n";
    } else {
        ss << "null\n";
    }
    if (missionClass != nullptr) {
        ss << missionClass->MissionNarrative() << "\n";
    }
    else {
        ss << "NULLPTR\n";
    }
	ss << "missionOffer=";
	if (missionOffer != nullptr) {
		ss << missionOffer->MissionNarrative() << "\n";
	} else {
		ss << "NULLPTR\n";
	}
	ss << "m_key=" << m_key << "\n";
    ss << "action=" << action->ToString() << "\n";
    ss << "lastAction=" << lastAction->ToString() << "\n";
    ss << "location=" << locationClass.ToString() << "\n";
    ss << "lastLocation=" << lastLocationClass.ToString() << "\n";
    ss << "attacked=" << BoolToString(attacked) << "\n";
    ss << "narrative=" << narrative << "\n";
    ss << "\n";
	pLog(ss);
    pStats->PrintStats();
}

void UPlayerData::UpdateMissions(USimWorld &world)
{
    MissionClass* tempMissionClass = static_cast<MissionClass*>(missionClass.get());
    if (tempMissionClass->IsMissionComplete(world))
    {
		std::stringstream ss;
		ss << CharacterName() << " has completed his mission to " << missionClass->MissionName() << " and now has sanity=" << FormatDouble(pStats->getSanity()) << "!";
		pLog(ss, true);
		pStats->deltaSanity(5);
        missionClass = std::make_shared<MissionClass>(this);
		pLog("Old mission: " + tempMissionClass->MissionNarrative(), true);
		pLog("New mission: " + missionClass->MissionNarrative(), true);
    }
}

bool UPlayerData::IsRequestedRecently(UPlayerData* requestedPlayer, EItemType m_itemType)
{
	return (*(relMap.Find(requestedPlayer->m_key)))->isRequestedRecently;
}

void UPlayerData::SetRequested(UPlayerData* requestedPlayer)
{
	(*(relMap.Find(requestedPlayer->m_key)))->SetRecentlyRequested();
}

// Member variables set in constructor to work with Unreal Engine.
UPlayerData::UPlayerData()
{
	pLog("Constructing UPlayerData");
    missionOffer = nullptr;
    missionClass = std::make_shared<MissionClass>(this);
    lastAction = std::make_shared<BaseAction>(EActions::noAction);
    attacked = false;
    narrative = "Narrative not set";
	m_playerName = "No-name";
	aiController = AI::doNothingAI;
	itemPtr = nullptr;
	playerTargetPtr = nullptr;
	itemFocusPtr = nullptr;
	physicalCharacter = nullptr;
    action = std::make_shared<BaseAction>(EActions::noAction);
    pStats = CreateDefaultSubobject<UPStats>(TEXT("PlayerStats"));
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

bool UPlayerData::OtherInReach(UPlayerData& otherPlayerPtr, PlayerMap& playerMap)
{
    if ((otherPlayerPtr.locationClass.location == locationClass.location) && (&otherPlayerPtr != this)) {
        return true;
    } else {
        return false;
    }
}
