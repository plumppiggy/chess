#include "King.h"
#include <iostream>
using namespace std;

King::King(bool isWhite) : Piece(isWhite) {}

King::~King() {}

bool King::canMoveTo(ChessBoard &board, Square & dest) {
    if (dest == *(location())) {
        return false;
    }
    int x = dest.getX();
    int y = dest.getY();

    int kx = location()->getX();
    int ky = location()->getY();

    int absx = abs(x - kx);
    int absy = abs(y - ky);

    if ((absx == 1 && absy == 1) || (absx == 0 && absy == 1) || (absx == 1 && absy == 0)) {
        return true;
    }

    return false;
}

void King::display() {
    if (isWhite) {
        cout << "K";
    } else {
        cout <<"k";
    }
}
