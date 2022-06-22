#include "Piece.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Piece::Piece(bool isWhite) : isWhite{isWhite}, square{nullptr} {}

Piece::~Piece() {}

bool Piece::move(Player &byPlayer, Square & dest) {
    bool valid = false;
    Piece *capture = nullptr;
    Square *origin = square;

    if (isWhite == byPlayer.isPlayerWhite()) {
        if (canMove(dest)) {
            if (dest.occupied()) {
                capture = dest.occupiedBy();

                if (capture->isPieceWhite() != byPlayer.isPlayerWhite()) {
                    valid = true;
                }
            } else {
                valid = true;
            }

            if (valid) {
                if (capture) {
                    capture->setLocation(nullptr);
                }
                square->setPiece(nullptr);
                square->setPiece(this);

                if (byPlayer.inCheck()) {
                    valid = false;

                    square = origin;
                    square->setPiece(this);
                    dest.setPiece(capture);

                    if (capture) {
                        capture->setLocation(&dest);
                    }
                } else {
                    if (capture) {
                        byPlayer.capture(capture);
                    }
                }

                
            }
        }
    }

    return valid;
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


