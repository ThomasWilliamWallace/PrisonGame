#pragma once

#include "PlayerMap.hpp"

class PlayerRegistry{

public:
    PlayerMap m_playerMap;
    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};