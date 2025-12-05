add_library(dungeon_lib
    npc.cpp
    battle.cpp
    factory.cpp
    observer.cpp
    dungeon.cpp
)

target_include_directories(dungeon_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(dungeon_editor main.cpp)
target_link_libraries(dungeon_editor PRIVATE dungeon_lib)