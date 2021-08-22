#include "gtest/gtest.h"
#include "TranslateToHTNWorldState.h"
#include "HTNPlanner.h"
#include "HTNDomain.h"
#include "Locations.h"
#include "SimWorld.h"
#include "EItemType.h"
#include "pLog.h"
#include "PlayerData.h"
#include "Missions.h"
#include "BasicAI.h"
#include "HTNPrimitives.h"

//#include "Constants.h"
//#include "Actions.h"
//#include "HTNPlanner.h"
//#include "PlayerRegistry.h"
//#include "Names.h"


namespace test_helper {

    HTNPrimitiveList plan_from_world(UPlayerData* player, USimWorld& world)
    {
        //update worldstate from real world
        HTNWorldState htnWorldState = TranslateToHTNWorldState(player, world, world.playerRegistry.m_playerMap, nullptr);

        //make new plan
        HTNCompound* missionPtr = new PrisonerBehaviourCompound();
        HTNPrimitiveList htnPlan = HTNIterative(htnWorldState, *missionPtr, 0);

        return htnPlan;
    }

}  // namespace test_helper


namespace tests {

    class EmptyScenario : public ::testing::Test
    {
    protected:
        std::shared_ptr<USimWorld> world = std::make_shared<USimWorld>();
        UPlayerData* player;

        virtual void SetUp()
        {
            UPlayerRegistry& playerRegistry = world->playerRegistry;
            PlayerMap& playerMap = playerRegistry.m_playerMap;

            //Add players
            player = new UPlayerData();

            player->m_playerName = "Thomas";
            player->missionClass = std::make_shared<MissionClass>(player);
            player->locationClass = ELocations::mainHall;
            world->playerRegistry.RegisterPlayer(player);
        }

        virtual void TearDown()
        {
            // UPlayerData memory will be freed by playerRegistry in world.
        }
    };
    
