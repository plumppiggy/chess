#include <iostream>
#include <string>
#include "Player.h"
#include "ChessBoard.h"
#include "Game.h"

using namespace std;

Player::Player(string name, bool isWhite) : 
        name{name}, isWhite{isWhite} {}

Player::~Player() {}


bool Player::inCheck(Game& game) {

    std::cout << "DEBUG: Checking if player " << getName() << " is in check." << std::endl;

    // Get the location of the player's king
    Square* kingSquare = king->location();
    if (!kingSquare) {
        std::cerr << "ERROR: King's location is not set for player " << getName() << "." << std::endl;
        return false;
    }

    std::cout << "DEBUG: King's location is at (" << kingSquare->getX() << ", " << kingSquare->getY() << ")." << std::endl;

    // Get the opponent's pieces
    auto opponentPieces = game.opponent(*this)->myPieces();
    if (opponentPieces.empty()) {
        std::cout << "DEBUG: Opponent has no pieces. Player " << getName() << " cannot be in check." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Opponent has " << opponentPieces.size() << " pieces." << std::endl;

    // Iterate through all opponent pieces
    for (auto it = opponentPieces.begin(); it != opponentPieces.end(); ++it) {
        Piece* opponentPiece = *it;
        if (!opponentPiece) {
            std::cerr << "ERROR: Found a null opponent piece in the opponent's pieces set." << std::endl;
            continue;
        }

        Square* opponentLocation = opponentPiece->location();
        if (!opponentLocation) {
            std::cerr << "DEBUG: Opponent piece has no location. Skipping this piece." << std::endl;
            continue;
        }

        std::cout << "DEBUG: Checking opponent piece at (" << opponentLocation->getX() << ", " << opponentLocation->getY() << ")." << std::endl;

        // Check if the opponent piece can move to the king's square
        if (opponentPiece->canMoveTo(game.getBoard(), *kingSquare)) {
            std::cout << "DEBUG: Opponent piece at (" << opponentLocation->getX() << ", " << opponentLocation->getY()
                      << ") can move to the king's square (" << kingSquare->getX() << ", " << kingSquare->getY() << ")." << std::endl;
            std::cout << "Player " << getName() << " is in check by "
                      << (opponentPiece->isPieceWhite() ? "white" : "black") << " piece." << std::endl;
            return true;
        }
    }

    std::cout << "DEBUG: No opponent pieces can move to the king's square. Player " << getName() << " is not in check." << std::endl;
    return false;
}

void Player::capture(Piece * p) {
    pieces.erase(p);
}

string Player::getName() {
    std::cout << "DEBUG: Player's name is " << name << "." << std::endl;
    return name;
}

bool Player::isPlayerWhite() {
    return isWhite;
}

set<Piece*> Player::myPieces() {
    return pieces;
}

King* Player::myKing() {
    return king;
}

