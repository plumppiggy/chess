#include "Rook.h"

using namespace std;

Rook::Rook(bool isWhite) : Piece(isWhite) {}

Rook::~Rook() {}

bool Rook::canMoveTo(ChessBoard &board, Square& dest) {
    std::cout << "DEBUG: Rook::canMoveTo called for destination (" 
              << dest.getX() << ", " << dest.getY() << ")" << std::endl;

    if (!location()) {
        std::cerr << "DEBUG: Rook has no current location. Returning false." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Rook current location is (" 
              << location()->getX() << ", " << location()->getY() << ")" << std::endl;

    if (dest == *(location())) {
        std::cerr << "DEBUG: Destination is the same as the current location. Returning false." << std::endl;
        return false;
    }

    bool validMove = false;

    if (board.clearHorPath(*(location()), dest)) {
        std::cout << "DEBUG: Horizontal path is clear from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << ")." << std::endl;
        validMove = true;
    }

    if (board.clearVertPath(*(location()), dest)) {
        std::cout << "DEBUG: Vertical path is clear from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << ")." << std::endl;
        validMove = true;
    }

    if (!validMove) {
        std::cerr << "DEBUG: No valid path for rook from (" << location()->getX() << ", " << location()->getY()
                  << ") to (" << dest.getX() << ", " << dest.getY() << "). Returning false." << std::endl;
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