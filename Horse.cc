#include "Horse.h"

using namespace std;

Horse::Horse(bool isWhite) : Piece{isWhite} {}

Horse::~Horse() {}

bool Horse::canMoveTo(ChessBoard &board, Square &dest) {
    if (dest == *(location())) {
        return false;
    }
    int x = location()->getX() - dest.getX();
    int y = location()->getY() - dest.getY();

    if (abs(y) == 2 && abs(x) == 1) {
        return true;
    }

    if (abs(x) == 2 && abs(y) == 1) {
        return true;
    }

    return false;

}

void Horse::display() {
    if (isWhite) {
        cout << "H";
    } else {
        cout << "h";
    }
}

