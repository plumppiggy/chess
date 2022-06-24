#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "Piece.h"
#include <set>
#include <iostream>

class Game {
    public:
        ~Game();
        static void initialize();

        static Player* getPlayer();

        static Player* opponent(Player & player);

    private:
        Game();
        static Player* player1;
        static Player* player2;
        static Player* nextPlayer;
        static std::set<Piece*> whiteP;
        static std::set<Piece*> blackP;


};

#endif