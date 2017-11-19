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

private:

    //Game init
    void initButtons();
    void initGameArea();
    void initDiscardPile();
    void initCardArea();

    //Main Game Loop
    void populateCardArea();
    void moveCard();
    bool isCardAreaEmpty();
    void checkIfTied();
    void handlePlayerMoveInProgress();
    void handleWaitForNextPlayer();
    void handleInitInProgress();
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

    //Card setup phase input
    void evaluateInitPhaseClickEvent(ProcessedEvent event);
    void initPhaseGameAreaClick(ProcessedEvent event);
    void initPhaseSideAreaClick(ProcessedEvent event);

    //Battle phase input
    void evaluateBattlePhaseClickEvent(ProcessedEvent event);
    bool playerHasValidMoves(Color color);
    std::vector<int> gatherNearbyValidFieldIndeces(unsigned char moveDist, int index);
    void resolveBattle();
    void triggerVictory(Color color);
    int getNextEmptyDiscardPileIndex();

    void spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color);
    void placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace);

    std::vector<int> possibleMoves;
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
