#pragma once

#include "AbstractItem.h"

class Item : public AbstractItem {
public:
    Item(EItemType itemE, ELocations location, UPlayerData* carryingPlayer=nullptr): AbstractItem(itemE, location, carryingPlayer) {};
};