//
// Created by apha on 2017.11.07..
//

#include "Game.h"

void Game::start() {
    //TODO contains main loop, starts with clearing screen, checking gameState and variables and rendering screen accordingly.
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



