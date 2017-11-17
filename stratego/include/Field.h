//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_FIELD_H
#define STRATEGO_FIELD_H


#include <bits/unique_ptr.h>
#include "Card.hpp"
#include "Display.h"

class Field {
public:
    Field();
    Field(size_t x, size_t y, bool isTraversable);
    ~Field() = default;

    size_t getX() const;
    size_t getY() const;
    bool getIsTraversable() const;
    bool getIsHighlighted() const;
    const std::unique_ptr<Card> &getContent() const;

    std::unique_ptr<Card> removeCard();
    void placeCard(std::unique_ptr<Card> cardToPlace);
    void highlight();
    void unhighlight();


private:
    size_t x;
    size_t y;
    bool isTraversable;
    bool isHighlighted;
    std::unique_ptr<Card> content;
};


#endif //STRATEGO_FIELD_H
