//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDBOMB_H
#define STRATEGO_CARDBOMB_H

#include <Card.hpp>

class CardBomb: public Card {

public:
    explicit CardBomb(Color color) : Card(color) {}

    const CardType getType() const {
        return type;
    }

    unsigned char getMoveDistance() const {
        return moveDistance;
    }

    bool canDefeat(CardType target) override {
        for (auto& defeatable: defatables) {
            if(target == defeatable) {
                return true;
            }
        }
        return false;
    }

private:
    const CardType type = CardType::FLAG;

    const std::vector<CardType> defatables = {
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
