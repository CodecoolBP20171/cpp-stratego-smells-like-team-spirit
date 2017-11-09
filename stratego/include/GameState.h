//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_GAMESTATE_H
#define STRATEGO_GAMESTATE_H


enum class GameState {
    //Init phase states
    BLUE_INIT_START, BLUE_INIT_IN_PROGRESS, RED_INIT_START, RED_INIT_IN_PROGRESS,

    //Game loop states
    BLUE_MOVE_IN_PROGRESS, WAITING_FOR_RED, RED_MOVE_IN_PROGRESS, WAITING_FOR_BLUE,

    //Game over states
    BLUE_WINS, RED_WINS,

    EXIT
};


#endif //STRATEGO_GAMESTATE_H
