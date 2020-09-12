#include "PlayerData.h"
#include "Missions.h"
#include "SimWorld.h"
#include "Locations.h"
#include <sstream>
#include "HardTime2Character.h"
#include "pLog.h"

std::string CharacterName(UPlayerData* playerPtr)
{
	if (playerPtr == nullptr)
		return "c_empty";
	else
		//return playerPtr->m_playerName;
		return "No-Name";
}

void UPlayerData::PrintPlayer()
{
	std::stringstream ss;
    ss << "*** PLAYER " << " ***\n";
	ss << "action=" << ActionToString(action->m_action) << "\n";
	ss << "lastAction=" << ActionToString(lastAction->m_action) << "\n";
    ss << "location=" << locationClass.ToString() << "\n";
    ss << "lastLocation=" << lastLocationClass.ToString() << "\n";
//    ss << "attacked=" << BoolToString(attacked) << "\n";
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
    ss << "missionClass=" << missionClass.MissionNarrative() << "\n";
    ss << "missionOffer=" << missionOffer.MissionNarrative() << "\n";
    ss << "cash=" << cash << "\n";
    ss << "sentence=" << sentence << "\n";
	ss << "m_key=" << m_key << "\n";
    ss << "\n";
	pLog(ss);
//    pStats.PrintStats();
}

MissionClass CreateNewMission(UPlayerData* playerPtr)
{
    if (playerPtr == nullptr)
    {
        return MissionClass();
    }
    EMissions tempMission = GetRandomMission();
    double tempObjective;
    switch (tempMission)
    {
        case EMissions::noMission:
            return MissionClass();
        case EMissions::increaseAgility:
            tempObjective = playerPtr->pStats.getAgility();
            break;
        case EMissions::increaseStrength:
            tempObjective = playerPtr->pStats.getStrength();
            break;
        case EMissions::increaseIntelligence:
            tempObjective = playerPtr->pStats.getIntelligence();
            break;
        case EMissions::bringItemToRoom:
            return MissionClass(tempMission, &(playerPtr->abstractPlayerData), GetRandomItemType(), GetRandomLocation());
		default:
			throw std::invalid_argument("Selected an invalid mission type.");
    }
    tempObjective += 3; //todo ensure that the mission is achievable, ie 100 or below
    return MissionClass(tempMission, &(playerPtr->abstractPlayerData), tempObjective);
}

void UPlayerData::UpdateMissions(USimWorld &world)
{
    if (missionClass.IsMissionComplete(world))
    {
		std::stringstream ss;
		ss << " has completed his mission to " << missionClass.MissionName() << " and now has sanity=" << FormatDouble(pStats.getSanity()) << "!";
		pLog(ss, true);
        pStats.deltaSanity(5);
		missionClass = MissionClass(&(this->abstractPlayerData));
		pLog(missionClass.MissionNarrative(), true);
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

UPlayerData::UPlayerData()
{
	itemPtr = nullptr;
	itemFocusPtr = nullptr;
    action = std::make_shared<BaseAction>(EActions::goToGym);
	pLog("Constructing UPlayerData");
}

UPlayerData::UPlayerData(const FObjectInitializer& ObjectInitializer)
{
	pLog("Constructing UPlayerData with FObjectInitializer");

	itemPtr = nullptr;
	itemFocusPtr = nullptr;
	action = std::make_shared<BaseAction>(EActions::goToGym);
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