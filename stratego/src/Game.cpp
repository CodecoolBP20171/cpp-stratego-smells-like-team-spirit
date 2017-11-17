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

void Game::start() {
    //TODO contains main loop, starts with clearing screen, checking gameState and variables and rendering screen accordingly.

    //Testing card
    //std::unique_ptr<Card> testCard = std::unique_ptr<CardBomb>(new CardBomb(Color::BLUE));
    //std::cout << "card trying to defeat flag: " << testCard->canDefeat(CardType::FLAG);
    //std::cout << "card trying to defeat marshall: " << testCard->canDefeat(CardType::MARSHALL);

    //Testing field, adding, removing content etc.
    //std::unique_ptr<Field> testField = std::unique_ptr<Field>(new Field(10, 10, true));
    //if(testField->getContent() == nullptr) {
    //    std::cout << "Field content is nullptr" << std::endl;
    //}
    //testField->placeCard(std::move(testCard));
    //if(testField->getContent() == nullptr) {
    //    std::cout << "Field content is nullptr" << std::endl;
    //} else {
    //    if(testCard == nullptr) {
    //        std::cout << "test card became nullptr" << std::endl;
    //    }
    //    std::cout << "Field content: " << static_cast<int>(testField->getContent()->getType()) << std::endl;
    //}
    //std::cout << "\nremoving from Field back to testCard" << std::endl;
    //testCard = testField->removeCard();
    //if(testCard == nullptr) {
    //    std::cout << "test card is nullptr" << std::endl;
    //} else {
    //    std::cout << "test card TYPE: " << static_cast<int>(testCard->getType())<<std::endl;
    //}
    //if(testField->getContent() == nullptr) {
    //    std::cout << "field content is nullptr" << std::endl;
    //}

    display = std::unique_ptr<Display>(new Display());
    display->init("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);

    while(gameState != GameState::EXIT) {
        display->handleEvents();
        display->update();
        display->render();
        if(gameState == GameState::BLUE_INIT_IN_PROGRESS) display->renderMapOverlay(Color::BLUE);
        if(gameState == GameState::RED_INIT_IN_PROGRESS) display->renderMapOverlay(Color::RED);
        handleEvents();
        renderButtons();
        renderGameArea();
        renderCardArea();
        if(gameState == GameState::BLUE_INIT_START ||
                gameState == GameState::RED_INIT_START) {
            populateCardArea();
        } else if(gameState == GameState::BLUE_INIT_IN_PROGRESS &&
                isCardAreaEmpty()) {
            changeFacingOfCards(Color::BLUE, true);
            gameState = GameState::RED_INIT_START;
        } else if(gameState == GameState::RED_INIT_IN_PROGRESS &&
                isCardAreaEmpty()) {
            changeFacingOfCards(Color::RED, true);
            changeFacingOfCards(Color::BLUE, false);
            gameState = GameState::BLUE_MOVE_IN_PROGRESS;
            std::cout << "Blue move in progress...\n";
        } else if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
            if(!playerHasValidMoves()) gameState = GameState::WAITING_FOR_RED;
        } else if(gameState == GameState::WAITING_FOR_RED) {
            std::cout << "waiting for red";
        }
        if(!source.isEmpty() && !destination.isEmpty()){
            std::cout << "trying to move card" << std::endl;
            moveCard();
        }
        display->renderPresent();
    }
    display->clean();
}

void Game::populateCardArea() {
    //TODO Checks gameState to see which player's cards need to be created
    //TODO Loops through all cardTypes and adds the corresponding amount of copies of them to the card area.
    //for (int i = 0; i < 10; ++i) {
    //    std::unique_ptr<Card> testCard = std::unique_ptr<CardBomb>(new CardBomb(Color::BLUE));
    //    testCard->setIsFaceDown(true);
    //    for (int j = 0; j < cardArea.size() ; ++j) {
    //        if(cardArea[j]->getContent() == nullptr) {
    //            cardArea[j]->placeCard(std::move(testCard));
    //        }
    //    }
    //}
    for (int j = 0; j < cardArea.size() ; ++j) {
        cardArea[j]->removeCard();
    }

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

void Game::placeCard() {
    //TODO Used in the init phase. Highlights field, chooses Destination and performs the placement of card from card area to game area.
}

void Game::setMove() {
    //TODO Used to set the source and the destination for a move.
}

void Game::moveCard() {

    std::unique_ptr<Card> tempCard;
    if(source.getClickedArea() == ClickedArea::GAME_AREA) {
        tempCard = gameArea[source.fieldIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        gameArea[source.fieldIndex]->unhighlight();
        source.empty();
        destination.empty();

    } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
        tempCard = cardArea[source.sideAreaIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        cardArea[source.sideAreaIndex]->unhighlight();
        source.empty();
        destination.empty();

    }
}

void Game::hideCardsDuringTransition() {
    //TODO checks if the destination contains a card. If yes, then that means the move was an attack so show attacker and defender but face everything else down.
    //TODO If destination was empty, then face down all cards.
}

Game::Game() {
    gameState = GameState::BLUE_INIT_START;
    initGameArea();
    initCardArea();
    initButtons();
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

void Game::handleEvents() {
    if(!display->isEventQueueEmpty()) {
        ProcessedEvent event = display->getEventFromQueue();
        //std::cout << "field index: " << event.fieldIndex << std::endl;
        //std::cout << "side index: " << event.sideAreaIndex << std::endl;
        //std::cout << "restart: " << event.restartBtn << std::endl;
        //std::cout << "exit:" << event.exitBtn << std::endl;
        if(event.exitBtn) {gameState = GameState::EXIT;}
        if(event.restartBtn) {restartGame();}
        if(gameState == GameState::RED_INIT_IN_PROGRESS ||
            gameState == GameState::BLUE_INIT_IN_PROGRESS){
            evaluateInitPhaseClickEvent(event);
        }
        if(gameState == GameState::BLUE_MOVE_IN_PROGRESS ||
                gameState == GameState::RED_MOVE_IN_PROGRESS) {
            evaluateBattlePhaseClickEvent(event);
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
    //TODO Check if player has valid moves to make

}

bool Game::playerHasValidMoves() {
    Color currentPlayerColor;
    currentPlayerColor = getCurrentPlayerColor();
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

bool Game::validMovesExistFromField(int fieldIndex) {
    unsigned char moveDistance = gameArea[fieldIndex]->getContent()->getMoveDistance();
    if(moveDistance == 0) return false;
    if(moveDistance == 1) {
        //Check 1 above if possible
        if((fieldIndex - 10) >= 0) {
            if(gameArea[fieldIndex-10] == nullptr) return true;
        }
        //Check 1 below if possible
        if((fieldIndex + 10) <= 99) {
            if(gameArea[fieldIndex+10] == nullptr) return true;
        }
    }
    return false;
}

std::vector<int> Game::gatherNearbyValidFieldIndeces(unsigned char moveDist, int index) {
    //TODO Refactor this mess! :(
    std::vector<int> result;
    std::cout << "index: " << index << std::endl;
    Color currentPlayerColor = getCurrentPlayerColor();
    double gameAreaDiameter= 10;
    double rightEdge = ((ceil(index/gameAreaDiameter))*gameAreaDiameter)-1;
    std::cout << "right edge: " << rightEdge << std::endl;
    double leftEdge = ((floor(index/gameAreaDiameter))*gameAreaDiameter);
    std::cout << "left edge: " << leftEdge << std::endl;

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
    std::cout << "Valid move indeces for " << index << " ";
    for (int k = 0; k < result.size(); ++k) {
        std::cout << result[k] << " ";
    }
    std::cout << std::endl;

    return result;
}



