//
// Created by andras on 2017.11.16..
//

#ifndef STRATEGO_PROCESSEDEVENT_H
#define STRATEGO_PROCESSEDEVENT_H


#include <Color.h>

struct ProcessedEvent {
    bool restartBtn = false;
    bool exitBtn = false;
    int fieldIndex = -1;
    int sideAreaIndex = -1;

    bool isEmpty() {
        return (!restartBtn && !exitBtn && fieldIndex == -1 && sideAreaIndex == -1);
    }

    bool isInBlueTerritory() {
        return fieldIndex <= 39;
    }

    bool isInRedTerritory() {
        return fieldIndex >= 60;
    }

    bool isInTerritory(Color color) {
        if(fieldIndex == -1) return false;

        if(color == Color::RED) {
            return fieldIndex <= 39;
        } else {
            return fieldIndex >= 60;
        }
    }

    void empty() {
        restartBtn = false;
        exitBtn = false;
        fieldIndex = -1;
        sideAreaIndex = -1;
    }
};


#endif //STRATEGO_PROCESSEDEVENT_H
