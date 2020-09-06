#pragma once

#include "PlayerMap.h"

class PlayerRegistry{

public:
    PlayerMap m_playerMap;
    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};