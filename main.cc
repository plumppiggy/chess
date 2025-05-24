#include <iostream>

#include <memory> 
#include "game.h"
#include "ChessPlayer.h"
#include "AIPlayer.h"
#include "ChessBoard.h"
#include "InputReader.h"
#include "Player.h"


int main () {
    ChessPlayer* player1;
    ChessPlayer* player2;
    Game game;

    std::cout << "Choose a game mode: " << std::endl;
    std::cout << "1. Player vs Player" << std::endl;
    std::cout << "2. Player vs AI" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        player1 = new Player("White", true);
        player2 = new Player("Black", false);
    } else if (choice == 2) {
        player1 = new Player("White", true);
        player2 = new AIPlayer();
    } else {
        std::cerr << "Invalid choice" << std::endl;
        return 1;
    }
    game.initialize(player1, player2);
    ChessBoard::getBoard()->display(std::cout);

    ChessPlayer* cur = player1;
    InputReader inputReader;
    while (true) {
        std::cout << cur->getName() << "'s turn" << std::endl;
        Move move;
        if (cur->getName() == "AI Player") {
            move = cur->getMove(game);
            std::cout << "AI chose move: (" << move.from_x << ", " << move.from_y << ") to (" 
                      << move.to_x << ", " << move.to_y << ")" << std::endl;
        } else {
            move = inputReader.ReadMove();

        }

        if (!game.MakeMove(*cur, move)) {
            std::cerr << "Invalid move, please try again." << std::endl;
            continue;
        }
        ChessBoard::getBoard()->display(std::cout);

        cur = (cur == player1) ? player2 : player1;
    }

}