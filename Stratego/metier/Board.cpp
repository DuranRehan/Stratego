#include <regex>
#include <algorithm>
#include <fstream>
#include <string>
#include "board.h"
using namespace model;
using namespace std;

Board::Board(bool debug):debug{debug} {
    initializeDefaultBoard();
    initializeArmy();
}

Board::Board(){
    initializeDefaultBoard();
}

bool Board::isWinner(){
    if(!this->winner.has_value()){
        return false;
    }
    return true;
}

bool Board::isAnotherPlay(){
    if(isEmpty()){
        return false;
    }
    unsigned countBlue = 0;
    for (auto lg : board) {
        for(auto col : lg){
            if(col.has_value()) {
                if(col->getColor() ==ColorPiece::BLUE && col->getRole() != 'B'&&col->getRole() != 'D'){
                    countBlue++;
                }
            }
        }
    }
    unsigned countRed = 0;

    for (auto lg : board) {
        for(auto col : lg){
            if(col.has_value()) {
                if(col->getColor() ==ColorPiece::RED && col->getRole() != 'B'&&col->getRole() != 'D'){
                    countRed++;
                }
            }
        }
    }
    return (countRed>0) && (countBlue >0);
}

bool Board::isGameOver(){
    if(isWinner() || !isAnotherPlay()){
        return true;
    }
    return false;
}

bool Board::isInside(Position pos){
    return 0 <= pos.getX() && 0 <= pos.getY()
            && pos.getX() < BOARD_SIZE && pos.getY() < BOARD_SIZE;
}

bool Board::isEmpty(){
    for (auto lg : board) {
        for(auto col : lg){
            if(col.has_value()) {
                return false;
            }
        }
    }
    return true;
}

void Board::movePiece(Position pos,Direction dir,int dist){
        optional<Piece> &piece = at(pos);
        switch (dir) {
        case Direction::BOTTOM:{
            Position newPos{pos.getX()+dist,pos.getY()};
            board[newPos.getX()][newPos.getY()] = piece;
            board[pos.getX()][pos.getY()].reset();
            break;
        }
        case Direction::TOP: {
            Position newPos{pos.getX()-dist,pos.getY()};
            board[newPos.getX()][newPos.getY()] = piece;
            board[pos.getX()][pos.getY()].reset();
            break;
        }
        case Direction::RIGHT:{
            Position newPos{pos.getX(),pos.getY()+dist};
            board[newPos.getX()][newPos.getY()] = piece;
            board[pos.getX()][pos.getY()].reset();
            break;
        }
        case Direction::LEFT:{
            Position newPos{pos.getX(),pos.getY()-dist};
            board[newPos.getX()][newPos.getY()] = piece;
            board[pos.getX()][pos.getY()].reset();
            break;
        }
        default:
            throw invalid_argument("Cannot be moved in this direction !\n");
        }
}

bool Board::moveValid(Position pos,Direction dir,int distance) {
    optional<Piece> piece = board[pos.getX()][pos.getY()];
    if(!isInside(pos)
            ||piece->getRole()=='B'
            || piece->getRole()=='D'
            || (piece->getRole()!='2' && distance != 1)
            || distance <1)
    {
        return false;
    }
    for(int i =1; i <= distance;i++ ) {
        switch(dir){
        case Direction::BOTTOM:{
            Position tempPos{pos.getX()+i,pos.getY()};
            if(!isInside(tempPos))
                return false;
            else if(isPieceAt(tempPos)){
                return false;
            }
            break;
        }
        case Direction::TOP:{
            Position tempPos{pos.getX()-i,pos.getY()};
            if(!isInside(tempPos))
                return false;
            else if(isPieceAt(tempPos))
                return false;
            break;
        }
        case Direction::RIGHT:{
            Position tempPos{pos.getX(),pos.getY()+i};
            if(!isInside(tempPos))
                return false;
            else if(isPieceAt(tempPos))
                return false;
            break;
        }
        case Direction::LEFT:{
            Position tempPos{pos.getX(),pos.getY()-i};
            if(!isInside(tempPos))
                return false;
            else if(isPieceAt(tempPos))
                return false;
            break;
        }
        default:
            throw invalid_argument("Not supposed to go there !\n");
        }
    }
    return true;
}

optional<Piece> Board::attackPiece(Position pos1, Position pos2 ){
    optional<Piece> &attacker = at(pos1);
    optional<Piece> &defender = at(pos2);
    optional<Piece> winnerPiece{};
    attacker->setHidden(false);
    defender->setHidden(false);
    if(defender->getRole()=='D'){
        defender.reset();
        winnerPiece=attacker;
        at(pos2)=attacker;
        at(pos1) = nullopt;
        this->winner = attacker->getColor();
    } else if(defender->getRole() == 'B' && attacker->getRole()=='3') {
        defender.reset();
         winnerPiece=attacker;
        at(pos2)=attacker;
        at(pos1) = nullopt;
    } else if(defender->getRole() == 'B' && attacker->getRole() !='3'){
        attacker.reset();
        winnerPiece=defender;
        at(pos1) = nullopt;
    }else if(attacker->getRole()=='1' && defender->getRole() =='M'){ //ATTENTION : Marechal M et Espion 1! car 10 = 2char
        defender.reset();
        winnerPiece=attacker;
        at(pos2)=attacker;
        at(pos1) = nullopt;
    }else if(attacker->getRole() < defender->getRole()){
        attacker.reset();
        winnerPiece=defender;
        at(pos1) = nullopt;
    } else if(attacker->getRole() > defender->getRole()){
        defender.reset();
        winnerPiece=attacker;
        at(pos2)=attacker;
        at(pos1) = nullopt;
    } else if(attacker->getRole() == defender->getRole()){
        attacker.reset();
        defender.reset();
        winnerPiece = nullopt;
        at(pos1) = nullopt;
        at(pos2) = nullopt;
    }
    if(!debug){
        attacker->setHidden(true);
        defender->setHidden(true);
    }
    return winnerPiece;
}

