#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "Piece.h"
#include <set>
#include <iostream>
#include <vector>

class Game {
    public:
        Game();
        ~Game();

        Game(const Game& other);
        void initialize(ChessPlayer* player1, ChessPlayer* player2);

        ChessPlayer* getPlayer(int player_id);

        ChessPlayer* opponent(ChessPlayer & player);
        bool MakeMove(ChessPlayer& player, Move move);

        std::vector<Move> generateMoves(ChessPlayer& player);
        bool inCheck(ChessPlayer& player);

        ChessBoard& getBoard() {
            return board;
        }


    private:
        ChessPlayer* player1;
        ChessPlayer* player2;
        ChessBoard board;


};

#endif