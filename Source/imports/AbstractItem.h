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
    SimItem(RealItemType* realItem); // HTNPlanner calls the SimItem(SimItem& item) constructor where Unreal calls the SimItem(RealItemType* realItem)- the two constructors do different things.
                                    // Need to unify the constructor calling, so as to eliminate the HTNWorldState header ifdefs, which Unreal cannot handle.
                                    // This means one constructor always used to create from an existing SimItem, and one always used to create a new SimItem from a RealItem.
                                    // If necessary, we can use named constructors to differentiate the two situations.
                                    // We can also pass the RealItem pointer type into HTNWorldState constructor, instead of passing in SimItems.
    SimItem(RealItemType* realItem, EItemType itemE, ELocations location, AbstractPlayerData* carryingPlayer = nullptr);
    SimItem(SimItem& item);

    RealItemType* m_realItem;
};