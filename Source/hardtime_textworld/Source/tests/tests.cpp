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


namespace tests {
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
            player->aiController = AIController(AI::htnAI);
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);

            player = new UPlayerData();
            player->m_playerName = "Jack";
            player->aiController = AIController(AI::humanAI);
            player->missionClass = std::make_shared<MissionClass>(player);
            world->playerRegistry.RegisterPlayer(player);

            player = new UPlayerData();
            player->m_playerName = "Rupert";
            player->aiController = AIController(AI::htnAI);
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

}  // namespace
