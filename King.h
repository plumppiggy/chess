#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece{
    public:
        King(bool isWhite);
        ~King();
        bool canMoveTo(Square & location);
        void display();
};

#endif