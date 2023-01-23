#include <iostream>
#include "game.h"
#include "ChessBoard.h"

using namespace std;

int main () {
    Player * cur = nullptr;
    Game::initialize();
    ChessBoard::getBoard()->display(cout);

    while (true) {
        cur = Game::getPlayer();
        while (!cur->makeMove()) {
            cerr << "Invalid move, please try again" << endl;
        }
        ChessBoard::getBoard()->display(cout);
    }

}