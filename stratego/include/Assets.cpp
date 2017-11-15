//
// Created by andras on 2017.11.14..
//

#include <iostream>
#include "Assets.h"

Assets::Assets() {

    // Initialising card face images
    for (int i = 0; i <= static_cast<int>(CardType::MARSHALL) ; ++i) {
        CardAsset tempCard;
        tempCard.type = static_cast<CardType>(i);
        tempCard.textureInAtlas.h = 50;
        tempCard.textureInAtlas.w = 50;
        tempCard.textureInAtlas.x = i * 50;
        tempCard.textureInAtlas.y = 520;
        tempCard.color = Color::RED;
        cardAssets.push_back(tempCard);

        tempCard.textureInAtlas.y = 570;
        tempCard.color = Color::BLUE;
        cardAssets.push_back(tempCard);
    }

    SDL_Rect background;
    background.h = 520;
    background.w = 780;
    background.x = 0;
    background.y = 0;
    UIElements[UIElement::BACKGROUND] = background;

    SDL_Rect fieldHighlight;
    fieldHighlight.h = 50;
    fieldHighlight.w = 50;
    fieldHighlight.x = 650;
    fieldHighlight.y = 520;
    UIElements[UIElement::FIELD_HIGHLIGHT] = fieldHighlight;

    SDL_Rect redCardBack;
    redCardBack.h = 50;
    redCardBack.w = 50;
    redCardBack.x = 600;
    redCardBack.y = 520;
    UIElements[UIElement::RED_CARD_BACK] = redCardBack;

    SDL_Rect blueCardBack;
    blueCardBack.h = 50;
    blueCardBack.w = 50;
    blueCardBack.x = 600;
    blueCardBack.y = 570;
    UIElements[UIElement::BLUE_CARD_BACK] = blueCardBack;

}


SDL_Rect *Assets::getTexturePosition(CardType type, Color color) {
    for (int i = 0; i < cardAssets.size() ; ++i) {
        if(cardAssets[i].type == type && cardAssets[i].color == color) {
            return &cardAssets[i].textureInAtlas;
        }
    }
    std::cout << "Could not find specified card texture!" << std::endl;
    return nullptr;
}

SDL_Rect *Assets::getUIElement(UIElement elementName) {
    return &UIElements[elementName];
}
