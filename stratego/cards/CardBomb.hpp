//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDBOMB_H
#define STRATEGO_CARDBOMB_H

#include <Card.hpp>

class CardBomb: public Card {

public:
    explicit CardBomb(Color color) : Card(color) {}

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
    const CardType TYPE = CardType::BOMB;
    static const int NR_TO_SPAWN = 6;
    const std::vector<CardType> defeatables = {
            CardType::SPY,
            CardType::SCOUT,
            CardType::MINER,
            CardType::SARGEANT,
            CardType::LIEUTENANT,
            CardType::CAPTAIN,
            CardType::MAJOR,
            CardType::COLONEL,
            CardType::GENERAL,
            CardType::MARSHALL
    };

    unsigned char moveDistance = 0;
};
#endif //STRATEGO_CARDBOMB_H
