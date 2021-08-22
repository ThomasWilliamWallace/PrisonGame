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
    /*
    class InitialWorldState : public ::testing::Test
    {
    protected:
        std::shared_ptr<USimWorld> world = std::make_shared<USimWorld>();

        virtual void SetUp()
        {
            world->items.push_back(new Item(EItemType::extinguisher, ELocations::mainHall));
            world->items.push_back(new Item(EItemType::bottle, ELocations::mainHall));
            world->items.push_back(new Item(EItemType::hammer, ELocations::circuitTrack));
            world->items.push_back(new Item(EItemType::ball, ELocations::mainHall));
            world->items.push_back(new Item(EItemType::mirror, ELocations::bedroom));
            world->items.push_back(new Item(EItemType::rock, ELocations::library));

            UPlayerRegistry& playerRegistry = world->playerRegistry;
            PlayerMap& playerMap = playerRegistry.m_playerMap;

            //Add players
            UPlayerData* player;

            player = new UPlayerData();

            player->m_playerName = "Thomas";
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);

            player = new UPlayerData();
            player->m_playerName = "Jack";
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);

            player = new UPlayerData();
            player->m_playerName = "Rupert";
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);
        }

        virtual void TearDown()
        {
        }
    };
    
    TEST_F(InitialWorldState, TakeBallToGym) {
        UPlayerData* player_rupert = world->playerRegistry.m_playerMap[0];
        Item* ball_in_hall = world->items[3];

        //update worldstate from real world
        HTNWorldState htnWorldState = TranslateToHTNWorldState(player_rupert, *world, world->playerRegistry.m_playerMap, nullptr);

        //make new plan
        HTNCompound* missionPtr = new PrisonerBehaviourCompound();
        HTNPrimitiveList htnPlan = HTNIterative(htnWorldState, *missionPtr, 0);

        // Check resulting plan
        EXPECT_EQ(size(htnPlan), 3);
        EXPECT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        HTNPrimitivePtr action_1 = htnPlan[0];
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(action_1);
        EXPECT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, ball_in_hall);
        EXPECT_EQ(htnPlan[1]->m_name, "GoToGymPrim");
        EXPECT_EQ(htnPlan[2]->m_name, "DropItemPrim");
    }

    // TODO adapt test to either carry out plan, or limit name to single plan step.
    TEST_F(InitialWorldState, TakeBallToGymWhenBallIsFound) {
        UPlayerData* player_rupert = world->playerRegistry.m_playerMap[0];
        // Remove ball from world. Instead put it in library.
        world->items.erase(world->items.begin() + 3);
        world->items.push_back(new Item(EItemType::ball, ELocations::library));
        Item* extinguisher_in_hall = world->items[0];
        Item* ball_in_library = world->items[5];

        //update worldstate from real world
        HTNWorldState htnWorldState = TranslateToHTNWorldState(player_rupert, *world, world->playerRegistry.m_playerMap, nullptr);

        //make new plan
        HTNCompound* missionPtr = new PrisonerBehaviourCompound();
        HTNPrimitiveList htnPlan = HTNIterative(htnWorldState, *missionPtr, 0);

        // Check resulting plan
        EXPECT_EQ(size(htnPlan), 1);
        EXPECT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        HTNPrimitivePtr action_1 = htnPlan[0];
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(action_1);
        EXPECT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, extinguisher_in_hall);
    }
    */
    class EmptyWorld : public ::testing::Test
    {
    protected:
        std::shared_ptr<USimWorld> world = std::make_shared<USimWorld>();

        virtual void SetUp()
        {
            UPlayerRegistry& playerRegistry = world->playerRegistry;
            PlayerMap& playerMap = playerRegistry.m_playerMap;

            //Add players
            UPlayerData* player;

            player = new UPlayerData();

            player->m_playerName = "Thomas";
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);
        }

        virtual void TearDown()
        {
        }
    };

    TEST_F(EmptyWorld, DefaultGoStudyFromCentre) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "StudyPrim");
    }

    TEST_F(EmptyWorld, DefaultGoStudyFromPeriphery) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
        player->locationClass = ELocations::circuitTrack;

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 3);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToMainHallPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[2]->m_name, "StudyPrim");
    }

    TEST_F(EmptyWorld, DefaultPickUpItemFromCentre) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
        world->items.push_back(new Item(EItemType::hammer, ELocations::mainHall));
        Item* hammer_in_hall = world->items[0];

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PickUpItemByPtrPrim");
        std::shared_ptr<PickUpItemByPtrPrim> pickUpItemByPtrPrim = std::static_pointer_cast<PickUpItemByPtrPrim>(htnPlan[0]);
        ASSERT_EQ(pickUpItemByPtrPrim->m_itemFocus->m_realItem, hammer_in_hall);
    }

    TEST_F(EmptyWorld, DefaultPickUpItemFromPeriphery) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
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

    TEST_F(EmptyWorld, ItemsOutOfSightAreIgnored) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
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

    TEST_F(EmptyWorld, MissionTakeItemToPlaceFromCentre) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
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

    TEST_F(EmptyWorld, MissionTakeItemToPlaceFromPeriphery) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
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

    TEST_F(EmptyWorld, FightWhenAttacked) {
        UPlayerData* attacker = new UPlayerData();
        attacker->m_playerName = "Jack";
        attacker->missionClass = std::make_shared<MissionClass>(attacker);
        world->playerRegistry.RegisterPlayer(attacker);
        attacker->locationClass = ELocations::library;

        UPlayerData* defender = world->playerRegistry.m_playerMap[0];
        defender->locationClass = ELocations::library;
        defender->relMap[1]->deltaAggro(30);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(defender, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "PunchPrim");
        std::shared_ptr<PunchPrim> punchPrim = std::static_pointer_cast<PunchPrim>(htnPlan[0]);
        std::shared_ptr<AttackAction> attackAction = std::static_pointer_cast<AttackAction>(punchPrim->Operate(defender));
        ASSERT_EQ(attackAction->m_targetPlayer, attacker);
    }

    TEST_F(EmptyWorld, PickUpWeaponAndFightWhenAttacked) {
        UPlayerData* attacker = new UPlayerData();
        attacker->m_playerName = "Jack";
        attacker->missionClass = std::make_shared<MissionClass>(attacker);
        world->playerRegistry.RegisterPlayer(attacker);
        attacker->locationClass = ELocations::library;

        world->items.push_back(new Item(EItemType::bat, ELocations::library));
        Item* bat_in_library = world->items[0];

        UPlayerData* defender = world->playerRegistry.m_playerMap[0];
        defender->locationClass = ELocations::library;
        defender->relMap[1]->deltaAggro(30);

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

    TEST_F(EmptyWorld, EvadeWhenAttackedAndLosing) {
        UPlayerData* attacker = new UPlayerData();
        attacker->m_playerName = "Jack";
        attacker->missionClass = std::make_shared<MissionClass>(attacker);
        world->playerRegistry.RegisterPlayer(attacker);
        attacker->locationClass = ELocations::library;

        UPlayerData* defender = world->playerRegistry.m_playerMap[0];
        defender->locationClass = ELocations::library;
        defender->pStats.deltaHealth(-4);
        defender->relMap[1]->deltaAggro(30);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(defender, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "EvadePrim");
        std::shared_ptr<EvadePrim> evadePrim = std::static_pointer_cast<EvadePrim>(htnPlan[0]);
        std::shared_ptr<EvadeAction> evadeAction = std::static_pointer_cast<EvadeAction>(evadePrim->Operate(defender));
        ASSERT_EQ(evadeAction->m_evadePlayer, attacker);
    }

    TEST_F(EmptyWorld, IncreaseIntelligenceMissionWhenInLibrary) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
        player->locationClass = ELocations::library;
        player->missionClass = std::make_shared<MissionClass>(EMissions::increaseIntelligence, player, 1);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 1);
        ASSERT_EQ(htnPlan[0]->m_name, "StudyPrim");
    }

    TEST_F(EmptyWorld, IncreaseIntelligenceMissionWhenInCentre) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
        player->locationClass = ELocations::mainHall;
        player->missionClass = std::make_shared<MissionClass>(EMissions::increaseIntelligence, player, 1);

        HTNPrimitiveList htnPlan = test_helper::plan_from_world(player, *world);

        // Check resulting plan
        ASSERT_EQ(size(htnPlan), 2);
        ASSERT_EQ(htnPlan[0]->m_name, "GoToLibraryPrim");
        ASSERT_EQ(htnPlan[1]->m_name, "StudyPrim");
    }

    TEST_F(EmptyWorld, IncreaseIntelligenceMissionWhenInPeriphery) {
        UPlayerData* player = world->playerRegistry.m_playerMap[0];
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
