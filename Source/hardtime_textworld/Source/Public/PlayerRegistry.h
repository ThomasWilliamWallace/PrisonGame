#pragma once

#include "PlatformSpecific.h"
#include "PlayerData.h"

class UPlayerRegistry{

public:
    PlayerMap m_playerMap;
    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};