#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "ChessBoard.h"

class Rook : public Piece {
    public:
        Rook(bool isWhite);

        ~Rook();

        bool canMoveTo(Square &location);

        void display();
        double getValue() const override {
            return 5.0;
        }

};

#endif
