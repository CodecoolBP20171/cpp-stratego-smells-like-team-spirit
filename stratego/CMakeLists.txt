cmake_minimum_required(VERSION 3.8)
project(stratego)

set(CMAKE_CXX_STANDARD 11)

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
        main.cpp)

add_executable(stratego ${SOURCE_FILES})