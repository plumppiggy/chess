#pragma once

#include "ChessPlayer.h"
#include "Move.h"

class AIPlayer : public ChessPlayer {
   public:
    AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king);
    AIPlayer();

    bool inCheck(Game &game) override;
    void capture(Piece* piece) override;
    std::string getName() override;
    bool isPlayerWhite() override;
    std::set<Piece*> myPieces() override;
    King* myKing() override;
    Move getMove(Game &game) override;

    void SetPieces(std::set<Piece*> &pieces) override {
        this->pieces = pieces;
    }

    void SetKing(King* king) override {
        this->king = king;
    }

    ChessPlayer* Clone() const override {
        std::set<Piece*> newPieces;
    for (Piece* piece : pieces) {
        newPieces.insert(piece->clone()); // Assuming each Piece has a clone() method
    }

    King* newKing = static_cast<King*>(king->clone()); // Assuming King has a clone() method

    return new AIPlayer(name, isWhite, newPieces, *newKing);
    }

private:

    double mini_max(int depth, Game &game, double alpha, double beta, bool isMaximisingPlayer);
    double evaluate_board(Game &game);
    std::string name;
    bool isWhite;
    std::set<Piece*> pieces;
    King* king;
};