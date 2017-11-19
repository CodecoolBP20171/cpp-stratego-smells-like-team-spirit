//
// Created by apha on 2017.11.07..
//

#include <SDL_events.h>
#include "Game.h"
#include "../cards/CardBomb.hpp"
#include "../cards/CardFlag.hpp"
#include "../cards/CardSpy.hpp"
#include "../cards/CardScout.hpp"
#include "../cards/CardMiner.hpp"
#include "../cards/CardSargeant.hpp"
#include "../cards/CardLieutentant.hpp"
#include "../cards/CardCaptain.hpp"
#include "../cards/CardMajor.hpp"
#include "../cards/CardColonel.hpp"
#include "../cards/CardGeneral.hpp"
#include "../cards/CardMarshall.hpp"
#include <algorithm>

void Game::start() {

    display = std::unique_ptr<Display>(new Display());
    display->init("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);

    while(gameState != GameState::EXIT) {
        display->handleEvents();
        display->render();
        renderButtons();
        renderGameArea();

        if(gameState == GameState::BLUE_INIT_START ||
           gameState == GameState::RED_INIT_START) {
            populateCardArea();
        } else if(gameState == GameState::BLUE_INIT_IN_PROGRESS ||
                gameState == GameState::RED_INIT_IN_PROGRESS) {
            handleInitInProgress();
        } else if(gameState == GameState::RED_MOVE_IN_PROGRESS ||
           gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
            handlePlayerMoveInProgress();
        } else if(gameState == GameState::WAITING_FOR_BLUE ||
                gameState == GameState::WAITING_FOR_RED) {
            handleWaitForNextPlayer();
        } else if(gameState == GameState::RED_WINS ||
                gameState == GameState::BLUE_WINS ||
                gameState == GameState::TIED) {
            handleVictory();
        }

        handlePlayerClicks();
        if(!source.isEmpty() && !destination.isEmpty()){
            moveCard();
        }
        display->renderPresent();
    }
    display->clean();
}

void Game::populateCardArea() {
    //for (int i = 0; i <= static_cast<int>(CardType::MARSHALL) ; ++i) {
    for (int i = 0; i <= static_cast<int>(CardType::SCOUT) ; ++i) {
        auto currentTypeToSpawn = static_cast<CardType >(i);
        int amountToSpawn;
        Color colorToSpawnWith;
        if(gameState == GameState::BLUE_INIT_START) {
            colorToSpawnWith = Color::BLUE;
        } else {
            colorToSpawnWith = Color::RED;
        }

        switch (currentTypeToSpawn) {
            case CardType::FLAG: {
                amountToSpawn = CardFlag::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::FLAG, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::BOMB: {
                amountToSpawn = CardBomb::getNR_TO_SPAWN();
                amountToSpawn = 1;
                spawnNrOfTypesOfCards(CardType::BOMB, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SPY: {
                amountToSpawn = CardSpy::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::SPY, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SCOUT: {
                amountToSpawn = CardScout::getNR_TO_SPAWN();
                amountToSpawn = 1;
                spawnNrOfTypesOfCards(CardType::SCOUT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MINER: {
                amountToSpawn = CardMiner::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MINER, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SARGEANT: {
                amountToSpawn = CardSargeant::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::SARGEANT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::LIEUTENANT: {
                amountToSpawn = CardLieutenant::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::LIEUTENANT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::CAPTAIN: {
                amountToSpawn = CardCaptain::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::CAPTAIN, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MAJOR: {
                amountToSpawn = CardMajor::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MAJOR, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::COLONEL: {
                amountToSpawn = CardColonel::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::COLONEL, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::GENERAL: {
                amountToSpawn = CardGeneral::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::GENERAL, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MARSHALL: {
                amountToSpawn = CardMarshall::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MARSHALL, amountToSpawn, colorToSpawnWith);
                break;
            }
        }

    }

    if(gameState == GameState::BLUE_INIT_START) {
        gameState = GameState::BLUE_INIT_IN_PROGRESS;
    } else {
        gameState = GameState::RED_INIT_IN_PROGRESS;
    }
}

void Game::moveCard() {

    std::unique_ptr<Card> tempCard;
    if(source.getClickedArea() == ClickedArea::GAME_AREA) {
        tempCard = gameArea[source.fieldIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        gameArea[source.fieldIndex]->unhighlight();

    } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
        tempCard = cardArea[source.sideAreaIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        cardArea[source.sideAreaIndex]->unhighlight();
    }

    if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        gameState = GameState::WAITING_FOR_RED;
        gameArea[source.fieldIndex]->highlight();
        gameArea[destination.fieldIndex]->highlight();
    }

    if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
        gameState = GameState::WAITING_FOR_BLUE;
        gameArea[source.fieldIndex]->highlight();
        gameArea[destination.fieldIndex]->highlight();
    }

    source.empty();
    destination.empty();

}

Game::Game() {
    gameState = GameState::BLUE_INIT_START;
    initGameArea();
    initCardArea();
    initButtons();
    initDiscardPile();
}

void Game::initGameArea() {
    size_t x, y;
    for (int i = 0; i < 10; ++i) {
        y = 10 + 50 * static_cast<size_t >(i);
        for (int j = 0; j < 10; ++j) {
            x = 10 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
            gameArea.emplace_back(std::move(newField));
        }
    }
    gameArea[42]->setIsTraversable(false);
    gameArea[43]->setIsTraversable(false);
    gameArea[52]->setIsTraversable(false);
    gameArea[53]->setIsTraversable(false);

    gameArea[46]->setIsTraversable(false);
    gameArea[47]->setIsTraversable(false);
    gameArea[56]->setIsTraversable(false);
    gameArea[57]->setIsTraversable(false);
    //Setting all fields to highlighted for testing
    //for (int k = 0; k < gameArea.size(); k++) {
    //        gameArea[k]->highlight();
    //    }
}


void Game::initCardArea() {
    size_t x, y;
    for (int i = 0; i < 8; ++i) {
        y = 110 + 50 * static_cast<size_t >(i);
        for (int j = 0; j < 5; ++j) {
            x = 520 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
            cardArea.emplace_back(std::move(newField));
        }
    }

    //Testing if they exist and if highlight works
    //for (int k = 0; k < cardArea.size(); k+=3) {
    //        cardArea[k]->highlight();
    //}
}

void Game::renderGameArea() {
    for (int i = 0; i < gameArea.size(); ++i) {
        int fieldX = gameArea[i]->getX();
        int fieldY = gameArea[i]->getY();
        bool highlighted = gameArea[i]->getIsHighlighted();
        if(gameArea[i]->getContent() == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            if(gameArea[i]->getContent()->getIsFaceDown()){
                Color color = gameArea[i]->getContent()->getColor();
                display->renderField(fieldX, fieldY, highlighted, color);
            } else {
                Color color = gameArea[i]->getContent()->getColor();
                CardType type = gameArea[i]->getContent()->getType();
                display->renderField(fieldX, fieldY, highlighted, color, type);
            }
        }
    }
}

void Game::renderCardArea() {
    for (int i = 0; i < cardArea.size(); ++i) {
        int fieldX = cardArea[i]->getX();
        int fieldY = cardArea[i]->getY();
        bool highlighted = cardArea[i]->getIsHighlighted();
        if(cardArea[i]->getContent() == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            Color color = cardArea[i]->getContent()->getColor();
            CardType type = cardArea[i]->getContent()->getType();
            display->renderField(fieldX, fieldY, highlighted, color, type);
        }
    }
}

void Game::renderButtons() {
    display->renderButton(restart.getPosition(), restart.getCurrentTexture());
    display->renderButton(exit.getPosition(), exit.getCurrentTexture());
}

void Game::initButtons() {

    SDL_Rect btnPos;
    btnPos.h = 30;
    btnPos.w = 80;
    btnPos.x = 550;
    btnPos.y = 65;
    restart.setPosition(btnPos);
    restart.setNormalTexture(UIElement::RESTART_BTN);
    restart.setPressedDownTexture(UIElement::RESTART_BTN_PRESSED);
    restart.setPressedDown(false);

    btnPos.x = 660;
    exit.setPosition(btnPos);
    exit.setNormalTexture(UIElement::EXIT_BTN);
    exit.setPressedDownTexture(UIElement::EXIT_BTN_PRESSED);
    exit.setPressedDown(false);
}

void Game::spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color) {
    std::unique_ptr<Card> tempCard;
    for (int i = 0; i < amountToSpawn; ++i) {
        switch (typeToSpawn){
            case CardType::FLAG: {
                tempCard = std::unique_ptr<CardFlag>(new CardFlag(color));
                break;
            }
            case CardType::BOMB: {
                tempCard = std::unique_ptr<CardBomb>(new CardBomb(color));
                break;
            }
            case CardType::SPY: {
                tempCard = std::unique_ptr<CardSpy>(new CardSpy(color));
                break;
            }
            case CardType::SCOUT: {
                tempCard = std::unique_ptr<CardScout>(new CardScout(color));
                break;
            }
            case CardType::MINER: {
                tempCard = std::unique_ptr<CardMiner>(new CardMiner(color));
                break;
            }
            case CardType::SARGEANT: {
                tempCard = std::unique_ptr<CardSargeant>(new CardSargeant(color));
                break;
            }
            case CardType::LIEUTENANT: {
                tempCard = std::unique_ptr<CardLieutenant>(new CardLieutenant(color));
                break;
            }
            case CardType::CAPTAIN: {
                tempCard = std::unique_ptr<CardCaptain>(new CardCaptain(color));
                break;
            }
            case CardType::MAJOR: {
                tempCard = std::unique_ptr<CardMajor>(new CardMajor(color));
                break;
            }
            case CardType::COLONEL: {
                tempCard = std::unique_ptr<CardColonel>(new CardColonel(color));
                break;
            }
            case CardType::GENERAL: {
                tempCard = std::unique_ptr<CardGeneral>(new CardGeneral(color));
                break;
            }
            case CardType::MARSHALL: {
                tempCard = std::unique_ptr<CardMarshall>(new CardMarshall(color));
                break;
            }
        }
        placeToNextEmptyFieldInSideArea(std::move(tempCard));
    }
}

void Game::placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace) {
    for (int j = 0; j < cardArea.size() ; ++j) {
        if(cardArea[j]->getContent() == nullptr) {
            cardArea[j]->placeCard(std::move(cardToPlace));
        }
    }
}

void Game::handlePlayerClicks() {
    if(!display->isEventQueueEmpty()) {
        ProcessedEvent event = display->getEventFromQueue();
        std::cout << "field index: " << event.fieldIndex << std::endl;
        std::cout << "side index: " << event.sideAreaIndex << std::endl;
        std::cout << "restart: " << event.restartBtn << std::endl;
        std::cout << "exit:" << event.exitBtn << std::endl;
        if(event.exitBtn) {gameState = GameState::EXIT;}
        if(event.restartBtn) {restartGame();}

        if(gameState == GameState::RED_INIT_IN_PROGRESS ||
            gameState == GameState::BLUE_INIT_IN_PROGRESS){
            evaluateInitPhaseClickEvent(event);
        } else if(gameState == GameState::BLUE_MOVE_IN_PROGRESS ||
                gameState == GameState::RED_MOVE_IN_PROGRESS) {
            if(event.getClickedArea() == ClickedArea::GAME_AREA) {
                evaluateBattlePhaseClickEvent(event);
            }
        } else if(gameState == GameState::WAITING_FOR_BLUE && event.getClickedArea() == ClickedArea::GAME_AREA) {
            clearHighlights();
            gameState = GameState::BLUE_MOVE_IN_PROGRESS;
        } else if(gameState == GameState::WAITING_FOR_RED && event.getClickedArea() == ClickedArea::GAME_AREA) {
            clearHighlights();
            gameState = GameState::RED_MOVE_IN_PROGRESS;
        }

    }
}

void Game::evaluateInitPhaseClickEvent(ProcessedEvent event) {

    Color currentPlayerColor;
    currentPlayerColor = getCurrentPlayerColor();

    if(event.getClickedArea() == ClickedArea::GAME_AREA) {
        if(event.isInTerritory(currentPlayerColor)) {
            initPhaseGameAreaClick(event);
        }
    } else if(event.getClickedArea() == ClickedArea::SIDE_AREA) {
        initPhaseSideAreaClick(event);
    }
}

void Game::initPhaseGameAreaClick(ProcessedEvent event) {
    if(!source.isEmpty()) {
        if(gameArea[event.fieldIndex]->getContent() == nullptr) {
            destination = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                event.fieldIndex != source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                event.fieldIndex == source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            source.empty();
        } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
            cardArea[source.sideAreaIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        }
    } else {
        if(gameArea[event.fieldIndex]->getContent() != nullptr) {
            source = event;
            gameArea[source.fieldIndex]->highlight();
        }
    }
}

void Game::initPhaseSideAreaClick(ProcessedEvent event) {
    if(cardArea[event.sideAreaIndex]->getContent() != nullptr) {
        if(source.isEmpty()) {
            source = event;
            cardArea[source.sideAreaIndex]->highlight();
        } else {
            if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
                    source.sideAreaIndex == event.sideAreaIndex) {
                cardArea[source.sideAreaIndex]->unhighlight();
                source.empty();
            } else if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
                    source.sideAreaIndex != event.sideAreaIndex){
                cardArea[source.sideAreaIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            } else if(source.getClickedArea() == ClickedArea::GAME_AREA) {
                gameArea[source.fieldIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            }
        }
    }
}

void Game::restartGame() {
    for (int i = 0; i < gameArea.size(); ++i) {
        gameArea[i]->removeCard();
    }
    for (int j = 0; j < cardArea.size(); ++j) {
        cardArea[j]->removeCard();
    }
    gameState = GameState::BLUE_INIT_START;
}

bool Game::isCardAreaEmpty() {
    for (int i = 0; i < cardArea.size(); ++i) {
        if(cardArea[i]->getContent() != nullptr) {
            return false;
        }
    }
    return true;
}

void Game::changeFacingOfCards(Color color, bool faceDown){
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getContent() != nullptr) {
            if(gameArea[i]->getContent()->getColor() == color) {
                gameArea[i]->getContent()->setIsFaceDown(faceDown);
            }
        }
    }
}

Color Game::getCurrentPlayerColor() {
    if(gameState == GameState::BLUE_INIT_IN_PROGRESS ||
       gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        return Color::BLUE;
    }
    return Color::RED;
}

void Game::evaluateBattlePhaseClickEvent(ProcessedEvent event) {
    Color currentPlayerColor = getCurrentPlayerColor();
    unsigned char moveDist;

    //if(!source.isEmpty()) {
    //    moveDist = gameArea[source.fieldIndex]->getContent()->getMoveDistance();
    //    possibleMoves = gatherNearbyValidFieldIndeces(moveDist, source.fieldIndex);
    //}

    if(gameArea[event.fieldIndex]->getContent() == nullptr) {
        if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
            destination = event;
            gameArea[source.fieldIndex]->unhighlight();
        }
    } else {
        if(source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() == currentPlayerColor) {
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() == currentPlayerColor) {
            gameArea[source.fieldIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() != currentPlayerColor) {
            if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
                defender = event;
                attacker = source;
                std::cout << "attacker: " << attacker.fieldIndex << std::endl;
                std::cout << "defender: " << defender.fieldIndex << std::endl;
                if(currentPlayerColor == Color::BLUE) {
                    gameState = GameState::WAITING_FOR_RED;
                    std::cout << "setting gamestate to: " << static_cast<int>(gameState) << std::endl;
                } else if(currentPlayerColor == Color::RED) {
                    gameState = GameState::WAITING_FOR_BLUE;
                }
                source.empty();
                destination.empty();
            }
        }
    }
}

bool Game::playerHasValidMoves(Color currentPlayerColor) {
    unsigned char moveDist;
    std::vector<int> validMoveIndeces;
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getContent() != nullptr) {
            if(gameArea[i]->getContent()->getColor() == currentPlayerColor) {
                moveDist = gameArea[i]->getContent()->getMoveDistance();
                validMoveIndeces = gatherNearbyValidFieldIndeces(moveDist, i);
                if(!validMoveIndeces.empty()) return true;
            }
        }
    }
    return false;
}

std::vector<int> Game::gatherNearbyValidFieldIndeces(unsigned char moveDist, int index) {
    //TODO Refactor this mess! :(
    std::vector<int> result;
    //std::cout << "index: " << index << std::endl;
    Color currentPlayerColor = getCurrentPlayerColor();
    int gameAreaDiameter = 10;
    int rightEdge = ((index / gameAreaDiameter)*gameAreaDiameter) + gameAreaDiameter -1;
    //std::cout << "right edge: " << rightEdge << std::endl;
    int leftEdge = ((index / gameAreaDiameter)*gameAreaDiameter);
    //std::cout << "left edge: " << leftEdge << std::endl;

    //Collect all available indeces above, break loop if edge/obstacle or after finding enemy
    for (int i = 1; i <= moveDist; ++i) {
        if ((index - (i * gameAreaDiameter)) >= 0) {
            if (gameArea[index - (i * gameAreaDiameter)]->getContent() == nullptr) {
                if( gameArea[index - (i * gameAreaDiameter)]->getIsTraversable()) {
                    result.emplace_back(index - (i * gameAreaDiameter));
                } else {
                    break;
                }
            } else if (gameArea[index - (i * gameAreaDiameter)]->getContent()->getColor() != currentPlayerColor) {
                result.emplace_back(index - (i * gameAreaDiameter));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    //Collect all available indeces below, break loop if edge/obstacle or after finding enemy
    for (int i = 1; i <= moveDist; ++i) {
        if ((index + (i * gameAreaDiameter)) <= 99) {
            if (gameArea[index + (i * gameAreaDiameter)]->getContent() == nullptr) {
                if(gameArea[index + (i * gameAreaDiameter)]->getIsTraversable()) {
                    result.emplace_back(index + (i * gameAreaDiameter));
                } else {
                    break;
                }
            } else if (gameArea[index + (i * gameAreaDiameter)]->getContent()->getColor() != currentPlayerColor) {
                result.emplace_back(index + (i * gameAreaDiameter));
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    //Collect all available indeces to the right, break loop if edge/obstacle or after finding enemy
    for (int j = 1; j <= moveDist; ++j) {
        if (index + j <= rightEdge) {
            if(gameArea[index + j]->getContent() == nullptr){
                if( gameArea[index + j]->getIsTraversable()) {
                    result.emplace_back(index + j);
                } else {
                    break;
                }
            } else if(gameArea[index + j]->getContent()->getColor() != currentPlayerColor) {
                result.emplace_back(index + j);
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    //Collect all available indeces to the left, break loop if edge/obstacle or after finding enemy
    for (int j = 1; j <= moveDist; ++j) {
        if (index - j >= leftEdge) {
            if(gameArea[index - j]->getContent() == nullptr){
                if( gameArea[index - j]->getIsTraversable()) {
                    result.emplace_back(index - j);
                } else {
                    break;
                }
            } else if(gameArea[index - j]->getContent()->getColor() != currentPlayerColor) {
                result.emplace_back(index - j);
                break;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    //DEBUG
    //std::cout << "Valid move indeces for " << index << " ";
    //for (int k = 0; k < result.size(); ++k) {
    //    std::cout << result[k] << " ";
    //}
    //std::cout << std::endl;

    return result;
}

void Game::clearHighlights() {
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getIsHighlighted()) {
            gameArea[i]->unhighlight();
        }
    }
}

void Game::revealCombatants() {
    if(attacker.fieldIndex != -1 && defender.fieldIndex != -1) {
        gameArea[attacker.fieldIndex]->getContent()->setIsFaceDown(false);
        gameArea[defender.fieldIndex]->getContent()->setIsFaceDown(false);
    }
}

void Game::resolveBattle() {
    if(attacker.isEmpty() || defender.isEmpty()) return;
    std::unique_ptr<Card> tempCard;
    if(gameArea[attacker.fieldIndex]->getContent()->getType() ==
            gameArea[defender.fieldIndex]->getContent()->getType()) {

        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

        tempCard = gameArea[defender.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

    } else if (gameArea[attacker.fieldIndex]->getContent()->canDefeat(gameArea[defender.fieldIndex]->getContent()->getType())) {
        if(gameArea[defender.fieldIndex]->getContent()->getType() == CardType::FLAG) {
            Color winnerColor = gameArea[attacker.fieldIndex]->getContent()->getColor();
            triggerVictory(winnerColor);
        }

        tempCard = gameArea[defender.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        gameArea[defender.fieldIndex]->placeCard(std::move(tempCard));
    } else {
        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
    }
    attacker.empty();
    defender.empty();
}

void Game::triggerVictory(Color winner) {
    if(winner == Color::RED) {
        gameState = GameState::RED_WINS;
    } else if(winner == Color::BLUE) {
        gameState = GameState::BLUE_WINS;
    }
}

void Game::initDiscardPile() {
    size_t x, y;
    for (int i = 0; i < 16; ++i) {
        y = 110 + 25 * static_cast<size_t >(i);
        for (int j = 0; j < 5; ++j) {
            x = 520 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
            discardPile.emplace_back(std::move(newField));
        }
    }
}

void Game::renderDiscardPile() {
    int fieldX, fieldY;
    CardType typeToRender;
    Color cardColor;
    for (int i = 0; i < discardPile.size(); ++i) {
        fieldX = discardPile[i]->getX();
        fieldY = discardPile[i]->getY();
        if(discardPile[i]->getContent() != nullptr) {
            typeToRender = discardPile[i]->getContent()->getType();
            cardColor = discardPile[i]->getContent()->getColor();
            display->renderField(fieldX, fieldY, false, cardColor, typeToRender);
        }
    }
}

int Game::getNextEmptyDiscardPileIndex() {
    for (int i = 0; i < discardPile.size(); ++i) {
        if(discardPile[i]->getContent() == nullptr) {
            return i;
        }
    }
}

void Game::renderAvailableMoves() {
    int x, y;
    if(!possibleMoves.empty()) {
        for (int i = 0; i < possibleMoves.size(); ++i) {
            x = gameArea[possibleMoves[i]]->getX();
            y = gameArea[possibleMoves[i]]->getY();
            display->renderAvailableMove(x, y);
        }
    }
}

void Game::checkIfTied() {
    if(!playerHasValidMoves(Color::RED) &&
            !playerHasValidMoves(Color::BLUE)) {
        gameState = GameState::TIED;
    }
}

void Game::handlePlayerMoveInProgress() {

    renderDiscardPile();
    checkIfTied();
    if(!possibleMoves.empty()) renderAvailableMoves();
    if(!source.isEmpty()) {
        unsigned char moveDist;
        moveDist = gameArea[source.fieldIndex]->getContent()->getMoveDistance();
        possibleMoves = gatherNearbyValidFieldIndeces(moveDist, source.fieldIndex);
    }

    if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        if(!playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAITING_FOR_RED;
        changeFacingOfCards(Color::BLUE, false);
        resolveBattle();

    } else if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
        if(!playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAITING_FOR_BLUE;
        changeFacingOfCards(Color::RED, false);
        resolveBattle();
    }
}

void Game::handleWaitForNextPlayer() {

    if(gameState == GameState::WAITING_FOR_BLUE) {
        changeFacingOfCards(Color::RED, true);
        changeFacingOfCards(Color::BLUE, true);
        renderDiscardPile();
        revealCombatants();
        display->renderWaitMsg(Color::BLUE);

    } else if(gameState == GameState::WAITING_FOR_RED) {
        changeFacingOfCards(Color::RED, true);
        changeFacingOfCards(Color::BLUE, true);
        renderDiscardPile();
        revealCombatants();
        display->renderWaitMsg(Color::RED);
    }
    possibleMoves.clear();
}

void Game::handleInitInProgress() {
    if(gameState == GameState::BLUE_INIT_IN_PROGRESS) {
        display->renderMapOverlay(Color::BLUE);
        renderCardArea();
    }

    if(gameState == GameState::RED_INIT_IN_PROGRESS) {
        display->renderMapOverlay(Color::RED);
        renderCardArea();
    }

    if(gameState == GameState::BLUE_INIT_IN_PROGRESS &&
              isCardAreaEmpty()) {
        changeFacingOfCards(Color::BLUE, true);
        gameState = GameState::RED_INIT_START;

    } else if(gameState == GameState::RED_INIT_IN_PROGRESS &&
              isCardAreaEmpty()) {
        changeFacingOfCards(Color::RED, true);
        changeFacingOfCards(Color::BLUE, false);
        gameState = GameState::WAITING_FOR_BLUE;

    }
}

void Game::handleVictory() {
    if(gameState == GameState::BLUE_WINS) {
        display->renderVictory(GameState::BLUE_WINS);
    } else if(gameState == GameState::RED_WINS) {
        display->renderVictory(GameState::RED_WINS);
    } else if(gameState == GameState::TIED) {
        display->renderVictory(GameState::TIED);
    }
}



