
#pragma once

#include <string>
#include <set>
#include "Piece.h"
#include "King.h"
#include "Move.h"

class Game;

class ChessPlayer {
  public: 
        virtual bool makeMove(Move move) = 0;
        virtual bool inCheck(Game& game) = 0;

        virtual void capture(Piece *piece) = 0;

        virtual std::string getName() = 0;
        virtual bool isPlayerWhite() = 0;

        virtual std::set<Piece*> * myPieces() = 0;
        virtual King * myKing() = 0;

        virtual Move getMove() {}
};
