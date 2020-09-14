#pragma once

#include "Locations.h"
#include "PlatformSpecific.h"
#include "EItemType.h"

class AbstractPlayerData;

std::string ItemTypeToString(EItemType itemType);
EItemType GetRandomItemType();

class AbstractItem
{
public:
    EItemType m_itemType;
    LocationClass m_locationClass;
    AbstractPlayerData* m_carryingPlayer;
    
    AbstractItem(EItemType itemE, ELocations location, AbstractPlayerData* carryingPlayer=nullptr): m_itemType(itemE), m_locationClass(location), m_carryingPlayer(carryingPlayer) {};
    
    virtual ~AbstractItem() = default;
    
    std::string ToString();
};

class SimItem : public AbstractItem
{
public:
    SimItem(RealItemType* realItem);
    SimItem(RealItemType* realItem, EItemType itemE, ELocations location, AbstractPlayerData* carryingPlayer = nullptr);
    SimItem(SimItem& item);

    RealItemType* m_realItem;
};