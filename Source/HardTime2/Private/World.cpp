#include "World.hpp"
#include "ActorItem.h"

World::World()
{
    weightsOccupied  = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    bedOccupied      = nullptr;
//    items.push_back(new AActorItem(ItemType::extinguisher, Locations::mainHall));
//    items.push_back(new AActorItem(ItemType::bottle      , Locations::mainHall));
//    items.push_back(new AActorItem(ItemType::hammer      , Locations::circuitTrack));
//    items.push_back(new AActorItem(ItemType::ball        , Locations::mainHall));
//    items.push_back(new AActorItem(ItemType::mirror      , Locations::bedroom));
//    items.push_back(new AActorItem(ItemType::rock        , Locations::library));
}

void World::Clean()
{
    bedOccupied      = nullptr;
    circuitsOccupied = nullptr;
    studyOccupied    = nullptr;
    weightsOccupied  = nullptr;
}

void World::WorldEffects(Player player[], int frame)
{
    if (bedOccupied != nullptr)
    {
        bedOccupied->pStats.deltaHealth(1);
    }
    if (circuitsOccupied != nullptr)
    {
        circuitsOccupied->pStats.deltaAgility(1);
    }
    if (studyOccupied != nullptr)
    {
        studyOccupied->pStats.deltaIntelligence(1);
    }
    if (weightsOccupied != nullptr)
    {
        weightsOccupied->pStats.deltaStrength(1);
    }
}