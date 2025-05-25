#include "Queen.h"
#include <iostream>

using namespace std;

Queen::Queen(bool isWhite) : Piece{isWhite} {}

Queen::~Queen() {}

bool Queen::canMoveTo(ChessBoard &board, Square &dest) {
    std::cout << "DEBUG: Queen::canMoveTo called for destination (" 
              << dest.getX() << ", " << dest.getY() << ")" << std::endl;

    if (!location()) {
        std::cerr << "DEBUG: Queen has no current location. Returning false." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Queen current location is (" 
              << location()->getX() << ", " << location()->getY() << ")" << std::endl;

    if (dest == *(location())) {
        std::cerr << "DEBUG: Destination is the same as the current location. Returning false." << std::endl;
        return false;
    }

    bool valid = false;

    if (board.clearDiagPath(*(location()), dest)) {
        std::cout << "DEBUG: Diagonal path is clear from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << ")." << std::endl;
        valid = true;
    } else if (board.clearHorPath(*(location()), dest)) {
        std::cout << "DEBUG: Horizontal path is clear from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << ")." << std::endl;
        valid = true;
    } else if (board.clearVertPath(*(location()), dest)) {
        std::cout << "DEBUG: Vertical path is clear from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << ")." << std::endl;
        valid = true;
    }

    if (!valid) {
        std::cerr << "DEBUG: No valid path for queen from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << "). Returning false." << std::endl;
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