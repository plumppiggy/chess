#ifndef BISHOP_H
#define BISHOP_H

#include "Square.h"
#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(bool isWhite);
        Bishop(const Bishop& other) : Piece(other) {}

        ~Bishop();

        bool canMoveTo(ChessBoard &board, Square &location) override;

        void display();

        double getValue() const override {
            return 3.0;
        }

        Piece* clone() const override {
            return new Bishop(*this);
        }

};
#endif