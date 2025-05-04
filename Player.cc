#include <iostream>
#include <string>
#include "Player.h"
#include "ChessBoard.h"
#include "Game.h"

using namespace std;

Player::Player(string name, bool isWhite, set<Piece *> & myPieces, King &king) : 
        name{name}, isWhite{isWhite}, pieces{myPieces}, king{king} {}

Player::~Player() {}

bool Player::makeMove(Move move) {
    return ChessBoard::getBoard()->squareAt(move.from_x, move.from_y)->occupiedBy()->move
                        (*this, *(ChessBoard::getBoard()->squareAt(move.to_x, move.to_y)));

}

bool Player::inCheck() {
    return false;

    for (auto it: Game::opponent(*this)->pieces) {
        if (it->location() && it->canMoveTo(*(king.location()))) {
            return true;
        }
    }

    return false;
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

