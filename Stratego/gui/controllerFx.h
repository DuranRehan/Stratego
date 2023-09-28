#ifndef CONTROLLERFX_H
#define CONTROLLERFX_H
#include "facade.h"
#include "viewfx.h"

namespace gui {
    class ControllerFx {
        //Attribut
        model::Facade *game_=nullptr;
        View &view;

    public:
        //construtor
        inline ControllerFx(View & v):view{v} {
            view.setController(*this);
        }
        /**
         * @brief isGameOver
         * @return sends true if the game is over otherwise the opposite
         */
        inline bool isGameOver() {return game_->checkIsOver();}

        // getter from attribut game
        inline model::Facade &game() const {return *game_;}

        /**
         * @brief run start the game
         */
        inline void run() {
            view.show();
            view.initializeUi();
        }

        // setter form attribut game
        inline void setGame(model::Facade &game){
            game_=&game;
            game_->subscribe(&view);
        };
        /**
         * @brief getWinner returns whether there is a winner or not
         * @return true if there is a winner
         */
        inline std::optional<model::ColorPiece> getWinner(){return game_->getWinner();}

        /**
         * @brief getCurrentTurn
         * @return the current player
         */
        inline  model::ColorPiece getCurrentTurn(){return game_->getCurrentPlayer();}

        /**
         * @brief makeAction moves or attacks a pawn
         * @param pos position
         * @param pos2  second position
         */
        void makeAction(model::Position pos,model::Position pos2);

        /**
         * @brief isNextTo checks a pawn is next to another
         * @param pos position
         * @param pos2 second position
         * @return
         */
        bool isNextTo(model::Position pos,model::Position pos2);

    };
}
#endif // CONTROLLERFX_H
