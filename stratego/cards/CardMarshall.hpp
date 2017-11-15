//
// Created by andras on 2017.11.15..
//

#ifndef STRATEGO_CARDMARSHALL_H
#define STRATEGO_CARDMARSHALL_H

#include <Card.hpp>
#include <CardType.h>

class CardMarshall: public Card {

public:
    explicit CardMarshall(Color color) : Card(color) {}

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
    const CardType TYPE = CardType::MARSHALL;
    static const int NR_TO_SPAWN = 1;
    const std::vector<CardType> defeatables = {
            CardType::FLAG,
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

    unsigned char moveDistance = 1;
};
#endif //STRATEGO_CARDMARSHALL_H
