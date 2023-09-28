#include "boardfx.h"
#include "controllerFx.h"
#include "viewfx.h"
#include <QPushButton>
using namespace model;
using namespace gui;
View::View(QWidget * parent) :
    QMainWindow(parent),utils::observers::Observers(),
    ui(new Ui::View)
{
    ui->setupUi(this);
    this->setWindowTitle("Stratego - Duran Rehan & Lama Ajit, 56055 & 55084, HE2B - ESI");
    this->setWindowIcon(QIcon(":/resources/icon.png"));
    this->setFixedSize(1660,780);
}
void View::initializeUi() {
    ui->title->setVisible(false);
    ui->statusLabel->setVisible(false);
    ui->winnerLabel->setVisible(false);
    ui->startBtn->connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(onClickStart()));
    ui->turnLabel->setVisible(false);
}
void View::onClickStart(){
    ui->startMenu->setVisible(false);
    model::Facade *game = new Facade(ui->checkBox->isChecked());
    controller_->setGame(*game);
    updateStartGame();
}

void View::updateStartGame(){
    board = new BoardFx{};
    board->setController(*controller_);
    board->updateBoard();
    ui->root->addLayout(board);
    ui->errorLabel->setVisible(false);
    ui->statusLabel->setVisible(true);
    ui->title->setVisible(true);
}

void View::update(const std::string &toUpdate) {
    if(toUpdate == "MOVE"){
        board->updateBoard();
        controller_->game().checkIsOver();
        ui->errorLabel->setVisible(false);
        updateTurnLabel();
    } else if(toUpdate == "ATTACK") {
        board->updateBoard();
        controller_->game().checkIsOver();
        ui->errorLabel->setVisible(false);
        updateTurnLabel();
    } else if(toUpdate == "GAME_OVER") {
       updateWinnerLabel();
    }else if(toUpdate =="ATTACK_OBSTACLE"){
        updateErrorLabel("You cannot attack obstacle");
    }
    else if(toUpdate =="ATTACK_SELF"){
        updateErrorLabel("You cannot attack your piece");
    }
    else if(toUpdate =="ILLEGAL_ATTACK"){
        updateErrorLabel("This piece cannot attack");
    }
    else if(toUpdate =="ATTACK_VOID"){
        updateErrorLabel("You cannot attack an empty place");
    }

    else if(toUpdate =="NOT_CORRECT_CURRENT_PLAYER"){
        updateErrorLabel("You cannot do that with that piece");
    }

    else if(toUpdate =="MOVE_NOT_VALID"){
        updateErrorLabel("This move is not allowed");
    }
}

void View::updateErrorLabel(const QString &text){
    ui->errorLabel->setVisible(true);
    ui->errorLabel->setText("[ERROR] " + text + " !");
}

void View::updateTurnLabel(){
    ui->turnLabel->setVisible(true);
    if(controller_->getCurrentTurn() == model::BLUE){
        ui->turnLabel->setText("Blue Turn");
        ui->turnLabel->setStyleSheet("color: rgb(0, 0, 255);");
    } else {
        ui->turnLabel->setText("Red Turn");
        ui->turnLabel->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void View::updateWinnerLabel(){
    ui->winnerLabel->setVisible(true);
    ui->errorLabel->setVisible(false);
    ui->statusLabel->setVisible(false);
    ui->rootWidget->setEnabled(false);
    ui->turnLabel->setVisible(false);
    if(controller_->getWinner() == BLUE){
        ui->winnerLabel->setText("And Blue win the battle ! Good job");
        ui->winnerLabel->setStyleSheet("color: rgb(0, 0, 255);");
    } else {
        ui->winnerLabel->setText("And Red win the battle ! Good job");
        ui->winnerLabel->setStyleSheet("color: rgb(255, 0, 0);");
    }
}
View::~View()
{
    delete ui;
}

