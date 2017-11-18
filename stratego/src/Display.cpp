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
    ProcessedEvent processedEvent;
    int mouse_x, mouse_y;

    switch (event.type){
        case SDL_QUIT: isRunning = false;
            processedEvent.exitBtn = true;
            eventQueue.push(processedEvent);
            break;
        case SDL_MOUSEBUTTONDOWN: {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            //std::cout << "\nX position of mouse: " << mouse_x << "\nY position of mouse: " << mouse_y << std::endl;
            processedEvent = processEvent(mouse_x, mouse_y);
            eventQueue.push(processedEvent);
        }
        default: break;
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
    //SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::BLUE_CARD_BACK), &destination);
    //for (int i = 0; i <= static_cast<int>(CardType::MARSHALL); ++i) {
    //    destination.x = 60 + (i*50);
    //    destination.y = 60;
    //    SDL_RenderCopy(renderer, background, assets.getTexturePosition(static_cast<CardType>(i), Color::RED), &destination);
    //    SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    //    destination.y = 410;
    //    SDL_RenderCopy(renderer, background, assets.getTexturePosition(static_cast<CardType>(i), Color::BLUE), &destination);
    //}

    //SDL_RenderPresent(renderer);
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

void Display::renderField(int x, int y, bool highlighted) {
    if(highlighted) {
        SDL_Rect destination;
        destination.h = 50;
        destination.w = 50;
        destination.x = x;
        destination.y = y;
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderPresent() {
    SDL_RenderPresent(renderer);
}

void Display::renderField(int x, int y, bool highlighted, Color cardColor, CardType faceUpCard) {

    SDL_Rect destination;
    destination.h = 50;
    destination.w = 50;
    destination.x = x;
    destination.y = y;

    SDL_RenderCopy(renderer, background, assets.getTexturePosition(faceUpCard, cardColor), &destination);
    if(highlighted) {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderField(int x, int y, bool highlighted, Color cardBackColor) {

    SDL_Rect destination;
    destination.h = 50;
    destination.w = 50;
    destination.x = x;
    destination.y = y;

    if(cardBackColor == Color::BLUE) {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::BLUE_CARD_BACK), &destination);
    } else {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::RED_CARD_BACK), &destination);
    }

    if(highlighted) {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }

}

void Display::renderButton(SDL_Rect destination, UIElement texture) {
    SDL_RenderCopy(renderer, background, assets.getUIElement(texture), &destination);
}

ProcessedEvent Display::getEventFromQueue() {
    ProcessedEvent result;
    if(!eventQueue.empty()) {
        result = eventQueue.front();
        eventQueue.pop();
    }
    return result;
}

bool Display::isEventQueueEmpty() {
    return eventQueue.empty();
}

ProcessedEvent Display::processEvent(int x, int y) {
    ProcessedEvent processedEvent;
    //Weed out out of bounds clicks
    if(x<10 || x>770 || y<10 || y > 510) { return processedEvent;}

    if(x>550 && x<630 && y>65 && y<95) {
        processedEvent.exitBtn = true;
    }
    if(x>660 && x<740 && y>65 && y<95) {
        processedEvent.restartBtn = true;
    }
    if(x>10 && x<510 && y>10 && y<510) {
        processedEvent.fieldIndex = processGameAreaClick(x, y);
    }
    if(x>520 && x<770 & y>110 && y<510){
        processedEvent.sideAreaIndex = processSideAreaClick(x, y);
    }
    return processedEvent;
}

int Display::processGameAreaClick(int x, int y) {
    int fieldIndex;
    fieldIndex = (((y-10)/50)*10)+((x-10)/50);
    return fieldIndex;
}

int Display::processSideAreaClick(int x, int y) {
    int sideIndex;
    sideIndex = (((y-110)/50)*5)+((x-520)/50);
    return sideIndex;
}

void Display::renderMapOverlay(Color color) {
    SDL_Rect destination;
    destination.h = 300;
    destination.w = 500;
    destination.x = 10;
    destination.y = 10;
    if(color == Color::BLUE) {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::MAP_OVERLAY_TOP_SHROUDED), &destination);
    } else {
        destination.y = 210;
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::MAP_OVERLAY_BOTTOM_SHROUDED), &destination);
    }
}

void Display::renderWaitMsg(Color color) {
    SDL_Rect destination;
    destination.h = 280;
    destination.w = 250;
    destination.x = 510;
    destination.y = 110;
    if(color == Color::BLUE) {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::MSG_WAIT_FOR_BLUE), &destination);
    } else {
        SDL_RenderCopy(renderer, background, assets.getUIElement(UIElement::MSG_WAIT_FOR_RED), &destination);
    }
}


