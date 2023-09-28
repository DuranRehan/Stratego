#include <regex>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "view.h"
#include "facade.h"
using namespace view;
using namespace std;
using namespace model;

View::View(Facade &game):game{game}{
    this->game.subscribe(this);
}

void View::printBoard(){
    int i = 1;
    int lgCount=0;
    displayCurrentTurn();
    displayHeader();
    auto board = game.getGameBoard();
    for (auto lg : board) {
        lgCount++;
        cout<<setw(2)<<lgCount<<"|   ";
        for(auto col : lg){
            if(col.has_value()) {
                if(i == 10) {
                    if (col->getColor() == game.getCurrentPlayer() || !col->isHidden()) {
                        cout<<parseRole(col->getRole())<<"    |"<<lgCount<<endl;
                        i=1;
                    }else if(col->getRole() != 'W' && col->isHidden()){
                        cout<<"?"<<"    |"<<lgCount<<endl;
                        i=1;
                    }
                }else if(col->getColor() != game.getCurrentPlayer() && col->getRole() != 'W' && col->isHidden()) {
                    cout<< "?"<< " ";
                    i++;
                } else {
                    cout<< parseRole(col->getRole())<< " ";
                    i++;
                }
            } else {
                if(i == 10) {
                    cout<<"*"<<"    |"<<lgCount<<endl;
                    i=1;
                } else {
                    cout<<"*"<<" ";
                    i++;
                }
            }
        }
    }
    displayFooter();
}

void View::displayWelcome(){
    cout<<setw(3)<<"|"<<"--------------------------|"<<endl;
    cout<<setw(3)<<"|"<<"    Welcome to Stratego   |"<<endl;
    cout<<setw(3)<<"|"<<"         2021-2022        |"<<endl;
}

void View::displayCurrentTurn() {
    cout<<setw(3)<<"|"<<"--------------------------|"<<endl;
    if(game.getCurrentPlayer()==BLUE)
        cout<<setw(3)<<"|"<<"    It's BLUE's turn      |"<<endl;
    else
        cout<<setw(3)<<"|"<<"    It's RED's turn       |"<<endl;
}

void View::displayHeader(){
    cout<<setw(3)<<"|"<<"--------------------------|"<<endl;
    char letters[] ={'A','B','C','D','E','F','G','H','I','J'};
    cout<<setw(3)<<"|"<<"   ";
    for(int i = 0; i<10;i++){
        cout<<letters[i]<<" ";
    }
    cout<<"   |"<<endl;
    cout<<setw(3)<<"|"<<"--------------------------|"<<endl;
}

void View::displayFooter(){
    displayHeader();
}

std::vector<std::string> View::askUserPlay(){
    string ans;
    // move A5 TOP 1
    // attack top/bottom/left/right
    string moveRegex = "(MOVE\\s[A-J]{1}(([1-9])|10)+\\s(TOP|BOTTOM|LEFT|RIGHT)+(\\s(([1-9]|10))){1})";
    string attackRegex="(ATTACK\\s[A-J]{1}(([1-9])|10)+\\s(TOP|BOTTOM|LEFT|RIGHT))";
    string helpRegex="(\\?)";
    string allRegex = moveRegex+"|"+attackRegex+"|"+helpRegex;
    regex reg{allRegex};
    cout<<"<<<ENTER YOUR MOVE>>>"<<endl;
    getline(cin,ans);
    while(!regex_match(ans,reg)){
        cout<<"[ERROR] The command is not correctly form ! <use '?' to help> "<<endl;
        cout<<"<<<Retry>> ";
        getline(cin,ans);
    }
    vector<string> answer{};
    splitString(answer,ans);
    cout<<endl;
    return answer;
}

void View::splitString(vector<string>& split,string text){
    char space_char = ' ';
    stringstream sstream(text);
    string word;
    while (getline(sstream, word, space_char)) {
        split.push_back(word);
    }
}

void View::displayHelp(){
    cout<<"-+-+-+-+-+-+HELP+-+-+-+-+-+"<<endl
       <<">>MOVE [Position] [DIRECTION] [DISTANCE]" <<endl
      <<">>ATTACK [Position] [DIRECTION]"<<endl
     <<"         >>>EXAMPLE<<<"<<endl
    <<">>MOVE F5 TOP 1 | MOVE E3 LEFT 5"<<endl
    <<">>ATTACK J8 TOP | ATTACK A3 RIGHT"<<endl
    <<"-+-+-+-+-+-+-+-+-+-+-+-+-+-+"<<endl;
}

void View::displayAttack(optional<Piece> attacker, optional<Piece> defender,optional<Piece>& winner){
    cout<<"----------------------"<<endl
        <<"  ATTACK IN PROGRESS  "<<endl
        <<"      Attacker : "<<parseColors(attacker->getColor())<<" "<<parseRole(attacker->getRole())<<endl
        <<"      Defender : "<<parseColors(defender->getColor())<<" "<<parseRole(defender->getRole())<<endl
        <<"     END OF ATTACK   "<<endl
        <<"----------------------"<<endl;

    if(winner.has_value()){
        cout<<"     Winner => "<<parseColors(winner->getColor())<<" "<<parseRole(winner->getRole())<<endl;
    } else  {
        cout<<"     Both are dead"<<endl;
    }
    cout<<"--------------------"<<endl;
}

void View::displayWinner(){
    cout<<"---------------------"<<endl;
    cout<<"        Winner!      "<<endl;
    cout<<"        "<<parseColors(game.getWinner())<<" Army  "<<endl;
    cout<<"---------------------"<<endl;
}

void View::showMessage(string s){
    cout<<s;
}

string View::parseColors(optional<ColorPiece>color){
    switch (color.value()) {
    case BLUE:
        return "BLUE";
        break;
    case RED:
        return "RED";
        break;
    case NEUTRAL:
        return "NEUTRAL";
    default:
        throw invalid_argument("not suppose to go there ! \n");
    }
}

string View::parseRole(Role role){
    switch (role) {
    case MARECHAL:
        return "M";
        break;
    case GENERAL:
        return "9";
        break;
    case COLONEL:
        return "8";
        break;
    case MAJOR:
        return "7";
        break;
    case COMMANDANT:
        return "6";
        break;
    case LIEUTENANT:
        return "5";
        break;
    case SERGENT:
        return "4";
        break;
    case DEMINEUR:
        return "3";
        break;
    case ECLAIREUR:
        return "2";
        break;
    case ESPIONNE:
        return "1";
        break;
    case FLAG:
        return "D";
        break;
    case BOMBE:
        return "B";
        break;
    case WALL:
        return "W";
        break;
    default:
        throw invalid_argument("not suppose to go there ! \n");
    }
}

void View::update(const std::string &toUpdate) {
    if(toUpdate == "ATTACK"){
        printBoard();
    }
    if(toUpdate == "MOVE"){
        printBoard();
    }
}




