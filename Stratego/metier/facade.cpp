#include "facade.h"
using namespace std;
using namespace model;

Facade::Facade(bool debug):board{debug},currentPlayer{RED},debugMode{debug}{
}

bool Facade::checkIsOver(){
    if(board.isGameOver()){
        notify("GAME_OVER");
        return  true;
    }
    return false;
}

void Facade::nextPlayer(){
    if (currentPlayer == RED) {
        currentPlayer = BLUE;
    } else {
        currentPlayer = RED;
    }
}

void Facade::moveRound(Position pos,Direction dir,int dist){
    if(board.at(pos)->getColor() != currentPlayer){
        notify("NOT_CORRECT_CURRENT_PLAYER");
        throw invalid_argument("[ERROR] You are not allowed to move this piece, not your piece !\n");
    }
    if(board.moveValid(pos,dir,dist)){
        board.movePiece(pos,dir,dist);
        nextPlayer();
        notify("MOVE");
    }else{
        notify("MOVE_NOT_VALID");
        throw invalid_argument("[ERROR] This move is not allowed !\n");
    }
}

optional<Piece> Facade::playAttackRound(Position attackerPos, Position defenderPos){
    optional<Piece> attacker = board.at(attackerPos);
    optional<Piece> defender = board.at(defenderPos);
    if(board.at(attackerPos)->getColor() != currentPlayer){
        notify("NOT_CORRECT_CURRENT_PLAYER");
        throw invalid_argument("[ERROR] Attack with this piece is not allowed, not your piece !\n");
    }
    if(!attacker.has_value()||!defender.has_value()){
        notify("ATTACK_VOID");
        throw invalid_argument("[ERROR] Cannot attack the void\n");
    }
    if(attacker->getColor() == defender->getColor()){
        notify("ATTACK_SELF");
        throw invalid_argument("[ERROR] Attacking yourself is not allowed !\n");
    }
    if(defender->getRole()=='W'){
        notify("ATTACK_OBSTACLE");
        throw invalid_argument("[ERROR] This Piece cannot be attacked\n");
    }
    if(attacker->getRole() == 'B'
            || (attacker->getRole() == 'W')
            || attacker->getRole() == 'D'
            || attacker->getRole() == '.'){
        notify("ILLEGAL_ATTACK");
        throw invalid_argument("[ERROR] This Piece cannot attack\n");
    }
    optional<Piece> winner = board.attackPiece(attackerPos,defenderPos);
    nextPlayer();
    notify("ATTACK");
    return winner;
}

bool Facade::isValidMove(Position pos,Direction dir,int dist){
    return board.moveValid(pos,dir,dist);
}

optional<Piece> Facade::getPieceAt(Position pos){
    return board.at(pos);
}

array<array<optional<Piece>,Board::BOARD_SIZE>,Board::BOARD_SIZE> Facade::getGameBoard() const{
    return board.getGameBoard();
}

ColorPiece Facade::getCurrentPlayer()const{
    return currentPlayer;
}

optional<ColorPiece> Facade::getWinner()const{
    return board.getWinner();
}
