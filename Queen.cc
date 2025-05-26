#include "Queen.h"
#include <iostream>

using namespace std;

Queen::Queen(bool isWhite) : Piece{isWhite} {}

Queen::~Queen() {}

bool Queen::canMoveTo(ChessBoard &board, Square &dest) {

    if (!location()) {
        std::cerr << "DEBUG: Queen has no current location. Returning false." << std::endl;
        return false;
    }

    if (dest == *(location())) {
        std::cerr << "DEBUG: Destination is the same as the current location. Returning false." << std::endl;
        return false;
    }

    auto piece = dest.occupiedBy();
    if (piece && piece->isPieceWhite() == isPieceWhite()) {
        return false;
    }

    bool valid = false;

    if (board.clearDiagPath(*(location()), dest)) {
        valid = true;
    } else if (board.clearHorPath(*(location()), dest)) {
        valid = true;
    } else if (board.clearVertPath(*(location()), dest)) {
        valid = true;
    }

    if (!valid) {
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