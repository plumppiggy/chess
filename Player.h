#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"
#include "King.h"
#include "InputReader.h"
#include "ChessPlayer.h"
#include <string>
#include <set>

class Player : public ChessPlayer {
    public:
        Player(std::string name, bool isWhite, std::set<Piece*>& pieces, King & king);
        ~Player();

        bool makeMove(Move move) override;
        bool inCheck(Game &game) override;

        void capture(Piece *piece) override;

        std::string getName() override;
        bool isPlayerWhite() override;

        std::set<Piece*> * myPieces() override;
        King * myKing() override;


    private:
        std::string name;
        bool isWhite;
        std::set<Piece*>& pieces;
        King & king;

};

#endif
