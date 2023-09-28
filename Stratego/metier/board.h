#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <array>
#include <optional>

#include "piece.h"
#include "position.h"
#include "direction.h"
namespace model {
// positions of the water
static const std::vector<Position> BOARD_WALL{
    Position{4,2},
    Position{4,3},

    Position{5,2},
    Position{5,3},

    Position{4,6},
    Position{4,7},

    Position{5,6},
    Position{5,7},
};

/**
 * @brief Board class represent the game board and implement all logic behind the game
 *
 */
class Board{
    //attributs
public:
    static const int BOARD_SIZE = 10;
private:
    std::array<std::array<std::optional<Piece>,BOARD_SIZE>,BOARD_SIZE> board;
    bool debug;
    std::optional<ColorPiece> winner;
public :

    /**
     * @brief Initialize a default board
     * @param debug true if the cheat mode is enable, false otherwise
     */
    explicit Board(bool debug);
    /**
     * @brief default constructor for testing, does not initialize player armies
     */
    explicit Board(); //Only for testing with CATCH !
    /**
     * @brief check if the given position is inside the board of not
     * @param p position that will be checked
     * @return
     */
    bool isInside(Position p);
    /**
     * @brief Check if the board is empty or not
     * @return true if the board is empty, false otherwise
     */
    bool isEmpty();
    /**
     * @brief moves the piece a certain position, in certain direction and distance
     * @param pos the position of the piece that will be moved
     * @param direction the direction in which the piece will move
     * @param distance the distance the piece will move
     */
    void movePiece(Position pos,model::Direction dir,int distance=1);
    /**
     * @brief check if the move of a certain piece is allowed or not
     * @param pos the position of the piece that will be moved
     * @param direction the direction in which the piece will move
     * @param distance the distance the piece will move
     * @return true if the move is allowed, false otherwise
     */
    bool moveValid(Position pos,model::Direction dir,int distance=1);
    /**
     * @brief attacking a piece in certain position with a certains Piece
     * @param attackerPosition the position of the piece that will attack
     * @param defenderPosition the position of the piece that will be attack
     * @return a Piece, the winner of the duel
     */
    std::optional<Piece> attackPiece(Position attackerPosition,Position defenderPosition);
    /**
     * @brief set a piece in the game board
     * @param piece that will be setted
     * @param p the position where the piece will be setted
     */
    void setPiece(std::optional<Piece> &piece,Position p);
    /**
     * @brief initialize the army of the players with their files
     */
    void initializeArmy();
    /**
     * @brief check if the board contains a piece in given position
     * @param pos position of the board to check
     * @return true if the board contains a piece in this position, false otherwise
     */
    bool isPieceAt(Position pos);
    /**
     * @brief check if there is still a move to be made
     * @return true if there is a move that can be maded, false otherwise
     */
    bool isAnotherPlay();
    /**
     * @brief Check if there is a winner (capture the enemy flag)
     * @return true, if there is a winner, false otherwise
     */
    bool isWinner();
    /**
     * @brief Check if the game is over or not
     * @return true, if the game is over, false otherwise
     */
    bool isGameOver();
    /**
     * @brief Gets the piece by reference at certains position
     * @param pos position of the piece
     * @return the piece piece in given position
     */
    std::optional<Piece>& at(Position pos);
    /**
     * @brief Gets color the winner of the game
     * @return the color of the winner
     */
    std::optional<ColorPiece> getWinner()const;
    /**
     * @brief get the game board of the game
     * @return the game board of the game
     */
    std::array<std::array<std::optional<Piece>,Board::BOARD_SIZE>,Board::BOARD_SIZE> getGameBoard() const;
    /**
     * @brief Set all pieces of a certain color visible or not
     * @param value true or false depend
     */
    void setVisiblePieces(ColorPiece color,bool value);
private:
    /**
     * @brief check if the given file is correctly form or not
     * @param url, the url of the file to check
     * @return true, if the file is correctly form, false otherwise
     */
    bool checkFileIsOk(std::string url);
    /**
     * @brief counts the number of occurrences of a piece and save it in a vector
     * @param vec the vector that will be check
     * @param nb the number that will be counted
     */
    void countPiece(std::vector<int>& vec,std::string nb);
    /**
     * @brief initialize the default board of the game with water piece
     */
    void initializeDefaultBoard();
    /**
     * @brief parse the char to a role
     * @param c char that will be parsed
     * @return a char parsed in role
     */
    Role parseRole(char c);

};

} //Namespace model
#endif // BOARD_H
