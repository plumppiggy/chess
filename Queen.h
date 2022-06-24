#ifndef QUEEN_H
#define QUEEN_H

#include "Square.h"
#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(bool isWhite);

        ~Queen();

        bool canMoveTo(Square &location);

        void display();

};
#endif