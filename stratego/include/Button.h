//
// Created by andras on 2017.11.16..
//

#ifndef STRATEGO_BUTTON_H
#define STRATEGO_BUTTON_H


#include <SDL_rect.h>
#include <UIElement.h>

class Button {
public:
    bool isPressedDown() const;

    const SDL_Rect &getPosition() const;
    const UIElement &getCurrentTexture() const;

    void setNormalTexture(UIElement normalTexture);
    void setPressedDownTexture(UIElement pressedDownTexture);
    void setPosition(const SDL_Rect &position);

    void setPressedDown(bool pressedDown);

private:
    SDL_Rect position;
    bool pressedDown;
    UIElement normalTexture;
    UIElement pressedDownTexture;
};


#endif //STRATEGO_BUTTON_H
