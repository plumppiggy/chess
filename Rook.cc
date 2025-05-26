#include "Rook.h"

using namespace std;

Rook::Rook(bool isWhite) : Piece(isWhite) {}

Rook::~Rook() {}

bool Rook::canMoveTo(ChessBoard &board, Square& dest) {
    if (!location()) {
        std::cerr << "DEBUG: Rook has no current location. Returning false." << std::endl;
        return false;
    }

    auto piece = dest.occupiedBy();
    if (piece && piece->isPieceWhite() == isPieceWhite()) {
        return false;
    }

    if (dest == *(location())) {
        return false;
    }

    bool validMove = false;

    if (board.clearHorPath(*(location()), dest)) {
        validMove = true;
    }

    if (board.clearVertPath(*(location()), dest)) {
        validMove = true;
    }

    if (!validMove) {
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