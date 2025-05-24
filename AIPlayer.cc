#include "AIPlayer.h"
#include <iostream>

AIPlayer::AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king)
    : name(name), isWhite(isWhite), pieces(pieces), king(&king) {}
AIPlayer::AIPlayer() 
    : name("AI Player"), isWhite(true), king(nullptr) {
    // Default constructor initializes with default values
}
bool AIPlayer::makeMove(Move move) {
    return true;
}

bool AIPlayer::inCheck(Game &game) {
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