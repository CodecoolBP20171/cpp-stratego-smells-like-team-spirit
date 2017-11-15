//
// Created by andras on 2017.11.14..
//

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <Game.h>
#include "Display.h"

void Display::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialised..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window created..." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created..." << std::endl;
        }

        isRunning = true;
        SDL_Surface* tmpSurface = IMG_Load("assets/texture_atlas.png");
        if(!tmpSurface) {
            std::cout << "couldn't load img " << SDL_GetError() << std::endl;
        }
        background = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

    } else {
        isRunning = false;
    }
}

void Display::handleEvents() {
    SDL_Event event;

    SDL_PollEvent(&event);
    {
        switch (event.type){
            case SDL_QUIT: isRunning = false;
                break;
            default: break;
        }
    }
}

void Display::update() {

}

void Display::render()
{
    SDL_Rect source, destination;
    source.h = 520;
    source.w = 780;
    source.x = 0;
    source.y = 0;

    destination.h = 50;
    destination.w = 50;
    destination.x = 110;
    destination.y = 110;

    SDL_RenderClear(renderer);
    //This is where we could add stuff to render
    SDL_RenderCopy(renderer, background, &source, NULL);
    SDL_RenderCopy(renderer, background, assets.getTexturePosition(CardType::FLAG, Color::RED), &destination);
    for (int i = 0; i <= static_cast<int>(CardType::MARSHALL); ++i) {

        destination.x = 60 + (i*50);
        destination.y = 60;
        SDL_RenderCopy(renderer, background, assets.getTexturePosition(static_cast<CardType>(i), Color::RED), &destination);
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);

        destination.y = 410;
        SDL_RenderCopy(renderer, background, assets.getTexturePosition(static_cast<CardType>(i), Color::BLUE), &destination);
    }

    for (int j = 0; j < Game::gameArea.size(); ++j) {
        for (int i = 0; i < gameArea[j].size(); ++i) {
            destination.x = gameArea[j][i]->getX();
            destination.y = gameArea[j][i]->getY();
            SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
        }
    }

    SDL_RenderPresent(renderer);
}

void Display::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaned up after Display class..." << std::endl;
}

bool Display::running() {
    return isRunning;
}
