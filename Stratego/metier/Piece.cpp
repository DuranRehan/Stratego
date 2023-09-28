#include "piece.h"
#include <iostream>
using namespace model;
using namespace std;

Piece::Piece(ColorPiece colorPiece, Role role, bool hidden)
    :colorPiece{colorPiece},role{role},hidden{hidden}{}

void Piece::setHidden(bool value) {
    this->hidden = value;
}

Role Piece::getRole() const{
    return this->role;
}

ColorPiece Piece::getColor() const{
    return this->colorPiece;
}

bool Piece::isHidden() const{
    return this->hidden;
}

