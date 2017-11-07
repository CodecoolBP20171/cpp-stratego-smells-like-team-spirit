//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_GAME_H
#define STRATEGO_GAME_H


#include <vector>
#include "Field.h"
#include "Coordinate.h"
#include "GameState.h"

class Game {

public:
    Game();
    ~Game() = default;
    void start();
    void init();
    void loop();
    void moveCard(Field from, Field destination);
    void resolveAttack(Card attacker, Card defender);




private:
    GameState state;
    std::vector<std::vector<Field>> gameArea; //TODO can be static array? The number of fields should be fixed
    std::vector<std::vector<Field>> cardArea; //For the cards initially, then during the game discarded cards get here.
};


#endif //STRATEGO_GAME_H
