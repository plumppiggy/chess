#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Square.h"
#include <iostream>


class ChessBoard {
    private:
        
        bool whiteTurn = true;
        bool inCheck = false;
        bool endGame = false;

        static const int DIMENSION = 8;
        Square * squares[DIMENSION][DIMENSION];
        

        bool validGame(); // can the game keep going?


    public:
        ChessBoard();
        ~ChessBoard();
        ChessBoard(const ChessBoard& other);

        Square * squareAt(int x, int y);

        bool clearVertPath(Square & origin, Square & end);
        bool clearHorPath(Square & origin, Square & end);
        bool clearDiagPath(Square &origin, Square &end);

        void display(std::ostream & out);


    
};

#endif