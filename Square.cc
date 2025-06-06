#include "Square.h"
#include "Player.h"

using namespace std;

Square::Square(int x, int y) : x{x}, y{y}, piece{nullptr} {}

Square::~Square() {}

void Square::setPiece(Piece * _piece) {
    piece = _piece;
}

int Square::getX() {
    return x;
}

int Square::getY() {
    return y;
}

bool Square::occupied() {
    return piece != nullptr;
}

Piece* Square::occupiedBy() {
    return piece;
}

