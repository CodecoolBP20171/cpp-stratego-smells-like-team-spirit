//
// Created by andras on 2017.11.21..
//

#ifndef STRATEGO_INPUTPARSER_H
#define STRATEGO_INPUTPARSER_H


#include <vector>
#include "Field.h"

class InputParser {
public:

    void evaluateInitPhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination, Color currentPlayerColor);

    void initPhaseGameAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination);

    void initPhaseSideAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination);
};


#endif //STRATEGO_INPUTPARSER_H
