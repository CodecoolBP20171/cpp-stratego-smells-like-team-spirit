//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_CARD_H
#define STRATEGO_CARD_H


#include <map>
#include <vector>
#include <cmath>
#include "CardType.h"
#include "Color.h"

class Card {

public:
    explicit Card(Color color) : color(color) {}
    virtual bool canDefeat(CardType target) = 0;
    virtual const CardType getType() const = 0;
    virtual unsigned char getMoveDistance() const = 0;

    bool getIsFaceDown() const {
        return isFaceDown;
    }

    void setIsFaceDown(bool isFaceDown) {
        Card::isFaceDown = isFaceDown;
    }

    Color getColor() const {
        return color;
    }

    int getCurrentX() const {
        return currentX;
    }

    void setCurrentX(int currentX) {
        Card::currentX = currentX;
    }

    int getCurrentY() const {
        return currentY;
    }

    void setCurrentY(int currentY) {
        Card::currentY = currentY;
    }

    int getNextXPos(int destinationX) {
        double step;
        if(currentX < destinationX) {
            step = destinationX - currentX;
            currentX += std::ceil(step / 30);
        } else if(currentX > destinationX) {
            step = currentX - destinationX;
            currentX -= std::ceil(step / 30);
        }
        return currentX;
    }

    int getNextYPos(int destinationY) {
        double step;
        if(currentY < destinationY) {
            step = destinationY - currentY;
            currentY += std::ceil(step / 30);
        } else if(currentY > destinationY) {
            step = currentY - destinationY;
            currentY -= std::ceil(step / 30);
        }
        return currentY;
    }
protected:
    int currentX;
    int currentY;
    bool isFaceDown = false;
    Color color;
};


#endif //STRATEGO_CARD_H
