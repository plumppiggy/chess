#include "Pawn.h"
#include "ChessBoard.h"

using namespace std;

Pawn::Pawn(bool isWhite) : Piece{isWhite}, moved{false} {}

Pawn::~Pawn() {}

void Pawn::setLocation(Square* location) {
    Piece::setLocation(location);
}

bool Pawn::canMoveTo(Square & dest) {
    int x = dest.getX() - location()->getX();
    int y = dest.getY() - location()->getY();
    if (!isWhite) {
        x *= -1;
        y *= -1;
    }
    if (!dest.occupied() && y == 1 && x == 0) {
        return true;
    } else if (!hasMoved() && y == 2 && x == 0 && (ChessBoard::getBoard()->clearVertPath(*(location()), dest))) {
        return true;
    } else if (dest.occupied() && y == 1 && (x == 1 || x == -1)) {
        return true;
    }
    return false;
}

bool Pawn::hasMoved() {
    return moved;
}

void Pawn::display() {
    if (isWhite) {
        cout << "P";
    } else {
        cout << "p";
    }
}
