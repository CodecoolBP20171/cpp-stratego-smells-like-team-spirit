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
#include "Button.h"

class Game {
    friend class Display;

public:
    Game();
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

    //Game init
    void initButtons();
    void initGameArea();
    void initCardArea();

    //Rendering
    void renderButtons();
    void renderGameArea();
    void renderCardArea();

    //Input;
    void handleEvents();
    void evaluateInitPhaseClickEvent(ProcessedEvent event);

    void spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color);
    void placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace);

    Button restart;
    Button exit;
    ProcessedEvent source;
    ProcessedEvent destination;
    std::unique_ptr<Display> display;
    GameState gameState;
    std::vector<std::unique_ptr<Field>> gameArea;
    //std::vector<std::vector<std::unique_ptr<Field>>> cardArea;
    std::vector<std::unique_ptr<Field>> cardArea;
};


#endif //STRATEGO_GAME_H
