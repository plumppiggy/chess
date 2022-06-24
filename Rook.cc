#include "Rook.h"

using namespace std;

Rook::Rook(bool isWhite) : Piece(isWhite) {}

Rook::~Rook() {}

bool Rook::canMoveTo(Square & dest) {
    bool validMove = false;
    if ((ChessBoard::getBoard()->clearHorPath(*(location()), dest)) || 
        (ChessBoard::getBoard()->clearVertPath(*(location()), dest))) {
        validMove = true;
    }
    return validMove;
}

void Rook::display() {
    if (isWhite) {
        cout << "R";
    } else {
        cout << "r";
    }
}