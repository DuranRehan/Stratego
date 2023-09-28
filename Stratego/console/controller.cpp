#include <iostream>
#include <string>
#include "controller.h"
#include "facade.h"
#include "view.h"
#include "direction.h"

using namespace controller;
using namespace view;
using namespace std;
using namespace model;

Controller::Controller():game{false},view{game}{}

void Controller::run(){
    view.displayWelcome();
    view.printBoard();
    while(!game.checkIsOver()){
        vector<string> answer = view.askUserPlay();
        if(answer.at(0)=="MOVE"){
            try {
                moveRound(answer);
            }  catch (const exception& e) {
                view.showMessage(e.what());
            }
        } else if(answer.at(0)=="ATTACK"){
            try {
                attackRound(answer);
            }  catch (const exception& e) {
                  view.showMessage(e.what());
            }
        }else if(answer.at(0)=="?"){
            view.displayHelp();
        }else if(answer.at(0)=="EXIT"){
            return;
        } else {
            throw invalid_argument("You cannot be here ! \n");
        }
    }
    view.displayWinner();
}

void Controller::moveRound(vector<string> answer){
    int x = parseLettersToInt(answer.at(1)[0])-1;
    int y =toInteger(answer.at(1))-1;
    Direction dir = parseDirection(answer.at(2));
    if(game.getCurrentPlayer() == BLUE){
        dir = oppositeDirection(dir);
    }
    int dist = (int) answer.at(3)[0]-'0';
    game.moveRound(Position{y,x},dir,dist);
}

void Controller::attackRound(vector<string> answer){
    int column = parseLettersToInt(answer.at(1)[0])-1;
    int row =toInteger(answer.at(1))-1;
    Direction dir = parseDirection(answer.at(2));
    optional<Piece> winner;
    optional<Piece> attacker;
    optional<Piece> defender;
    if(game.getCurrentPlayer() == BLUE){
        dir = oppositeDirection(dir);
    }
    switch (dir) {
    case TOP:
        attacker = game.getPieceAt(Position{row,column});
        defender = game.getPieceAt(Position{row-1,column});
        winner = game.playAttackRound(Position{row,column},Position{row-1,column});
        view.displayAttack(attacker,defender,winner);
        break;
    case BOTTOM:
        attacker = game.getPieceAt(Position{row,column});
        defender = game.getPieceAt(Position{row+1,column});
        winner = game.playAttackRound(Position{row,column},Position{row+1,column});
        view.displayAttack(attacker,defender,winner);
        break;
    case LEFT:
        attacker = game.getPieceAt(Position{row,column});
        defender = game.getPieceAt(Position{row,column-1});
        winner = game.playAttackRound(Position{row,column},Position{row,column-1});
        view.displayAttack(attacker,defender,winner);
        break;
    case RIGHT:
        attacker = game.getPieceAt(Position{row,column});
        defender = game.getPieceAt(Position{row,column+1});
        winner = game.playAttackRound(Position{row,column},Position{row,column+1});
        view.displayAttack(attacker,defender,winner);
        break;
    default:
        throw invalid_argument("Not suppose to be here!\n");
    }
}

Direction Controller::parseDirection(string s){
    if(s=="TOP"){
        return TOP;
    } else if(s=="BOTTOM") {
        return BOTTOM;
    } else if (s=="LEFT") {
        return LEFT;
    } else if(s=="RIGHT"){
        return RIGHT;
    } else{
        throw invalid_argument("The String is not valide !\n");
    }
}

int Controller::toInteger(string s){
    if(s.length() > 2 && s[1]=='1'&& s[2]=='0'){
        return 10;
    }
    return (int) s[1]-'0';
}

int Controller::parseLettersToInt(char t){
    switch (t) {
    case 'A':
        return 1;
        break;
    case 'B':
        return 2;
        break;
    case 'C':
        return 3;
        break;
    case 'D':
        return 4;
        break;
    case 'E':
        return 5;
        break;
    case 'F':
        return 6;
        break;
    case 'G':
        return 7;
        break;
    case 'H':
        return 8;
        break;
    case 'I':
        return 9;
        break;
    case 'J':
        return 10;
        break;
    default:
        throw invalid_argument("Not suppose to be here !\n");
    }
}

Direction Controller::oppositeDirection(Direction dir){
    switch (dir) {
    case TOP:
        return BOTTOM;
        break;
    case BOTTOM:
        return TOP;
        break;
    case LEFT:
        return RIGHT;
        break;
    case RIGHT:
        return LEFT;
        break;
    default:
        throw invalid_argument("Not suppose to be here!\n");
    }
}
