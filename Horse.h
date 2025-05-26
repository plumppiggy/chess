#ifndef HORSE_H
#define HORSE_H

#include "Piece.h"
#include "Square.h"

class Horse : public Piece {
    public: 
        Horse(bool isWhite);
        Horse(const Horse& other) : Piece(other) {}
        ~Horse();
        bool canMoveTo(ChessBoard &board, Square & dest) override;
        void display();

        double getValue() const override {
            return 3.0;
        }

        Piece* clone() const override {
            return new Horse(*this);
        }

};

#endif