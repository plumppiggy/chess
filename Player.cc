#include <iostream>
#include <string>
#include "Player.h"
#include "ChessBoard.h"
#include "Game.h"

using namespace std;

Player::Player(string name, bool isWhite, set<Piece *> & myPieces, King &king) : 
        name{name}, isWhite{isWhite}, pieces{myPieces}, king{king} {}

Player::~Player() {}

bool Player::makeMove() {
    string from = "";
    string to = "";
    int fromX, fromY, toX, toY;
    if (inCheck()) {
        cout << name << " is in check" << endl;
    }
    cout << name << " enter a move (ex b2 b3)";
    cin >> from >> to;
    while (from.length() != 2 || to.length() != 2 || from.at(0) < 'a' || from.at(0) > 'h' || to.at(0) < 'a'
            || to.at(0) > 'h' || from.at(1) < '1'|| from.at(1) > '8' || to.at(1) > '8' || to.at(1) < '1' ||
            !(ChessBoard::getBoard()->squareAt(from.at(0) - 'a', from.at(1) - '1')->occupied())) {
                cerr << "Invalid move" << endl;
                cin.clear();
                cin.ignore();
                cout << name << " enter a move (ex b3 b2)";
                cin >> from >> to;
    }

    fromX = tolower(from.at(0) - 'a');
    fromY = from.at(1) - '1';
    toX = tolower(to.at(0) - 'a');
    toY = to.at(1) - '1';

    //cout << fromX << fromY << toX << toY << endl;

    return ChessBoard::getBoard()->squareAt(fromX, fromY)->occupiedBy()->move
                        (*this, *(ChessBoard::getBoard()->squareAt(toX, toY)));

}

bool Player::inCheck() {
    return false;

    // for (auto it: Game::opponent(*this)->pieces) {
    //     if (it->location() && it->canMoveTo(*(king.location()))) {
    //         return true;
    //     }
    // }

    // return false;
}

void Player::capture(Piece * p) {
    Game::opponent(*this)->pieces.erase(p);
    p->setLocation(nullptr);
}

string Player::getName() {
    return name;
}

bool Player::isPlayerWhite() {
    return isWhite;
}

set<Piece*> * Player::myPieces() {
    return &pieces;
}

King * Player::myKing() {
    return &king;
}