    TEST_F(EmptyScenario, DefaultGoStudyFromCentre) {

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "StudyPrim");
    }

    TEST_F(EmptyScenario, DefaultGoStudyFromPeriphery) {

        player->locationClass = ELocations::circuitTrack;

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 3);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToMainHallPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "StudyPrim");
    }

    TEST_F(EmptyScenario, DefaultPickUpItemFromCentre) {

        world->items.push_back(new Item(EItemType::hammer, ELocations::mainHall));
        Item* hammer_in_hall = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, hammer_in_hall);
    }

    TEST_F(EmptyScenario, DefaultPickUpItemFromPeriphery) {

        player->locationClass = ELocations::gym;
        world->items.push_back(new Item(EItemType::bottle, ELocations::gym));
        Item* bottle_in_gym = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, bottle_in_gym);
    }

    TEST_F(EmptyScenario, DefaultPickupItemButItemsOutOfSightAreIgnored) {

        world->items.push_back(new Item(EItemType::ball, ELocations::library));
        world->items.push_back(new Item(EItemType::bottle, ELocations::gym));
        world->items.push_back(new Item(EItemType::sword, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::pipe, ELocations::bedroom));

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "StudyPrim");
    }

    TEST_F(EmptyScenario, MissionTakeItemToPlaceFromCentre) {

        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::ball, ELocations::mainHall));
        world->items.push_back(new Item(EItemType::extinguisher, ELocations::mainHall));
        Item* extinguisher_in_hall = world->items[1];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 3);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, extinguisher_in_hall);
        ASSERT_EQ(htnPlan[1]->m_name, "GoToCircuitTrackPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "DropItemPrim");
    }

    TEST_F(EmptyScenario, MissionTakeItemToPlaceFromPeriphery) {

        player->locationClass = ELocations::bedroom;
        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::ball, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::extinguisher, ELocations::bedroom));
        Item* extinguisher_in_bedroom = world->items[1];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 4);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, extinguisher_in_bedroom);
        ASSERT_EQ(htnPlan[1]->m_name, "GoToMainHallPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "GoToCircuitTrackPrim");
        ASSERT_EQ(htnPlan[3]->m_name, "DropItemPrim");
    }

    // If the item is already in the correct place, the planner will still attempt to move it to the same place.
    // This behaviour is being kept, as the responsibility for checking mission termination is not part of the planner. To bring it in here would be duplication.
    TEST_F(EmptyScenario, MissionTakeItemToPlaceButAlreadyThere) {

        player->locationClass = ELocations::bedroom;
        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::ball, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::extinguisher, ELocations::bedroom));
        Item* extinguisher_in_bedroom = world->items[1];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, extinguisher_in_bedroom);
        ASSERT_EQ(htnPlan[1]->m_name, "DropItemPrim");
    }

    TEST_F(EmptyScenario, MissionTakeItemToPlaceButItemsOutOfSightAreIgnored) {

        player->locationClass = ELocations::bedroom;
        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::ball, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::extinguisher, ELocations::gym));
        Item* ball_in_bedroom = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, ball_in_bedroom);
    }

    TEST_F(EmptyScenario, MissionTakeItemToPlaceButItemDoesNotExist) {

        player->locationClass = ELocations::bedroom;
        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::ball, ELocations::bedroom));
        Item* ball_in_bedroom = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, ball_in_bedroom);
    }
    
    // If the player is already carrying an item, there is currently no plan to drop it. It will be dropped when the player picks up the new item.
    TEST_F(EmptyScenario, MissionTakeItemToPlaceButAlreadyCarryingAnItem) {

        player->locationClass = ELocations::bedroom;
        player->missionClass = std::make_shared<MissionClass>(MissionClass(EMissions::bringItemToRoom, player, EItemType::extinguisher, ELocations::circuitTrack));
        world->items.push_back(new Item(EItemType::ball, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::extinguisher, ELocations::bedroom));
        world->items.push_back(new Item(EItemType::sword, ELocations::bedroom));
        Item* extinguisher_in_bedroom = world->items[1];
        Item* sword_in_bedroom = world->items[2];

        // Player is carrying the sword.
        player->itemPtr = sword_in_bedroom;
        sword_in_bedroom->m_carryingPlayer = player;

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 4);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, extinguisher_in_bedroom);
        ASSERT_EQ(htnPlan[1]->m_name, "GoToMainHallPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "GoToCircuitTrackPrim");
        ASSERT_EQ(htnPlan[3]->m_name, "DropItemPrim");
    }
    
    class UnderAttackScenario: public EmptyScenario
    {
    protected:
        UPlayerData* defender;
        UPlayerData* attacker;

        virtual void SetUp()
        {
            EmptyScenario::SetUp();
            attacker = new UPlayerData();
            attacker->m_playerName = "Jack";
            attacker->missionClass = std::make_shared<MissionClass>(attacker);
            world->playerRegistry.RegisterPlayer(attacker);
            attacker->locationClass = ELocations::mainHall;

            defender = player;
            defender->relMap[attacker->m_key]->deltaAggro(30);
        }

        virtual void TearDown()
        {
            // UPlayerData memory will be freed by playerRegistry in world.
        }
    };

    TEST_F(UnderAttackScenario, FightWhenAttacked) {

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(defender, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PunchPrim");
        std::shared_ptr<PunchPrim> punchPrim = std::static_pointer_cast<PunchPrim>(htnPlan[0]);
        std::shared_ptr<AttackAction> attackAction = std::static_pointer_cast<AttackAction>(punchPrim->Operate(defender));
        ASSERT_EQ(attackAction->m_targetPlayer, attacker);
    }
    
    TEST_F(UnderAttackScenario, PickUpWeaponAndFightWhenAttacked) {

        world->items.push_back(new Item(EItemType::bat, ELocations::mainHall));
        Item* bat_in_library = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(defender, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, bat_in_library);
        ASSERT_EQ(htnPlan[1]->m_name, "PunchPrim");
        std::shared_ptr<PunchPrim> punchPrim = std::static_pointer_cast<PunchPrim>(htnPlan[1]);
        std::shared_ptr<AttackAction> attackAction = std::static_pointer_cast<AttackAction>(punchPrim->Operate(defender));
        ASSERT_EQ(attackAction->m_targetPlayer, attacker);
    }

    TEST_F(UnderAttackScenario, EvadeWhenAttackedAndLosing) {
        defender->pStats.deltaHealth(-4);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(defender, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "EvadePrim");
        std::shared_ptr<EvadePrim> evadePrim = std::static_pointer_cast<EvadePrim>(htnPlan[0]);
        std::shared_ptr<EvadeAction> evadeAction = std::static_pointer_cast<EvadeAction>(evadePrim->Operate(defender));
        ASSERT_EQ(evadeAction->m_evadePlayer, attacker);
    }

    TEST_F(EmptyScenario, IncreaseIntelligenceMissionWhenInLibrary) {

        player->locationClass = ELocations::library;
        player->missionClass = std::make_shared<MissionClass>(EMissions::increaseIntelligence, player, 1);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "StudyPrim");
    }

    TEST_F(EmptyScenario, IncreaseIntelligenceMissionWhenInCentre) {

        player->locationClass = ELocations::mainHall;
        player->missionClass = std::make_shared<MissionClass>(EMissions::increaseIntelligence, player, 1);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "StudyPrim");
    }

    TEST_F(EmptyScenario, IncreaseIntelligenceMissionWhenInPeriphery) {

        player->locationClass = ELocations::gym;
        player->missionClass = std::make_shared<MissionClass>(EMissions::increaseIntelligence, player, 1);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 3);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToMainHallPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "StudyPrim");
    }
    
}  // tests namespace
