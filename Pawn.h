#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "Piece.h"
#include "Square.h"

class Pawn : public Piece {
    public:
        Pawn(bool isWhite);
        Pawn(const Pawn& other) : Piece(other), moved(other.moved) {}
        ~Pawn();
        void setLocation(Square *location);
        bool canMoveTo(ChessBoard &board, Square &dest) override;
        void display();

        bool hasMoved();

        double getValue() const override {
            return 1.0;
        }

        Piece* clone() const override {
            return new Pawn(*this);
        }
    private:
        bool moved;
};

#endif