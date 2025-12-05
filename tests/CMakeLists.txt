find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_run test_dungeon.cpp)
target_link_libraries(tests_run PRIVATE dungeon_lib GTest::GTest GTest::Main)
add_test(NAME dungeon_tests COMMAND tests_run)
