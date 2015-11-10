add_definitions(-DSTATICLIB)

file(GLOB_RECURSE Components Components/*)
file(GLOB_RECURSE Entities Entities/*)
file(GLOB_RECURSE EntityComponentSystem EntityComponentSystem/*)
file(GLOB_RECURSE Systems Systems/*)
file(GLOB_RECURSE Utils Utils/*)
file(GLOB_RECURSE Game Game/*)
include_directories(.)

source_group("Components" FILES ${Components})
source_group("Entities" FILES ${Entities})
source_group("EntityComponentSystem" FILES ${EntityComponentSystem})
source_group("Systems" FILES ${Systems})
source_group("Utils" FILES ${Utils})
source_group("Game" FILES ${Game})

add_executable(Game ${Components} ${Entities} ${EntityComponentSystem} ${Systems} ${Game} ${Utils})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Game ${SFML_LIBRARIES})
endif()
add_dependencies(Game version)

set_property(TARGET Game PROPERTY OUTPUT_NAME "game")

