#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "Piece.h"
#include <set>
#include <iostream>

class Game {
    public:
        Game();
        ~Game();
        void initialize();

        Player* getPlayer(int player_id);

        Player* opponent(Player & player);
        bool MakeMove(ChessPlayer& player, Move move);


    private:
        Player* player1;
        Player* player2;
        std::set<Piece*> whiteP;
        std::set<Piece*> blackP;


};

#endif