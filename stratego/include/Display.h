//
// Created by andras on 2017.11.14..
//

#ifndef STRATEGO_DISPLAY_H
#define STRATEGO_DISPLAY_H


#include <SDL_video.h>
#include <SDL_render.h>

class Display {
public:
    Display() = default;
    ~Display() = default;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

private:
    bool isRunning;
    SDL_Texture* background;
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif //STRATEGO_DISPLAY_H
