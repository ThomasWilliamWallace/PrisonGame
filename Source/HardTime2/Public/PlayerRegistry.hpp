#pragma once

#include "PlayerMapFwd.hpp"

class PlayerRegistry{

public:
    PlayerMap m_playerMap;
    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};