# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("hardtime_textworld")

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
set(ht2tw_folder "${CMAKE_SOURCE_DIR}/Source/hardtime_textworld/Source")
set(ht2tw_public "${ht2tw_folder}/Public")
set(ht2tw_private "${ht2tw_folder}/Private")
set(ht2tw_tests "${ht2tw_folder}/tests")

# Header and source variables
set(ht2tw_header_files
	"${ht2tw_public}/AbstractAction.h"
	"${ht2tw_public}/AbstractItem.h"
	"${ht2tw_public}/Actions.h"
	"${ht2tw_public}/BasicAI.h"
	"${ht2tw_public}/Constants.h"
	"${ht2tw_public}/EActions.h"
	"${ht2tw_public}/EItemType.h"
	"${ht2tw_public}/ELocations.h"
	"${ht2tw_public}/EMissions.h"
	"${ht2tw_public}/HTNDomain.h"
	"${ht2tw_public}/HTNPlanner.h"
	"${ht2tw_public}/HTNPrimitives.h"
	"${ht2tw_public}/HTNWorldState.h"
	"${ht2tw_public}/Item.h"
	"${ht2tw_public}/Locations.h"
	"${ht2tw_public}/Missions.h"
	"${ht2tw_public}/Names.h"
	"${ht2tw_public}/PlatformSpecific.h"
	"${ht2tw_public}/PlayerData.h"
	"${ht2tw_public}/PlayerRegistry.h"
	"${ht2tw_public}/pLog.h"
	"${ht2tw_public}/PStats.h"
	"${ht2tw_public}/Relationship.h"
	"${ht2tw_public}/RequestHTNDomain.h"
	"${ht2tw_public}/SimWorld.h"
	"${ht2tw_public}/TranslateToHTNWorldState.h"
	)
set(ht2tw_source_files
	"${ht2tw_private}/AbstractAction.cpp"
	"${ht2tw_private}/AbstractItem.cpp"
	"${ht2tw_private}/HTNDomain.cpp"
	"${ht2tw_private}/HTNPlanner.cpp"
	"${ht2tw_private}/HTNPrimitives.cpp"
	"${ht2tw_private}/HTNWorldState.cpp"
	"${ht2tw_private}/Item.cpp"
	"${ht2tw_private}/BasicAI.cpp"
	"${ht2tw_private}/Constants.cpp"
	"${ht2tw_private}/Relationship.cpp"
	"${ht2tw_private}/Names.cpp"
	"${ht2tw_private}/TranslateToHTNWorldState.cpp"
	"${ht2tw_private}/Actions.cpp"
	"${ht2tw_private}/Missions.cpp"
	"${ht2tw_private}/Locations.cpp"
	"${ht2tw_private}/pLog.cpp"
	"${ht2tw_private}/SimWorld.cpp"
	"${ht2tw_private}/RequestHTNDomain.cpp"
	"${ht2tw_private}/PStats.cpp"
	"${ht2tw_private}/PlayerRegistry.cpp"
	"${ht2tw_private}/PlayerData.cpp"
	"${ht2tw_private}/PlatformSpecific.cpp"
)

# Main executable
add_executable (${PROJECT_NAME} "${ht2tw_private}/main.cpp" "${ht2tw_header_files}" "${ht2tw_source_files}")
target_include_directories(${PROJECT_NAME} PRIVATE ${ht2tw_public} ${ht2tw_private})

# Unit tests
add_executable (tests "${ht2tw_tests}/tests.cpp" "${ht2tw_header_files}" "${ht2tw_source_files}")
#add_executable(tests
#	"${ht2tw_tests}/tests.cpp"
#	"${ht2tw_public}/HTNWorldState.h"
#	"${ht2tw_public}/HTNPlanner.h"
#	"${ht2tw_public}/HTNDomain.h"
#	"${ht2tw_public}/Locations.h"
#	"${ht2tw_public}/SimWorld.h"
#	"${ht2tw_public}/EItemType.h"
#	"${ht2tw_public}/pLog.h"
#	"${ht2tw_public}/PlayerData.h"
#)
target_include_directories(tests PRIVATE ${ht2tw_public} ${ht2tw_private})
target_link_libraries(tests gtest_main)
add_test(NAME example_test COMMAND tests)
