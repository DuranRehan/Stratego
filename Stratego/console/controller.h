#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <vector>
#include "direction.h"
#include "view.h"
#include "facade.h"

namespace controller {
/**
 * @brief Gathers and controls the different elements of the model and the console view.
 *
 */

class Controller{
//atrributs
    model::Facade game;
    view::View view;
public:

    /**
     * @brief Define a console Controller
     */
    explicit Controller();
    /**
     * @brief Run the principal loop of the game
     */
    void run();
private:
    /**
     * @brief parse the users entry (A to J) char to int (1 to 10)
     * @param c char that will be parsed
     * @return the integers corresponding to the letters
     */
    int parseLettersToInt(char c);
    /**
     * @brief parse the given string to a direction
     * @param s the string that will be parsed
     * @return a Direction
     */
    model::Direction parseDirection(std::string s);
    /**
     * @brief Parse the given string to an integer (1 to 10)
     * @param s the string that will be parsed
     * @return integers 1 to 10
     */
    int toInteger(std::string s );
    /**
     * @brief Manage the action of play a round by attacking piece of the game
     * @param userAnswer the user entry
     */
    void attackRound(std::vector<std::string>userAnswer );
    /**
     * @brief Manage the action of play a round by moving piece of the game
     * @param userAnswer the user entry
     */
    void moveRound(std::vector<std::string> userAnswer);
    /**
     * @brief Gets the opposite direction
     * @param dir direction that will be used
     * @return the opposite direction of the given direction
     */
    model::Direction oppositeDirection(model::Direction dir);
};
}
#endif // CONTROLLER_H
