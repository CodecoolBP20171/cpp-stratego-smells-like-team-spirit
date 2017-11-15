//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDSPY_H
#define STRATEGO_CARDSPY_H

#include <Card.hpp>
#include <CardType.h>

class CardSpy: public Card {

public:
    explicit CardSpy(Color color) : Card(color) {}

    const CardType getType() const override {
        return TYPE;
    }

    unsigned char getMoveDistance() const override {
        return moveDistance;
    }

    bool canDefeat(CardType target) override {
        for (auto& defeatable: defeatables) {
            if(target == defeatable) {
                return true;
            }
        }
        return false;
    }

    static const int getNR_TO_SPAWN() {
        return NR_TO_SPAWN;
    }

private:
    const CardType TYPE = CardType::SPY;
    static const int NR_TO_SPAWN = 1;
    const std::vector<CardType> defeatables = {
            CardType::FLAG,
            CardType::SPY,
            CardType::MARSHALL
    };

    unsigned char moveDistance = 1;
};

#endif //STRATEGO_CARDSPY_H
