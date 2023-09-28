#include "controllerFx.h"
using namespace model;
using namespace gui;

void ControllerFx::makeAction(Position pos,Position pos2){
    Direction dir;
    int dirVertical=pos.getX()-pos2.getX();
    int dirHorizontal=pos.getY()-pos2.getY();
    if(dirVertical>0){
        dir=Direction::TOP;
    } else if(dirVertical<0){
        dir=Direction::BOTTOM;
    }else if(dirHorizontal<0){
        dir=Direction::RIGHT;
    } else if(dirHorizontal>=0){
        dir=Direction::LEFT;
    } else {
        throw std::invalid_argument("not supposed to go there");
    }
    int distance;
    if(dir==Direction::TOP || dir== Direction::BOTTOM){
        distance = abs(dirVertical);
    }else if(dir==Direction::LEFT || dir==Direction::RIGHT){
        distance = abs(dirHorizontal);
    }
    if(game_->getPieceAt(pos2).has_value() && isNextTo(pos,pos2)){
        try {
            game_->playAttackRound(pos,pos2);
        }  catch (const std::exception& e) {
            qDebug()<<e.what();
        }
    }else {
        try {
            game_->moveRound(pos,dir,distance);
        }  catch (const std::exception& e) {
            qDebug()<<e.what();
        }
    }
    game_->checkIsOver();
}

bool ControllerFx::isNextTo(Position pos,Position pos2){
    return((pos.getX() ==pos2.getX()-1 ||pos.getX() ==pos2.getX()+1) && pos.getY()==pos2.getY())
            || ((pos.getY() ==pos2.getY()-1 ||pos.getY() ==pos2.getY()+1) && pos.getX() == pos2.getX());
}

