#include "Bishop.h"
#include <iostream>

using namespace std;


Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

Bishop::~Bishop() {}

bool Bishop::canMoveTo(ChessBoard& board, Square &dest) {
    if (dest == *(location())) {
        return false;
    }
    bool validMove = false;
    if (board.clearDiagPath(*(location()), dest)) {
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