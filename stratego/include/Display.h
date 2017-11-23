//
// Created by andras on 2017.11.14..
//

#ifndef STRATEGO_DISPLAY_H
#define STRATEGO_DISPLAY_H


#include <SDL_video.h>
#include <SDL_render.h>
#include <queue>
#include <GameState.h>
#include "Assets.h"
#include "Field.h"
#include "SDL_events.h"
#include "Coordinate.h"
#include "ProcessedEvent.hpp"

class Display {
public:
    Display() = default;
    ~Display() = default;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    bool isIsRunning() const;

    void handleEvents();
    void render();
    void renderPresent();
    void clean();
    void renderField(int x, int y, bool highlighted);
    void renderField(int x, int y, bool highlighted, Color cardColor, CardType faceUpCard, int cardX, int cardY, int cardW);
    void renderField(int x, int y, bool highlighted, Color cardBackColor, int cardX, int cardY, int cardW);
    void renderButton(SDL_Rect destination, UIElement texture);
    void renderMapOverlay(Color color);
    void renderWaitMsg(Color color);
    void renderVictory(GameState victory);
    void renderAvailableMove(int x, int y);
    void delay();
    Uint32 getTicks();
    ProcessedEvent getEventFromQueue();
    bool isEventQueueEmpty();


private:
    //Click event processing
    ProcessedEvent processEvent(int x, int y);
    int processGameAreaClick(int x, int y);
    int processSideAreaClick(int x, int y);
    //SDL_Event event;
    std::queue<ProcessedEvent> eventQueue;

    bool isRunning;
    SDL_Renderer* renderer;
    SDL_Texture* textureAtlas;
    SDL_Window* window;
    Assets assets;

};


#endif //STRATEGO_DISPLAY_H
