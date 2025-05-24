#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "Piece.h"
#include "Square.h"

class Pawn : public Piece {
    public:
        Pawn(bool isWhite);
        ~Pawn();
        void setLocation(Square *location);
        bool canMoveTo(Square &dest);
        void display();

        bool hasMoved();

        double getValue() const override {
            return 1.0;
        }
    private:
        bool moved;
};

#endif