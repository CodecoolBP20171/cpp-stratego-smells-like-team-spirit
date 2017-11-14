//
// Created by andras on 2017.11.14..
//

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
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
            std::cout << "couldn't load img" << SDL_GetError() << std::endl;
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
    SDL_RenderClear(renderer);
    //This is where we could add stuff to render
    SDL_RenderCopy(renderer, background, &source, NULL);
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
