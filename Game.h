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
        void initialize(ChessPlayer* player1, ChessPlayer* player2);

        Player* getPlayer(int player_id);

        Player* opponent(Player & player);
        bool MakeMove(ChessPlayer& player, Move move);

        std::vector<Move> generateMoves(Player& player);


    private:
        Player* player1;
        Player* player2;
        std::set<Piece*> whiteP;
        std::set<Piece*> blackP;


};

#endif