#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece{
    public:
        King(bool isWhite);
        King(const King& other) : Piece(other) {}
        ~King();
        bool canMoveTo(ChessBoard &board, Square & location) override;
        void display();

        double getValue() const override {
            return 1000.0;
        }

        Piece* clone() const override {
            return new King(*this);
        }
};

#endif