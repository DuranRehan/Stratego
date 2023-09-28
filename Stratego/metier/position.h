#ifndef POSITION_H
#define POSITION_H
namespace  model {
/**
 * @brief Determine a precise position on the game board
 *
 */
class Position {
    //attributs
    int x;
    int y;

public:

    /**
     * @brief Define a position on the game board
     *
     * @param x the row of the game board
     * @param y the column of the game board
     */
    Position(int x,int y);

    /**
     * @brief Gets the x position of the board
     *
     * @return x positions
     */
    int getX() const;

    /**
     * @brief Gets the y position of the board
     *
     * @return y positions
     */
    int getY() const;
};

} //end of namespace model

#endif // POSITION_H
