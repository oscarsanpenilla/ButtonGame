cmake_minimum_required(VERSION 3.10)
project(VTechButtonGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(
  include
)

set(SRC_FILES
  src/buttons_game.cpp
  src/password_generator.cpp
  src/light_contoller.cpp

  include/errors.h
  include/games/impl/buttons_game_impl.h
)

add_executable(VTechButtonGame main.cpp ${SRC_FILES})

##################
# Tests
##################
find_package(GTest)
if (${GTest_FOUND})
  enable_testing()
  add_executable(game_tests tests/test_main.cpp ${SRC_FILES})
  target_include_directories(game_tests PRIVATE include)
  target_link_libraries(game_tests GTest::GTest GTest::Main)
endif ()
