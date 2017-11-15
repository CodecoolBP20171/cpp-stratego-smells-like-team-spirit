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
    //    std::cout << "test card type: " << static_cast<int>(testCard->getType())<<std::endl;
    //}
    //if(testingField.getContent() == nullptr) {
    //    std::cout << "field content is nullptr" << std::endl;
    //}

    display = std::unique_ptr<Display>(new Display());
    display->init("testing window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);
    while(display->running()) {
        display->handleEvents();
        display->update();
        display->render(std::move(gameArea));
    }
    display->clean();
}

void Game::populateCardArea() {
    //TODO Checks gameState to see which player's cards need to be created
    //TODO Loops through all cardTypes and adds the corresponding amount of copies of them to the card area.
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
}

void Game::initGameArea() {
    size_t x, y;
    for (int i = 0; i < 10; ++i) {
        y = 10 + 50 * static_cast<size_t >(i);
        std::vector<std::unique_ptr<Field>> rowOfFields;
        for (int j = 0; j < 10; ++j) {
            x = 10 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
            rowOfFields.emplace_back(std::move(newField));
        }
        gameArea.emplace_back(std::move(rowOfFields));
    }

    //Testing if they exist and if highlight works
    for (int k = 0; k < gameArea.size(); ++k) {
        for (int i = 0; i < gameArea[k].size(); ++i) {
            gameArea[k][i]->highlight();
        }
    }
}



