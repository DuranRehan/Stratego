#ifndef BOARDFX_H
#define BOARDFX_H
#include <QGridLayout>
#include "facade.h"
#include "controllerFx.h"
#include "piecefx.h"
namespace gui{
    class BoardFx : public QGridLayout{
        //attribut
        Q_OBJECT
        ControllerFx *ctrl_=nullptr;
        std::vector<model::Position> clickedPosition;
        std::vector<model::ColorPiece> clickedColor;
    public:
        //constructor
        BoardFx(QWidget * parent = nullptr);

        /**
         * @brief updateBoard BoardFx update the game after each action
         */
        void updateBoard();

        /**
         * @brief setController setter
         * @param controller of the game
         */
        void setController(ControllerFx &controller);
        ~BoardFx();
    private:

        /**
         * @brief clearLayout reset the layout
         */
        void clearLayout();

        /**
         * @brief remove the layout
         * @param layout
         */
        void remove ( QLayout* layout );
    private slots:

        /**
         * @brief onClick clicking on a pawn makes a border appear around the pawn
         * @param color of the pawn
         */
        void onClick(model::Position,model::ColorPiece color);
    };
}

#endif // BOARDFX_H
