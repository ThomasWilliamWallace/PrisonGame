#pragma once

#include "PlatformSpecific.h"
#include "PlayerRegistry.generated.h"

UCLASS()
class UPlayerRegistry : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
        TMap<int, UPlayerData*> m_playerMap;

    void RegisterPlayer(UPlayerData* playerData);
    void DeregisterPlayer(int key);
};