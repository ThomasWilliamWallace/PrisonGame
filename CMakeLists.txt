# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("HardTime2")

set(ht2tw_folder "${CMAKE_SOURCE_DIR}/Source/hardtime_textworld/Source")
set(ht2tw_public "${ht2tw_folder}/Public")
set(ht2tw_private "${ht2tw_folder}/Private")
set(ht2tw_cmake_test "${ht2tw_folder}/cmake_test")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -D TEXT_ONLY_HTN")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TEXT_ONLY_HTN")
endif()

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
	"${ht2tw_private}/main.cpp"
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

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "${ht2tw_header_files}" "${ht2tw_source_files}")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE ${ht2tw_public} ${ht2tw_private})

# TODO: Add tests and install targets if needed.

# Include sub-projects.
#add_subdirectory ("hardtime_textworld_cmake")
