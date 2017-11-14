cmake_minimum_required(VERSION 3.8)
project(stratego)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(src include assets ${SDL2_INCLUDE_DIRS})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

set(SOURCE_FILES
        include/Card.h
        include/CardType.h
        include/Coordinate.h
        include/Field.h
        include/Game.h
        include/GameState.h
        src/Card.cpp
        src/CardType.cpp
        src/Coordinate.cpp
        src/Field.cpp
        src/Game.cpp
        src/GameState.cpp
        main.cpp src/Display.cpp include/Display.h)

add_executable(stratego ${SOURCE_FILES})

target_link_libraries(stratego ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})