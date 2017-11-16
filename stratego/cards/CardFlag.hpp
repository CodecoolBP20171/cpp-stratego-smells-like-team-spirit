//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDFLAG_H
#define STRATEGO_CARDFLAG_H

#include <Card.hpp>
#include <CardType.h>

class CardFlag: public Card {

public:
    explicit CardFlag(Color color) : Card(color) {}

    const CardType getType() const override {
        return TYPE;
    }

    unsigned char getMoveDistance() const override {
        return moveDistance;
    }

    bool canDefeat(CardType target) override {
        return false;
    }

    static const int getNR_TO_SPAWN() {
        return NR_TO_SPAWN;
    }

private:
    const CardType TYPE = CardType::FLAG;
    static const int NR_TO_SPAWN = 1;
    unsigned char moveDistance = 0;
};

#endif //STRATEGO_CARDFLAG_H
