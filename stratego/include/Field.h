//
// Created by apha on 2017.11.07..
//

#ifndef STRATEGO_FIELD_H
#define STRATEGO_FIELD_H


#include <bits/unique_ptr.h>
#include "Card.h"

class Field {
public:

private:
    bool isTraversable;
    bool isHighlighted;
    std::unique_ptr<Card> content;
};


#endif //STRATEGO_FIELD_H
