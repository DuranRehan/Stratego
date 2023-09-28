#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include "piece.h"
#include "observers.h"

namespace model {
class Facade;
class Position;
}


namespace view {

/**
 * @brief Define the console view of Stratego
 */
class View : utils::observers::Observers {
    model::Facade &game;
public:
    /**
     * @brief Define a console view
     * @param game the game to display
     */
    View(model::Facade& game);
    /**
     * @brief Print the game board
     */
    void printBoard();
    /**
     * @brief Display a welcome message
     */
    void displayWelcome();
    /**
     * @brief Ask user to enter the desired play
     *
     * @return the desired play of user
     */

    std::vector<std::string> askUserPlay();
    /**
     * @brief Display the current player turn
     */
    void displayCurrentTurn();
    /**
     * @brief Display the help messages
     */
    void displayHelp();
    /**
     * @brief Display the current attack
     */
    void displayAttack(std::optional<model::Piece>,std::optional<model::Piece>,std::optional<model::Piece>&);
    /**
     * @brief Show a message to user
     * @param msg the message to send
     */
    void showMessage(std::string msg);
    /**
     * @brief Display the winner color
     */
    void displayWinner();
    /**
     * @brief Reimplementation of update method of parent class
     * @param toUpdate the update to make
     */
    void update(const std::string &toUpdate) override;
private:
    /**
     * @brief Display the header of game board
     */
    void displayHeader();
    /**
     * @brief Display the footer of game board
     */
    void displayFooter();
    /**
     * @brief Split string with space delimiter
     */
    void splitString(std::vector<std::string>&, std::string);
    /**
     * @brief Parse the color given to string
     * @param color the color to parse
     * @return a string representing a color
     */
    std::string parseColors(std::optional<model::ColorPiece> color);
    /**
     * @brief Parse the role given to string
     * @param role the role to parse
     * @return a string representing a role
     */
    std::string parseRole(model::Role role);
};
}
#endif // VIEW_H
