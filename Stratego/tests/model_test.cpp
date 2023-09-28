#include <catch.hpp>
#include "board.h"
using namespace std;
using namespace model;

Board board{};
TEST_CASE("Moving"){
    SECTION("Moving flag"){
        Position pos{1,1};
        optional<Piece> piece{{BLUE,FLAG}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM));
    }
    SECTION("Moving as a bomb"){
        Position pos{1,1};
        optional<Piece> piece{{BLUE,BOMBE}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM));
    }
    SECTION("Moving as a flag more than by 1 case"){
        Position pos{1,1};
        optional<Piece> piece{{BLUE,FLAG}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM,5));

    }
    SECTION("Trying to move outside the board - left"){
        Position pos{0,0};
        optional<Piece> piece{{BLUE,MAJOR}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::LEFT));
    }
    SECTION("Trying to move 1 that more case as a marechal.") {
        Position pos{1,1};
        optional<Piece> piece{{BLUE,MARECHAL}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM,5));
    }
    SECTION("Scout moving more than 1 case, and obstacle in the way") {
        Position pos{5,5};
        optional<Piece> piece{{BLUE,ESPIONNE}};
        board.setPiece(piece,pos);

        Position pos2{7,5};
        optional<Piece> piece2{{BLUE,DEMINEUR}};
        board.setPiece(piece2,pos2);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM,4));
    }
    SECTION("Moving straignt into an obstacle (water)" ) {
        Position pos{3,2};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        REQUIRE_FALSE(board.moveValid(pos,Direction::BOTTOM));
    }

    SECTION("Moving into an empty space by 1 - TOP") {
        Board board{};
        Position pos{1,1};
        Position pos2{0,1};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::TOP);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Moving into an empty space by 1 - LEFT"){
        Board board{};
        Position pos{1,1};
        Position pos2{1,0};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::LEFT);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Moving into an empty space by 1 - RIGHT"){
        Board board{};
        Position pos{1,1};
        Position pos2{1,2};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::RIGHT);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Moving into an empty space by 1 - BOTTOM"){
        Board board{};
        Position pos{1,1};
        Position pos2{2,1};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::BOTTOM);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Scout moving more than 1 case - LEFT") {
        Board board{};
        Position pos{3,4};
        Position pos2{3,0};
        optional<Piece> piece{{BLUE,ECLAIREUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::LEFT,4);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Scout moving more than 1 case - RIGHT") {
        Board board{};
        Position pos{3,4};
        Position pos2{3,8};
        optional<Piece> piece{{BLUE,ECLAIREUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::RIGHT,4);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Scout moving more than 1 case - BOTTOM") {
        Board board{};
        Position pos{3,4};
        Position pos2{7,4};
        optional<Piece> piece{{BLUE,ECLAIREUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::BOTTOM,4);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Scout moving more than 1 case - TOP") {
        Board board{};
        Position pos{3,4};
        Position pos2{0,4};
        optional<Piece> piece{{BLUE,ECLAIREUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,Direction::TOP,3);
        REQUIRE(board.at(pos2)->getRole()==piece->getRole());
    }
    SECTION("Move then check if previous position empty" ) {
        Board board{};
        Position pos{3,4};
        optional<Piece> piece{{BLUE,DEMINEUR}};
        board.setPiece(piece,pos);
        board.movePiece(pos,LEFT);
        REQUIRE(!board.isPieceAt(pos));
    }
}

TEST_CASE("Attack"){
    // 7 tests
    SECTION("Both same value"){
        Board board{};
        Position pos{3,4};
        Position pos2{2,3};
        optional<Piece> attacker{{BLUE,DEMINEUR}};
        optional<Piece> defenser{{RED,DEMINEUR}};
        board.setPiece(attacker,pos);
        board.setPiece(defenser,pos2);
        board.attackPiece(pos,pos2);
        REQUIRE(!(board.isPieceAt(pos) && board.isPieceAt(pos2)));
    }

    SECTION("Empty last position after attacking success"){
        Board board{};
        Position pos{3,4};
        Position pos2{2,3};
        optional<Piece> attacker{{BLUE,ESPIONNE}};
        optional<Piece> defenser{{RED,MARECHAL}};
        board.setPiece(attacker,pos);
        board.setPiece(defenser,pos2);
        board.attackPiece(pos,pos2);
        REQUIRE((!board.at(pos).has_value()&& board.at(pos2).has_value()));
    }

    SECTION("Spy attacking marechal"){
        Board board{};
        Position pos{3,4};
        Position pos2{2,3};
        optional<Piece> attacker{{BLUE,ESPIONNE}};
        optional<Piece> defenser{{RED,MARECHAL}};
        board.setPiece(attacker,pos);
        board.setPiece(defenser,pos2);
        board.attackPiece(pos,pos2);
        REQUIRE(board.at(pos2)->getRole()=='1');
    }

    SECTION("Bomb is attacked by non-sapper"){
        Board board{};
        Position pos{3,4};
        Position pos2{2,3};
        optional<Piece> attacker{{BLUE,MAJOR}};
        optional<Piece> defenser{{RED,BOMBE}};
        board.setPiece(attacker,pos);
        board.setPiece(defenser,pos2);
        board.attackPiece(pos,pos2);
        REQUIRE((!board.at(pos).has_value() && defenser->getRole()==BOMBE));
    }

    SECTION("Bomb is attacked by a sapper"){
        Board board{};
        Position pos{3,4};
        Position pos2{2,3};
        optional<Piece> attacker{{BLUE,DEMINEUR}};
        optional<Piece> defenser{{RED,BOMBE}};
        board.setPiece(attacker,pos);
        board.setPiece(defenser,pos2);
        board.attackPiece(pos,pos2);
        REQUIRE((board.at(pos2).has_value() && board.at(pos2)->getRole()=='3'));
    }
}

TEST_CASE("isGameOver"){
    SECTION("2 flags left, both players can move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,ESPIONNE}};
        board.at(Position{2,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{3,3})=optional {Piece{BLUE,DEMINEUR}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,ECLAIREUR}};
        board.at(Position{4,6})=optional {Piece{RED,ESPIONNE}};
        REQUIRE(!board.isGameOver());
    }
    SECTION("blue flag left, both players can move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,ESPIONNE}};
        board.at(Position{2,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{3,3})=optional {Piece{BLUE,DEMINEUR}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,ECLAIREUR}};
        board.at(Position{4,6})=optional {Piece{RED,ESPIONNE}};
        //blue Scout attack red Flag -> one flag remain
        board.attackPiece(Position{1,3},Position{4,9});
        REQUIRE(board.isGameOver());
    }

    SECTION("red flag left, both players can move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,ESPIONNE}};
        board.at(Position{2,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{3,3})=optional {Piece{BLUE,DEMINEUR}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,ECLAIREUR}};
        board.at(Position{4,6})=optional {Piece{RED,ESPIONNE}};
        //red Scout attack blue Flag -> one flag remain
        board.attackPiece(Position{4,6},Position{2,3});
        REQUIRE(board.isGameOver());
    }

    SECTION("2 flag left, Blue player can't move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{2,3})=optional {Piece{BLUE,BOMBE}};
        board.at(Position{3,3})=optional {Piece{BLUE,BOMBE}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,ESPIONNE}};
        board.at(Position{4,6})=optional {Piece{RED,ECLAIREUR}};
        REQUIRE(board.isGameOver());
    }

    SECTION("2 flag left, Red player can't move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{2,3})=optional {Piece{BLUE,ECLAIREUR}};
        board.at(Position{3,3})=optional {Piece{BLUE,ESPIONNE}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,BOMBE}};
        board.at(Position{4,6})=optional {Piece{RED,BOMBE}};
        REQUIRE(board.isGameOver());
    }
    SECTION("2 flag left, both player can't move"){
        Board board{};
        //player 1
        board.at(Position{1,3})=optional {Piece{BLUE,FLAG}};
        board.at(Position{2,3})=optional {Piece{BLUE,BOMBE}};
        board.at(Position{3,3})=optional {Piece{BLUE,BOMBE}};
        //player 2
        board.at(Position{4,9})=optional {Piece{RED,FLAG}};
        board.at(Position{4,7})=optional {Piece{RED,BOMBE}};
        board.at(Position{4,6})=optional {Piece{RED,BOMBE}};
        REQUIRE(board.isGameOver());
    }
}
