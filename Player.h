#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"
#include "King.h"
#include <string>
#include <set>

class Player {
    public:
        Player(std::string name, bool isWhite, std::set<Piece*>& pieces, King & king);
        ~Player();

        bool makeMove();
        bool inCheck();

        void capture(Piece *piece);

        std::string getName();
        bool isPlayerWhite();

        std::set<Piece*> * myPieces();
        King * myKing();


    private:
        std::string name;
        bool isWhite;
        std::set<Piece*>& pieces;
        King & king;

};

#endif
