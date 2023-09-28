#ifndef PIECEFX_H
#define PIECEFX_H
#include <QObject>
#include <QWidget>
#include <QGraphicsPolygonItem>
#include "piece.h"
#include "position.h"
#include <QMouseEvent>
namespace gui {
    class PieceFx : public QWidget, public QGraphicsPolygonItem{
        //attribut
        Q_OBJECT
        std::optional<model::Piece> piece;
        model::ColorPiece currentColorPlayer;
        model::Position position;
    public:
        //constructor
        PieceFx(std::optional<model::Piece> piece,model::ColorPiece currentPlayer,model::Position pos,QWidget * parent = nullptr);
        ~PieceFx();
    private:
        /**
         * @brief paintEvent displays all pawns
         * @param e
         */
        void paintEvent(QPaintEvent *e);

        //attribut
        using QGraphicsPolygonItem::mousePressEvent;

        /**
         * @brief mousePressEvent allows to know the position and the color of the piece click
         * @param event
         */
        void mousePressEvent(QMouseEvent *event);

        /**
         * @brief setCorrectBrush put the right colors in the rooms
         * @param brush
         */
        void setCorrectBrush(QBrush &brush);
    protected:

    signals:
        void sendValue(model::Position pos,model::ColorPiece);
   };
}

#endif // PIECEFX_H
