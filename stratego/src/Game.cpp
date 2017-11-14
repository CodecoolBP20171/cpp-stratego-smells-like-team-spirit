//
// Created by apha on 2017.11.07..
//

#include "Game.h"

void Game::start() {
    //TODO contains main loop, starts with clearing screen, checking gameState and variables and rendering screen accordingly.
    gameState = GameState::BLUE_INIT_START;
    display = std::unique_ptr<Display>(new Display());
    display->init("testing window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);
    while(display->running()) {
        display->handleEvents();
        display->update();
        display->render();
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



