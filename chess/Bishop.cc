#include "Bishop.h"
#include <iostream>

using namespace std;


Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

Bishop::~Bishop() {}

bool Bishop::canMoveTo(Square &newLocation) {
    bool validMove = false;
    if (ChessBoard::getBoard()->clearDiagPath(*(location()), newLocation)) {
        validMove = true;
    }
    return validMove;
}

void Bishop::display() {
    if (isWhite) { 
        cout << "B";
    } else {
        cout << "b";
    }
}