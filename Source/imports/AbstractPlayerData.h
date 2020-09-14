#pragma once

#include <iostream>
#include "PStats.h"
#include "AbstractMission.h"
#include "AbstractAction.h"

class AbstractPlayerData
{
public:
    PStats pStats;

    int m_key; //players PlayerRegistry index
    std::shared_ptr<BaseAction> action = std::make_shared<BaseAction>(EActions::useRoom); //stores the current action being attempted. This is held till the end of the frame, as it may be interrupted by another action.
    std::shared_ptr<BaseAction> lastAction = std::make_shared<BaseAction>(EActions::useRoom); //stores the last action taken. Useful for checking if hidden.
    LocationClass locationClass; //location maps to a discrete set of locations, gym, library, circuit track, bed.
    LocationClass lastLocationClass; //location the character was at when the turn began. Used by the print display.
    bool attacked = false; //tracks whether an attack has disrupted his turn.
    std::string narrative; //printed at the end of each round, giving the update for this character
    std::string m_playerName = "No-name"; //name of the character, used in speech
    std::shared_ptr<AbstractMission> missionClass = std::make_shared<AbstractMission>(RandomMission::CreateRandomMission, this); //a mission currently assigned to the character
    
    virtual ~AbstractPlayerData() = default;
    virtual void PrintPlayer();

    AbstractPlayerData();
};

std::string CharacterName(AbstractPlayerData* playerPtr);