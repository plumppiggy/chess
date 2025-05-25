#ifndef QUEEN_H
#define QUEEN_H

#include "Square.h"
#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(bool isWhite);

        ~Queen();

        bool canMoveTo(ChessBoard &board, Square &location);

        void display();

        double getValue() const override {
            return 9.0;
        }

        Piece* clone() const override {
            return new Queen(*this);
        }

};
#endif