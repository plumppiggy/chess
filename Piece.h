#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <optional>
#include "Square.h"
#include "ChessBoard.h"

class ChessPlayer;

class Piece {
    public:
        Piece(bool isWhite);
        Piece(const Piece& other) : isWhite(other.isWhite), square(other.square) {}
        virtual ~Piece();
    
        virtual std::optional<Piece*> move(ChessPlayer &byPlayer, Square & dest);
        virtual void setLocation(Square * location);
    
        bool isPieceWhite() const;
    
        virtual bool canMoveTo(ChessBoard &board, Square& location) = 0;
    
        bool isOnSquare();
    
        Square* location();
        void revertMove(Square *origin, Square &dest, Piece *capture = nullptr);

        virtual void display() = 0;

        virtual double getValue() const = 0;
        virtual Piece* clone() const = 0;

    protected:
        bool isWhite;
    
    private:
        Square* square;
};

#endif