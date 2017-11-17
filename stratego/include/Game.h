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





private:

    //Game init
    void initButtons();
    void initGameArea();
    void initCardArea();

    //Main Game Loop
    void setMove();
    void hideCardsDuringTransition();
    void moveCard();
    bool isCardAreaEmpty();

    //Rendering
    void renderButtons();
    void renderGameArea();
    void renderCardArea();
    void changeFacingOfCards(Color color, bool faceDown);

    //Input
    void handleEvents();
    void restartGame();
    Color getCurrentPlayerColor();

    //Card setup phase input
    void evaluateInitPhaseClickEvent(ProcessedEvent event);
    void initPhaseGameAreaClick(ProcessedEvent event);
    void initPhaseSideAreaClick(ProcessedEvent event);

    //Battle phase input
    void evaluateBattlePhaseClickEvent(ProcessedEvent event);
    bool playerHasValidMoves();
    bool validMovesExistFromField(int fieldIndex);
    std::vector<int> gatherNearbyValidFieldIndeces(unsigned char moveDist, int index);

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
