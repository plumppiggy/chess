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
    Move getMove(Game &game) override;

    void SetPieces(std::set<Piece*> &pieces) override {
        this->pieces = pieces;
    }

    void SetKing(King* king) override {
        this->king = king;
    }

private:

    double mini_max(int depth, Game &game, double alpha, double beta, bool isMaximisingPlayer);
    double evaluate_board(Game &game);
    std::string name;
    bool isWhite;
    std::set<Piece*> pieces;
    King* king;
};