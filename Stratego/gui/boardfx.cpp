#include "boardfx.h"
#include <QObject>
#include "piece.h"
#include <QPainter>
gui::BoardFx::BoardFx(QWidget *parent) : QGridLayout(parent),clickedPosition{},clickedColor{}{
    this->setSpacing(0);
}

void gui::BoardFx::updateBoard(){
    if(this->count()>0){
        clearLayout();
    }
    auto gameBoard = ctrl_->game().getGameBoard();
    for(unsigned i = 0; i < gameBoard.size() ;i++){
        for(unsigned j=0 ; j <gameBoard.at(i).size();j++){
            model::Position pos{(int)i,(int)j};
            auto game = ctrl_->game();
            if(game.getPieceAt(pos).has_value()){
                auto piece = game.getPieceAt(pos);
                if(piece->getRole()!= 'w'){
                    PieceFx *pieceFx = new PieceFx{piece,game.getCurrentPlayer(),pos};
                    connect(pieceFx,SIGNAL(sendValue(model::Position,model::ColorPiece)),this,SLOT(onClick(model::Position,model::ColorPiece)));
                    this->addWidget(pieceFx,i,j);
                }

            } else {
                auto piece = model::Piece{model::NEUTRAL,model::NOTHING,false};
                auto pieceFx = new PieceFx{piece,game.getCurrentPlayer(),pos};
                this->addWidget(pieceFx,i,j);
                connect(pieceFx,SIGNAL(sendValue(model::Position,model::ColorPiece)),this,SLOT(onClick(model::Position,model::ColorPiece)));
            }
        }
    }
}
void gui::BoardFx::onClick(model::Position pos,model::ColorPiece color){
    clickedPosition.push_back(pos);
    clickedColor.push_back(color);
    itemAtPosition(pos.getX(),pos.getY())->widget()->setStyleSheet("border: 2px solid;border-color: rgb(0, 255, 0);");
    if(clickedPosition.size()==2){
        //Clear border color
        for(auto clickPos : clickedPosition){
            itemAtPosition(clickPos.getX(),clickPos.getY())->widget()->setStyleSheet("border:none;");
        }

        if((clickedColor.at(0) == model::NEUTRAL && clickedColor.at(1) == model::NEUTRAL )){
            //Two neutral piece -> clear positions
            clickedPosition.clear();
            clickedColor.clear();
        } else {
            if((clickedColor.at(0) == model::NEUTRAL && clickedColor.at(1) == model::RED)
                    || (clickedColor.at(0) == model::NEUTRAL && clickedColor.at(1) == model::BLUE)){
                ctrl_->makeAction(clickedPosition.at(1),clickedPosition.at(0));
                clickedPosition.clear();
                clickedColor.clear();
            } else {
                ctrl_->makeAction(clickedPosition.at(0),clickedPosition.at(1));
                clickedPosition.clear();
                clickedColor.clear();
            }
        }
    }
}


void gui::BoardFx::setController(ControllerFx &controller){
    ctrl_ = &controller;
}


void gui::BoardFx::clearLayout()
{
    QLayoutItem *child;
    while ((child = this->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

gui::BoardFx::~BoardFx(){
    delete [] ctrl_;
}

