//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_CARD_H
#define STRATEGO_CARD_H


#include <map>
#include <vector>
#include "CardType.h"
#include "Color.h"

class Card {

public:
    explicit Card(Color color) : color(color) {}
    virtual bool canDefeat(CardType target) = 0;
    virtual const CardType getType() const = 0;
    virtual unsigned char getMoveDistance() const = 0;

protected:
    Color color;
};


#endif //STRATEGO_CARD_H
