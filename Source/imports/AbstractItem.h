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
    SimItem(AbstractItem* realItem):
        AbstractItem(realItem->m_itemType, realItem->m_locationClass.location, realItem->m_carryingPlayer),
        m_realItem(realItem)
    {};
    SimItem(AbstractItem* realItem, EItemType itemE, ELocations location, AbstractPlayerData* carryingPlayer=nullptr):
        AbstractItem(itemE, location, carryingPlayer),
        m_realItem(realItem)
    {};
    SimItem(SimItem& item):
        SimItem(item.m_realItem, item.m_itemType, item.m_locationClass.location, item.m_carryingPlayer)
    {};
    
    AbstractItem* m_realItem;
};
