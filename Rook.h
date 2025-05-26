#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "ChessBoard.h"

class Rook : public Piece {
    public:
        Rook(bool isWhite);
        Rook(const Rook& other) : Piece(other) {
        }

        ~Rook();

        bool canMoveTo(ChessBoard &board, Square &location) override;

        void display();
        double getValue() const override {
            return 5.0;
        }

        Piece* clone() const override {
            return new Rook(*this);
        }

};

#endif
