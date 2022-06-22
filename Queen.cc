#include "Queen.h"
#include <iostream>

using namespace std;

Queen::Queen(bool isWhite) : Piece{isWhite} {}

Queen::~Queen() {}


bool Queen::canMoveTo(Square &dest) {
    bool valid = false;

    if (ChessBoard::getBoard()->clearDiagPath(*(location()), dest)) {
        valid = true;
    } else if (ChessBoard::getBoard()->clearHorPath(*(location()), dest)) {
        valid = true;
    } else if (ChessBoard::getBoard()->clearVertPath(*(location()), dest)) {
        valid = true;
    }
    return valid;

}

void Queen::display() {
    if (isWhite) {
        cout << "Q";
    } else {
        cout << "q";
    }
}