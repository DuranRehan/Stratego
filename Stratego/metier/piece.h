#ifndef PIECE_H
#define PIECE_H
#include "Role.h"
#include "ColorPiece.h"
namespace model {

/**
 * @brief The Piece class define a Piece in the game board
 */
class Piece {
    //attributs
    ColorPiece colorPiece;
    Role role;
    bool hidden;

public:
    /**
     *
     * @brief Define a piece in the game board with specific role and color
     * @param colorPiece  color of the piece
     * @param role role of the piece
     * @param hidden set the piece in hidden face or not @default true
     */
    Piece(ColorPiece colorPiece, Role role, bool hidden = true);

    /**
     * @brief sets the piece in hidden face or not
     * @param value true or false depends
     */
    void setHidden(bool value);

    /**
     * @brief Gets the role of the piece
     * @return the role of the piece
     */

    Role getRole() const;

    /**
     * @brief Gets color of the piece
     * @return color of the piece
     */
    ColorPiece getColor() const;

    /**
     * @brief Check if the piece is hidden or not
     * @return true if the piece is hidden, false otherwise
     */
    bool isHidden() const;
};
} //end of namespace model
#endif // PIECE_H
