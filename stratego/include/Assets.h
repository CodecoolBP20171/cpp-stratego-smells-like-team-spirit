//
// Created by andras on 2017.11.14..
//

#ifndef STRATEGO_ASSETS_H
#define STRATEGO_ASSETS_H


#include <SDL_rect.h>
#include <vector>
#include <map>
#include <UIElement.h>
#include "CardType.h"
#include "Color.h"

class Assets {

public:
    Assets();

    SDL_Rect* getTexturePosition(CardType type, Color color);
    SDL_Rect* getUIElement(UIElement elementName);
private:

struct CardAsset{
    CardType type;
    Color color;
    SDL_Rect textureInAtlas;
};

    CardAsset blueB;
    CardAsset redFlag;
    std::vector<CardAsset> cardAssets;
    std::map<UIElement, SDL_Rect> UIElements;
};


#endif //STRATEGO_ASSETS_H
