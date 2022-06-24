#ifndef HORSE_H
#define HORSE_H

#include "Piece.h"
#include "Square.h"

class Horse : public Piece {
    public: 
        Horse(bool isWhite);
        ~Horse();
        bool canMoveTo(Square & dest);
        void display();

};

#endif