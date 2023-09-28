#ifndef VIEWFX_H
#define VIEWFX_H
#include <QMainWindow>
#include "ui_viewfx.h"
#include "observers.h"
namespace gui {
class ControllerFx;
class BoardFx;

}
QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View :public QMainWindow,public utils::observers::Observers
{
    //attribut
    Q_OBJECT
public:
    //constructor
    explicit View(QWidget * parent = nullptr);
    ~View();
    //attribut
    gui::ControllerFx * controller_ = nullptr;
    gui::BoardFx * board = nullptr;


    void update(const std::string &) override;

    /**
     * @brief updateStartGame update game start
     */
    void updateStartGame();

    /**
     * @brief initializeUi initialize game resources
     */
    void initializeUi();

    // setter
    inline void setController(gui::ControllerFx &ctrl){controller_=&ctrl;};
private:

    /**
     * @brief updateTurnLabel update the game according to the player (red or blue)
     */
    void updateTurnLabel();
    Ui::View *ui;

    /**
     * @brief updateErrorLabel put an error message
     * @param text is the type of error
     */
    void updateErrorLabel(const QString& text);

    /**
     * @brief updateWinnerLabel update the interface for the winner of the game
     */
    void updateWinnerLabel();
private slots:

    // start the game when the button is clicked
    void onClickStart();
};
#endif // VIEWFX_H
