#include "Piece.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Piece::Piece(bool isWhite) : isWhite{isWhite}, square{nullptr} {}

Piece::~Piece() {}


bool Piece::move(ChessPlayer& byPlayer, Square& dest) {
    if (!square) {
      std::cerr << "Error: Piece is not on a square." << std::endl;
      return false;
    }
  
    // Handle capture
    Piece* capture = nullptr;
    if (dest.occupied()) {
      capture = dest.occupiedBy();
      capture->setLocation(nullptr);
    }
  
    // Perform the move
    square->setPiece(nullptr);
    square = &dest;
    square->setPiece(this);
  
    // Notify the player of the capture
    if (capture) {
      byPlayer.capture(capture);
    }
  
    return true;
  }

void Piece::revertMove(Square *origin, Square &dest, Piece *capture) {
    square = origin;
    square->setPiece(this);
    dest.setPiece(capture);

    if (capture) {
        capture->setLocation(&dest);
    }
}

void Piece::setLocation(Square *location) {
    square = location;
}

bool Piece::isPieceWhite() const {
    return isWhite;
}

bool Piece::isOnSquare() {
    return square;
}

Square * Piece::location() {
    return square;
}




