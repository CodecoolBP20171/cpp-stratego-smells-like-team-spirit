//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDCAPTAIN_H
#define STRATEGO_CARDCAPTAIN_H

#include <Card.hpp>
#include <CardType.h>

class CardCaptain: public Card {

public:
    explicit CardCaptain(Color color) : Card(color) {}

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
    const CardType TYPE = CardType::CAPTAIN;
    static const int NR_TO_SPAWN = 4;
    const std::vector<CardType> defeatables = {
            CardType::FLAG,
            CardType::SPY,
            CardType::SCOUT,
            CardType::MINER,
            CardType::SARGEANT,
            CardType::LIEUTENANT,
            CardType::CAPTAIN
    };

    unsigned char moveDistance = 1;
};
#endif //STRATEGO_CARDCAPTAIN_H
