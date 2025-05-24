#ifndef BISHOP_H
#define BISHOP_H

#include "Square.h"
#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(bool isWhite);

        ~Bishop();

        bool canMoveTo(Square &location);

        void display();

        double getValue() const override {
            return 3.0;
        }

};
#endif