void Board::setPiece(optional<Piece>& piece,Position p){
    at(p) =piece;
}

void Board::initializeArmy(){
    //BlueFile config
    string url{"../../Stratego/blue.txt"};
    if(checkFileIsOk(url)){
        ifstream blueFile(url);
        vector<char> blueVector;
        if(blueFile) {
            string mot;
            while(blueFile >> mot) {
                blueVector.push_back(toupper(mot[0]));
            }
            blueFile.close();
        }
        reverse(blueVector.begin(),blueVector.end());
        for(unsigned lg = 0; lg < 4;lg++){
            for(unsigned col =0; col <10;col++){
                board[lg][col] = Piece{ColorPiece::BLUE,parseRole(blueVector.at(blueVector.size()-1))};
                blueVector.pop_back();
            }
        }
    } else {
        throw invalid_argument("[ERROR] Blue Files is not valid\n");
    }

    //RedFile config
    url="../../Stratego/red.txt";
    if(checkFileIsOk(url)){
        ifstream redFile(url);
        vector<char> redVector;
        if(redFile)
        {
            string mot;
            while(redFile >> mot) {
                redVector.push_back(toupper(mot[0]));
            }
            redFile.close();
        }
        reverse(redVector.begin(),redVector.end());
        for(unsigned lg = 9; lg >= 6;lg--){
            for(unsigned col =0; col <10;col++){
                board[lg][col] = Piece{ColorPiece::RED,parseRole(redVector.at(redVector.size()-1))};
                redVector.pop_back();
            }
        }
        cout<<endl;
    } else {
        throw invalid_argument("[ERROR] Red Files is not valid\n");
    }
}

bool Board::checkFileIsOk(string url) {
    ifstream file(url);
    string tempString{""};
    regex reg{"(((\\d)|([BDbdMm])|[^a-zA-Z])){40}"};
    if(file)
    {
        unsigned count= 0;
        string mot;
        vector<int> listOfPieces(12);
        while(file >> mot) {
            if(!(mot.length() > 1)) {
                tempString += mot;
                count++;
                countPiece(listOfPieces,mot);
            } else {
                return false;
            }
        }
        if(
                listOfPieces[0] != 1 ||
                listOfPieces[1] != 1 ||
                listOfPieces[2] != 8 ||
                listOfPieces[3] != 5 ||
                listOfPieces[4] != 4 ||
                listOfPieces[5] != 4 ||
                listOfPieces[6] != 4 ||
                listOfPieces[7] != 3 ||
                listOfPieces[8] != 2 ||
                listOfPieces[9] != 1 ||
                listOfPieces[10] !=1 ||
                listOfPieces[11] != 6) {
            return false;
        }
        if(count != 40) {
            return false;
        }
        file.close();
        if(regex_match(tempString,reg)) {
            return true;
        } else {
            return false;
        }
    }else{
        throw invalid_argument("[ERROR] no files found");
    }

    return false;
}

void Board::countPiece(vector<int>& l,string mot) {
    switch (toupper(mot[0])) {
    case '1':
        l[1]++;
        break;
    case '2':
        l[2]++;
        break;
    case '3':
        l[3]++;
        break;
    case '4':
        l[4]++;
        break;
    case '5':
        l[5]++;
        break;
    case '6':
        l[6]++;
        break;
    case '7':
        l[7]++;
        break;
    case '8':
        l[8]++;
        break;
    case '9':
        l[9]++;
        break;
    case 'M':
        l[10]++;
        break;
    case 'B':
        l[11]++;
        break;
    case 'D':
        l[0]++;
        break;
    }
}

void Board::initializeDefaultBoard(){
    for(auto pos : BOARD_WALL){
        optional<Piece> wall{{ColorPiece::NEUTRAL,WALL,false}};
        this->setPiece(wall,pos);
    }
}

bool Board::isPieceAt(Position p){
    return at(p).has_value();
}

optional<Piece>& Board::at(Position pos){
    return board[pos.getX()][pos.getY()];
}

optional<ColorPiece> Board::getWinner() const{
    return winner;
}

array<array<optional<Piece>,Board::BOARD_SIZE>,Board::BOARD_SIZE> Board::getGameBoard() const{
    return board;
}

Role Board::parseRole(char c){
    switch (c) {
    case 'M':
        return MARECHAL;
        break;
    case '9':
        return GENERAL;
        break;
    case '8':
        return COLONEL;
        break;
    case '7':
        return MAJOR;
        break;
    case '6':
        return COMMANDANT;
        break;
    case '5':
        return LIEUTENANT;
        break;
    case '4':
        return SERGENT;
        break;
    case '3':
        return DEMINEUR;
        break;
    case '2':
        return ECLAIREUR;
        break;
    case '1':
        return ESPIONNE;
        break;
    case 'D':
        return FLAG;
        break;
    case 'B':
        return BOMBE;
        break;
    case 'W':
        return WALL;
        break;
    default:
        throw invalid_argument("not suppose to go there ! \n");
    }
}

void Board::setVisiblePieces(ColorPiece color,bool value){
    for (auto &lg : board) {
        for(auto &col : lg){
            if(col->getColor() ==color) {
                col->setHidden(value);
            }
        }
    }
}
