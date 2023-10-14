cmake_minimum_required(VERSION 3.10)
project(VTechButtonGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(
  include
)

add_executable(VTechButtonGame main.cpp src/buttons_game.cpp include/errors.h)

##################
# Tests
##################
find_package(GTest REQUIRED)
enable_testing()
add_executable(game_tests tests/main.cpp src/buttons_game.cpp include/errors.h)
target_include_directories(game_tests PRIVATE include)
target_link_libraries(game_tests GTest::GTest GTest::Main)
