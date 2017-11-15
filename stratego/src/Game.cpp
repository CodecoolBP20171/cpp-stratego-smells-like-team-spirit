//
// Created by apha on 2017.11.07..
//

#include "Game.h"
#include "../cards/CardBomb.hpp"

void Game::start() {
    //TODO contains main loop, starts with clearing screen, checking gameState and variables and rendering screen accordingly.

    //Testing card
    std::unique_ptr<Card> testCard = std::unique_ptr<CardBomb>(new CardBomb(Color::BLUE));
    //std::cout << "card trying to defeat flag: " << testCard->canDefeat(CardType::FLAG);
    //std::cout << "card trying to defeat marshall: " << testCard->canDefeat(CardType::MARSHALL);

    //Testing field, adding, removing content etc.
    Field testingField(10, 10, true);
    //if(testingField.getContent() == nullptr) {
    //    std::cout << "Field content is nullptr" << std::endl;
    //}
    //testingField.placeCard(std::move(testCard));
    //if(testingField.getContent() == nullptr) {
    //    std::cout << "Field content is nullptr" << std::endl;
    //} else {
    //    if(testCard == nullptr) {
    //        std::cout << "test card became nullptr" << std::endl;
    //    }
    //    std::cout << "Field content: " << static_cast<int>(testingField.getContent()->getType()) << std::endl;
    //}
    //std::cout << "\nremoving from Field back to testCard" << std::endl;
    //testCard = testingField.removeCard();
    //if(testCard == nullptr) {
    //    std::cout << "test card is nullptr" << std::endl;
    //} else {
    //    std::cout << "test card TYPE: " << static_cast<int>(testCard->getType())<<std::endl;
    //}
    //if(testingField.getContent() == nullptr) {
    //    std::cout << "field content is nullptr" << std::endl;
    //}

    display = std::unique_ptr<Display>(new Display());
    display->init("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);
    while(display->running()) {
        display->handleEvents();
        display->update();
        display->render();
        renderGameArea();
        renderCardArea();
        if(gameState == GameState::BLUE_INIT_START) {
            populateCardArea();
        }
        display->renderPresent();
    }
    display->clean();
}

void Game::populateCardArea() {
    //TODO Checks gameState to see which player's cards need to be created
    //TODO Loops through all cardTypes and adds the corresponding amount of copies of them to the card area.
    for (int i = 0; i < 10; ++i) {
        std::unique_ptr<Card> testCard = std::unique_ptr<CardBomb>(new CardBomb(Color::BLUE));
        testCard->setIsFaceDown(true);
        for (int j = 0; j < cardArea.size() ; ++j) {
            if(cardArea[j]->getContent() == nullptr) {
                cardArea[j]->placeCard(std::move(testCard));
            }
        }
    }
    gameState = GameState::BLUE_INIT_IN_PROGRESS;
}

void Game::placeCard() {
    //TODO Used in the init phase. Highlights field, chooses Destination and performs the placement of card from card area to game area.
}

void Game::setMove() {
    //TODO Used to set the source and the destination for a move.
}

void Game::moveCard() {
    //TODO Used for performing the move from the source field to the destination field
}

void Game::hideCardsDuringTransition() {
    //TODO checks if the destination contains a card. If yes, then that means the move was an attack so show attacker and defender but face everything else down.
    //TODO If destination was empty, then face down all cards.
}

Game::Game() {
    gameState = GameState::BLUE_INIT_START;
    initGameArea();
    initCardArea();
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
    //Setting all fields to highlighted for testing
    for (int k = 0; k < gameArea.size(); k++) {
            gameArea[k]->highlight();
        }
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
    for (int k = 0; k < cardArea.size(); k+=3) {
            cardArea[k]->highlight();
    }
}

void Game::renderGameArea() {
    for (int i = 0; i < gameArea.size(); ++i) {
        int fieldX = gameArea[i]->getX();
        int fieldY = gameArea[i]->getY();
        bool highlighted = gameArea[i]->getIsHighlighted();
        if(gameArea[i]->getContent() == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            if(!gameArea[i]->getContent()->getIsFaceDown()){
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



