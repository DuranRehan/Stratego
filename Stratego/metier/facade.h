#ifndef FACADE_H
#define FACADE_H
#include "board.h"
#include "observable.h"
namespace model {

/**
 * @brief Facade class represent the facade of the Model and Gather the necessary elements for the game
 *
 */
class Facade : public utils::observable::Observable{
    model::Board board;
    ColorPiece currentPlayer;
    bool debugMode;
public:
    /**
     * @brief Initialize a default model
     * @param debug true if the cheat mode is enable, false otherwise
     */
    explicit Facade(bool debug = false);
    /**
     * @brief Check if the current game is over or not
     * @return true if the game is over, false otherwise
     */
    bool checkIsOver();
    /**
     * @brief Play a round by moving a piece
     * @param pieceToMove the position of the piece that will be moved
     * @param direction the direction in which the piece will move
     * @param distance the distance the piece will move
     */
    void moveRound(Position pieceToMove,Direction direction,int distance);
    /**
     * @brief Gets the piece in specific position
     * @param pos the position of the piece to gets
     * @return the piece in the given position
     */
    std::optional<Piece> getPieceAt(Position pos);
    /**
     * @brief Gets the game board
     * @return the game board
     */
    std::array<std::array<std::optional<Piece>,Board::BOARD_SIZE>,Board::BOARD_SIZE> getGameBoard() const;
    /**
     * @brief Gets the color of the current player
     * @return color of the current player
     */
    ColorPiece getCurrentPlayer()const;
    /**
     * @brief Play a round by attacking a piece
     * @param attackerPosition the position of the piece that will attack
     * @param defenderPosition the position of the piece that will be attack
     * @return a Piece, the winner of the duel
     */
    std::optional<Piece> playAttackRound(Position attackerPosition,Position defenderPosition);
    /**
     * @brief Gets the winner of the game
     * @return the colors of the winner
     */
    std::optional<ColorPiece> getWinner()const;
    /**
     * @brief Check if the move is valid or not
     * @param pos position of the piece to move
     * @param dir direction in which the piece will be moved
     * @param dist distance of the piece will be moved
     * @return true if the move is valid, false otherwise
     */
    bool isValidMove(Position pos,Direction dir,int dist);
private:
    /**
     * @brief Change the current player colors for the next turn
     */
    void nextPlayer();
};
}

#endif // FACADE_H
