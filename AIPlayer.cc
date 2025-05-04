#include "AIPlayer.h"
#include <iostream>

AIPlayer::AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king)
    : name(name), isWhite(isWhite), pieces(pieces), king(&king) {}

bool AIPlayer::makeMove() {
    return true;
}

bool AIPlayer::inCheck() {
    std::cout << name << " is checking if it's in check..." << std::endl;
    return false;
}

void AIPlayer::capture(Piece* piece) {
    std::cout << name << " captured a piece!" << std::endl;
    pieces.erase(piece);
}

std::string AIPlayer::getName() {
    return name;
}

bool AIPlayer::isPlayerWhite() {
    return isWhite;
}

std::set<Piece*>* AIPlayer::myPieces() {
    return &pieces;
}

King* AIPlayer::myKing() {
    return king;
}