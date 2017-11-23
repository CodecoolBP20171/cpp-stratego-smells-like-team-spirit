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

struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

class Display {
public:
    Display() = default;
    ~Display() = default;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    bool isIsRunning() const;

    void handleEvents();
    void renderBackground();
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

    std::unique_ptr<SDL_Window, sdl_deleter> create_window(char const *title, int x, int y, int w, int h, Uint32 flags);
    std::unique_ptr<SDL_Renderer, sdl_deleter> create_renderer(SDL_Window* window, int index, Uint32 flags);
    std::unique_ptr<SDL_Texture, sdl_deleter> load_texture(const std::string& filename);

private:

    //Click event processing
    ProcessedEvent processEvent(int x, int y);
    int processGameAreaClick(int x, int y);
    int processSideAreaClick(int x, int y);
    std::queue<ProcessedEvent> eventQueue;

    bool isRunning;
    std::unique_ptr<SDL_Renderer, sdl_deleter> renderer;
    std::unique_ptr<SDL_Texture, sdl_deleter> textureAtlas;
    std::unique_ptr<SDL_Window, sdl_deleter> window;

    Assets assets;

};


#endif //STRATEGO_DISPLAY_H
