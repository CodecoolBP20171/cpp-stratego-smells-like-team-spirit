//
// Created by andras on 2017.11.21..
//

#include "InputParser.h"

void InputParser::evaluateInitPhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                              std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                              ProcessedEvent &destination, Color currentPlayerColor) {

    if(event.getClickedArea() == ClickedArea::GAME_AREA) {
        if(event.isInTerritory(currentPlayerColor)) {
            //initPhaseGameAreaClick(event);
            initPhaseGameAreaClick(event, gameArea, cardArea, source, destination);
        }
    } else if(event.getClickedArea() == ClickedArea::SIDE_AREA) {
        //initPhaseSideAreaClick(event);
        initPhaseSideAreaClick(event, gameArea, cardArea, source, destination);
    }
}

void InputParser::initPhaseGameAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                         std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(!source.isEmpty()) {
        if(gameArea[event.fieldIndex]->getContent() == nullptr) {
            destination = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex != source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex == source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            source.empty();
        } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
            cardArea[source.sideAreaIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        }
    } else {
        if(gameArea[event.fieldIndex]->getContent() != nullptr) {
            source = event;
            gameArea[source.fieldIndex]->highlight();
        }
    }
}

void InputParser::initPhaseSideAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                         std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(cardArea[event.sideAreaIndex]->getContent() != nullptr) {
        if(source.isEmpty()) {
            source = event;
            cardArea[source.sideAreaIndex]->highlight();
        } else {
            if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
               source.sideAreaIndex == event.sideAreaIndex) {
                cardArea[source.sideAreaIndex]->unhighlight();
                source.empty();
            } else if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
                      source.sideAreaIndex != event.sideAreaIndex){
                cardArea[source.sideAreaIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            } else if(source.getClickedArea() == ClickedArea::GAME_AREA) {
                gameArea[source.fieldIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            }
        }
    }
}


