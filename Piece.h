#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include "Square.h"
#include "ChessBoard.h"

class Player;

class Piece {
    public:
        Piece(bool isWhite);
        virtual ~Piece();
    
        virtual bool move(Player &byPlayer, Square & dest);
        virtual void setLocation(Square * location);
    
        bool isPieceWhite() const;
    
        virtual bool canMoveTo(Square& location) = 0;
    
        bool isOnSquare();
    
        Square* location();

        virtual void display() = 0;

    protected:
        bool isWhite;
    
    private:
        Square * square;
};

#endif