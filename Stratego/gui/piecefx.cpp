#include "piecefx.h"
#include <QPainter>
#include <QDebug>
#include <QStyleOption>
using namespace model;
using namespace gui;
PieceFx::PieceFx(std::optional<Piece> piece,model::ColorPiece currentPlayer,Position pos,QWidget *parent):
    QWidget(parent),
    piece{piece},
    currentColorPlayer{currentPlayer},
    position{pos}{
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void PieceFx::paintEvent(QPaintEvent *e) {
    QImage image;
    QBrush brush;
    QPainter painter{this};
    if(piece->getColor() == currentColorPlayer || !piece->isHidden()){
        switch (piece->getRole()) {
        case MARECHAL:
            image.load(":/resources/marechal.png");
            break;
        case GENERAL:
            image.load(":/resources/general.png");
            break;
        case COLONEL:
            image.load(":/resources/colonel.png");
            break;
        case MAJOR:
            image.load(":/resources/major.png");
            break;
        case COMMANDANT:
            image.load(":/resources/commandant.png");
            break;
        case LIEUTENANT:
            image.load(":/resources/lieutenant.png");
            break;
        case SERGENT:
            image.load(":/resources/sergent.png");
            break;
        case DEMINEUR:
            image.load(":/resources/demineur.png");
            break;
        case ECLAIREUR:
            image.load(":/resources/eclaireur.png");
            break;
        case ESPIONNE:
            image.load(":/resources/spy.png");
            break;
        case FLAG:
            image.load(":/resources/flag.png");
            break;
        case BOMBE:
            image.load(":/resources/bombe.png");
            break;
        case WALL:
            image.load(":/resources/water.png");
            break;
        default:
            std::invalid_argument("not supposed to go there");
        }
    }else{
        image.load(":/resources/unknow.png");
    }
    setCorrectBrush(brush);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(QRect(0,0,130,80));
    painter.drawImage(QPoint(10,15),image);
    QStyleOption o;
     o.initFrom(this);
     style()->drawPrimitive(QStyle::PE_Widget, &o, &painter, this);
}
#pragma GCC diagnostic pop

void PieceFx::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        event->accept();

        emit sendValue(position,piece->getColor());

    }
}
void PieceFx::setCorrectBrush(QBrush &brush){
    if(piece->getColor() == RED){
        brush.setColor(Qt::red);
    }else if(piece->getColor() == BLUE){
        brush.setColor(Qt::blue);
    } else if(piece->getRole()=='W'){
        brush.setColor(Qt::darkCyan);
    } else{
        brush.setColor(Qt::gray);
    }
}

PieceFx::~PieceFx(){

}

