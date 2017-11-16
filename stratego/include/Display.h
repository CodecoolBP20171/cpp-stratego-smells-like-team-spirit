//
// Created by andras on 2017.11.14..
//

#ifndef STRATEGO_DISPLAY_H
#define STRATEGO_DISPLAY_H


#include <SDL_video.h>
#include <SDL_render.h>
#include "Assets.h"
#include "Field.h"

class Display {
public:
    Display() = default;
    ~Display() = default;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void renderPresent();
    void clean();
    bool running();
    void renderField(int x, int y, bool highlighted);
    void renderField(int x, int y, bool highlighted, Color cardColor, CardType faceUpCard);
    void renderField(int x, int y, bool highlighted, Color cardBackColor);
    void renderButton(SDL_Rect destination, UIElement texture);
    SDL_Renderer* renderer;
    SDL_Texture* background;

private:
    bool isRunning;
    SDL_Window* window;
    Assets assets;

};


#endif //STRATEGO_DISPLAY_H
