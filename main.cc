#include <iostream>

#include <memory> 
#include "game.h"
#include "AIPlayer.h"
#include "ChessBoard.h"
#include "InputReader.h"
#include "Player.h"
#include "ChessPlayer.h"


int main () {
    ChessPlayer* player1;
    ChessPlayer* player2;

    Game::initialize();

    std::cout << "Choose a game mode: " << std::endl;
    std::cout << "1. Player vs Player" << std::endl;
    std::cout << "2. Player vs AI" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        player1 = Game::getPlayer(1);
        player2 = Game::getPlayer(2);
    } else if (choice == 2) {
        player1 = Game::getPlayer(1);
        player2 = new AIPlayer();
    } else if (choice == 2) {
    } else {
        std::cerr << "Invalid choice" << std::endl;
        return 1;
    }
    ChessBoard::getBoard()->display(std::cout);

    ChessPlayer* cur = player1;
    InputReader inputReader;
    while (true) {
        std::cout << cur->getName() << "'s turn" << std::endl;
        Move move = inputReader.ReadMove();
        while (!cur->makeMove(move)) {
            std::cerr << "Invalid move, please try again" << std::endl;
        }
        ChessBoard::getBoard()->display(std::cout);

        cur = (cur == player1) ? player2 : player1;
    }

}