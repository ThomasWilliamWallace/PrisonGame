# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("hardtime_textworld")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)

# Compiler flags
add_compile_definitions(TEXT_ONLY_HTN)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0 -Wall")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++17")
endif()

# GTest
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set path variables
set(ht2tw_folder "${CMAKE_SOURCE_DIR}")
set(ht2tw_public "${ht2tw_folder}/Public")
set(ht2tw_private "${ht2tw_folder}/Private")
set(ht2tw_tests "${ht2tw_folder}/tests")

get_filename_component(parent_dir ${CMAKE_SOURCE_DIR}/.. ABSOLUTE)
set(htn_planner_folder "${parent_dir}/htn_planner")
set(htn_planner_public "${htn_planner_folder}/Public")
set(htn_planner_private "${htn_planner_folder}/Private")

# Header and source variables
set(ht2tw_header_files
	"${ht2tw_public}/Actions.h"
	"${ht2tw_public}/BasicAI.h"
	"${ht2tw_public}/HTNDomain.h"
	"${ht2tw_public}/HTNPrimitives.h"
	"${ht2tw_public}/Item.h"
	"${ht2tw_public}/Missions.h"
	"${ht2tw_public}/Names.h"
	"${ht2tw_public}/PlayerData.h"
	"${ht2tw_public}/PlayerRegistry.h"
	"${ht2tw_public}/Relationship.h"
	"${ht2tw_public}/RequestHTNDomain.h"
	"${ht2tw_public}/SimWorld.h"
	"${ht2tw_public}/TranslateToHTNWorldState.h"
	)
set(htn_planner_header_files
	"${htn_planner_public}/AbstractAction.h"
	"${htn_planner_public}/AbstractItem.h"
	"${htn_planner_public}/Constants.h"
	"${htn_planner_public}/EActions.h"
	"${htn_planner_public}/EItemType.h"
	"${htn_planner_public}/ELocations.h"
	"${htn_planner_public}/EMissions.h"
	"${htn_planner_public}/HTNPlanner.h"
	"${htn_planner_public}/HTNWorldState.h"
	"${htn_planner_public}/Locations.h"
	"${htn_planner_public}/PlatformSpecific.h"
	"${htn_planner_public}/pLog.h"
	"${htn_planner_public}/PStats.h"
	)
set(ht2tw_source_files
	"${ht2tw_private}/Actions.cpp"
	"${ht2tw_private}/BasicAI.cpp"
	"${ht2tw_private}/HTNDomain.cpp"
	"${ht2tw_private}/HTNPrimitives.cpp"
	"${ht2tw_private}/Item.cpp"
	"${ht2tw_private}/Missions.cpp"
	"${ht2tw_private}/Names.cpp"
	"${ht2tw_private}/PlayerData.cpp"
	"${ht2tw_private}/PlayerRegistry.cpp"
	"${ht2tw_private}/Relationship.cpp"
	"${ht2tw_private}/RequestHTNDomain.cpp"
	"${ht2tw_private}/SimWorld.cpp"
	"${ht2tw_private}/TranslateToHTNWorldState.cpp"
)
set(htn_planner_source_files
	"${htn_planner_private}/AbstractAction.cpp"
	"${htn_planner_private}/AbstractItem.cpp"
	"${htn_planner_private}/Constants.cpp"
	"${htn_planner_private}/HTNPlanner.cpp"
	"${htn_planner_private}/HTNWorldState.cpp"
	"${htn_planner_private}/Locations.cpp"
	"${htn_planner_private}/PlatformSpecific.cpp"
	"${htn_planner_private}/pLog.cpp"
	"${htn_planner_private}/PStats.cpp"
)

# Main executable
add_executable (${PROJECT_NAME} "${ht2tw_private}/main.cpp" "${htn_planner_header_files}" "${htn_planner_source_files}" "${ht2tw_header_files}" "${ht2tw_source_files}")
target_include_directories(${PROJECT_NAME} PRIVATE ${htn_planner_public} ${htn_planner_private} ${ht2tw_public} ${ht2tw_private})

# Unit tests
add_executable (tests "${ht2tw_tests}/tests.cpp" "${htn_planner_header_files}" "${htn_planner_source_files}" "${ht2tw_header_files}" "${ht2tw_source_files}")

target_include_directories(tests PRIVATE ${htn_planner_public} ${htn_planner_private} ${ht2tw_public} ${ht2tw_private})
target_link_libraries(tests gtest_main)
add_test(NAME example_test COMMAND tests)
