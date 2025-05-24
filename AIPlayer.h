#pragma once

#include "ChessPlayer.h"
#include "Move.h"

class AIPlayer : public ChessPlayer {
   public:
    AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king);
    AIPlayer();

    bool makeMove(Move move) override;
    bool inCheck(Game &game) override;
    void capture(Piece* piece) override;
    std::string getName() override;
    bool isPlayerWhite() override;
    std::set<Piece*>* myPieces() override;
    King* myKing() override;

private:
    std::string name;
    bool isWhite;
    std::set<Piece*> pieces;
    King* king;
};