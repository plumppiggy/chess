#include "Game.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Horse.h"
#include "Rook.h"
#include "Pawn.h"
#include "Square.h"

using namespace std;


Game::Game() {}

Game::~Game() {

    for (set<Piece*>::iterator it = whiteP.begin(); it != whiteP.end(); it++) {
        delete *it;
    }
    for (auto it : blackP) {
        delete it;
    }
    whiteP.clear();
    blackP.clear();

    delete &player1;
    delete &player2;
}

void Game::initialize() {
    Piece *aPiece;
    King * aKing;
    Square *aSquare;

    whiteP = *(new set<Piece*>);
    blackP = *(new set<Piece*>);

    // queens
    aPiece = new Queen(true);
    aSquare = ChessBoard::getBoard()->squareAt(3,0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Queen(false);
    aSquare = ChessBoard::getBoard()->squareAt(3,7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // bishops
    aPiece = new Bishop(true);
    aSquare = ChessBoard::getBoard()->squareAt(2, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Bishop(true);
    aSquare = ChessBoard::getBoard()->squareAt(5, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Bishop(false);
    aSquare = ChessBoard::getBoard()->squareAt(2, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Bishop(false);
    aSquare = ChessBoard::getBoard()->squareAt(5, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // horses
    aPiece = new Horse(true);
    aSquare = ChessBoard::getBoard()->squareAt(1, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Horse(true);
    aSquare = ChessBoard::getBoard()->squareAt(6, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Horse(false);
    aSquare = ChessBoard::getBoard()->squareAt(1, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Horse(false);
    aSquare = ChessBoard::getBoard()->squareAt(6, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // rooks
    aPiece = new Rook (true);
    aSquare = ChessBoard::getBoard()->squareAt(0, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Rook(true);
    aSquare = ChessBoard::getBoard()->squareAt(7, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Rook(false);
    aSquare = ChessBoard::getBoard()->squareAt(0, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Rook(false);
    aSquare = ChessBoard::getBoard()->squareAt(7, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    for (int i = 0; i < 8; i++) {
        aPiece = new Pawn(true);
        aSquare = ChessBoard::getBoard()->squareAt(i, 1);
        aSquare->setPiece(aPiece);
        aPiece->setLocation(aSquare);
        whiteP.insert(aPiece);

        aPiece = new Pawn(false);
        aSquare = ChessBoard::getBoard()->squareAt(i , 6);
        aSquare->setPiece(aPiece);
        aPiece->setLocation(aSquare);
        blackP.insert(aPiece);
    }

    aKing = new King(true);
    aSquare = ChessBoard::getBoard()->squareAt(4, 0);
    aSquare->setPiece(aKing);
    aKing->setLocation(aSquare);
    whiteP.insert(aKing);

    player1 = new Player("White", true, whiteP, *aKing);

    aKing = new King(false);
    aSquare = ChessBoard::getBoard()->squareAt(4,7);
    aSquare->setPiece(aKing);
    aKing->setLocation(aSquare);
    blackP.insert(aKing);

    player2 = new Player("Black", false ,blackP, *aKing);

    nextPlayer = player2;

}

Player * Game::getPlayer() {
    nextPlayer = opponent(*nextPlayer);
    return nextPlayer;
}

Player * Game::opponent(Player & player) {
    Player * opponent;
    if (player.getName() == player1->getName()) {
        opponent = player2;
    } else {
        opponent = player1;
    }
    return opponent;
}

Player* Game::player1;
Player* Game::player2;
Player* Game::nextPlayer;
std::set<Piece*> Game::whiteP;
std::set<Piece*> Game::blackP;