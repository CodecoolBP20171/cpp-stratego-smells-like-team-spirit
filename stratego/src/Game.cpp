//
// Created by apha on 2017.11.07..
//

#include "Game.h"

void Game::start() {
    //TODO Check the game state and act accordingly
    //TODO If Init phase -> call init()
    //TODO Loop -> while it is the loop phase, keep looping until it changes
    //TODO Game over -> ask if restart?
    //TODO if exit, return to main
}

void Game::init() {
    //TODO Generate cards for player 1 in the side area and wait until all cards are placed on the game area
    //TODO same for player 2 as above
}

void Game::loop() {
    //TODO Start the game loop and loop as long as the game state equals IN_PROGRESS
    //TODO Each loop the current player (which alternates) clicks a card and chooses a destination
    //TODO Is the move valid? -> Handle the chosen move
}

void Game::moveCard(Field from, Field destination) {

}
