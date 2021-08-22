#pragma once

#include "Locations.h"
#include "PlatformSpecific.h"
#include "EItemType.h"

class UPlayerData;

std::string ItemTypeToString(EItemType itemType);
EItemType GetRandomItemType();

class AbstractItem
{
public:
    EItemType m_itemType;
    LocationClass m_locationClass;
    UPlayerData* m_carryingPlayer;
    
    AbstractItem(EItemType itemE, ELocations location, UPlayerData* carryingPlayer=nullptr): m_itemType(itemE), m_locationClass(location), m_carryingPlayer(carryingPlayer) {};
    
    virtual ~AbstractItem() = default;
    
    std::string ToString();
};

enum class CreateSimFromRealItem {
    CreateSimFromRealItem
};

class SimItem : public AbstractItem
{
public:
    SimItem(CreateSimFromRealItem c, RealItemType* realItem);
    SimItem(RealItemType* realItem, EItemType itemE, ELocations location, UPlayerData* carryingPlayer = nullptr);
    SimItem(SimItem& item);
    
    RealItemType* m_realItem;
};
