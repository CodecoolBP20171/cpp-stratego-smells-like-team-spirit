//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_GAME_H
#define STRATEGO_GAME_H


#include <vector>
#include "Field.h"
#include "Coordinate.h"
#include "GameState.h"
#include "Display.h"

class Game {

public:
    Game() = default;
    ~Game() = default;
    void start();

    //Init
    void populateCardArea();
    void placeCard();

    //Main Game Loop
    void setMove();
    void hideCardsDuringTransition();
    void moveCard();




private:
    Field source;
    Field destination;
    std::unique_ptr<Display> display;
    GameState gameState;
    std::array<std::array<Field, 10>, 10> gameArea; //TODO can be static array? The number of fields should be fixed
    std::array<std::array<Field, 5>, 8> cardArea; //For the cards initially, then during the game discarded cards get here.
};


#endif //STRATEGO_GAME_H
