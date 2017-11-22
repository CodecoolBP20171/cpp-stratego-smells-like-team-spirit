//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_GAME_H
#define STRATEGO_GAME_H


#include <vector>
#include <Direction.h>
#include "Field.h"
#include "Coordinate.h"
#include "GameState.h"
#include "Display.h"
#include "Button.h"
#include "InputParser.h"

class Game {
    friend class Display;

public:
    Game();
    ~Game() = default;
    void start();

private:

    //Game init
    void initButtons();
    void initGameArea();
    void initDiscardPile();
    void initCardArea();

    //Main Game Loop
    void populateCardArea();
    void spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color);
    void placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace);
    void initCardPositions();

    void moveCard();
    bool isCardAreaEmpty();
    void checkIfTied();
    void handleInitInProgress();
    void handlePlayerMoveInProgress();
    void handleWaitForNextPlayer();
    void handleVictory();

    //Rendering
    void renderButtons();
    void renderGameArea();
    void renderCardArea();
    void renderDiscardPile();
    void renderAvailableMoves();
    void clearHighlights();
    void changeFacingOfCards(Color color, bool faceDown);
    void revealCombatants();

    //Input
    void handlePlayerClicks();
    void restartGame();
    Color getCurrentPlayerColor();


    //Battle phase input
    bool playerHasValidMoves(Color color);
    std::vector<int> gatherNearbyValidFieldIndeces(unsigned char moveDist, int index, Color color);
    void gatherViableMovesInDir(int index, unsigned char moveDist, Color color, std::vector<int> &result, Direction dir);
    void resolveBattle();
    void triggerVictory(Color color);
    int getNextEmptyDiscardPileIndex();


    std::vector<int> possibleMoves;
    std::unique_ptr<InputParser> input;
    Button restart;
    Button exit;
    ProcessedEvent attacker;
    ProcessedEvent defender;
    ProcessedEvent source;
    ProcessedEvent destination;
    std::unique_ptr<Display> display;
    GameState gameState;
    std::vector<std::unique_ptr<Field>> gameArea;
    std::vector<std::unique_ptr<Field>> cardArea;
    std::vector<std::unique_ptr<Field>> discardPile;

};


#endif //STRATEGO_GAME_H
