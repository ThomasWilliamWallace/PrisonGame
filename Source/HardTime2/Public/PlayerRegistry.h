#pragma once

#include "PlatformSpecific.h"

class PlayerRegistry{

public:
    PlayerMap m_playerMap;
    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};