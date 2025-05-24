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
}

Player* Game::getPlayer(int player_id) {
    if (player_id == 1) {
        return player1;
    } else if (player_id == 2) {
        return player2;
    } else {
        return nullptr;
    }
}

Player* Game::opponent(Player& player) {
    Player* opponent;
    if (player.getName() == player1->getName()) {
        opponent = player2;
    } else {
        opponent = player1;
    }
    return opponent;
}

bool Game::MakeMove(ChessPlayer& player, Move move) {
    std::cout << "DEBUG: Starting MakeMove for player: " << player.getName() << std::endl;
    std::cout << "DEBUG: Move from (" << move.from_x << ", " << move.from_y << ") to ("
              << move.to_x << ", " << move.to_y << ")" << std::endl;

    // Get the origin and destination squares
    Square* origin = ChessBoard::getBoard()->squareAt(move.from_x, move.from_y);
    Square* dest = ChessBoard::getBoard()->squareAt(move.to_x, move.to_y);

    if (!origin) {
        std::cerr << "ERROR: Origin square is invalid or out of bounds." << std::endl;
        return false;
    }
    if (!dest) {
        std::cerr << "ERROR: Destination square is invalid or out of bounds." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Origin square and destination square retrieved successfully." << std::endl;

    // Get the piece at the origin square
    Piece* piece = origin->occupiedBy();
    if (!piece) {
        std::cerr << "ERROR: No piece at the origin square (" << move.from_x << ", " << move.from_y << ")." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Piece at origin square is " << (piece->isPieceWhite() ? "White" : "Black") << " piece." << std::endl;

    // Check if the piece belongs to the current player
    if (piece->isPieceWhite() != player.isPlayerWhite()) {
        std::cerr << "ERROR: Player " << player.getName() << " cannot move this piece." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Piece belongs to the current player." << std::endl;

    // Check if the piece can move to the destination square
    if (!piece->canMoveTo(*dest)) {
        std::cerr << "ERROR: Piece cannot move to the destination square (" << move.to_x << ", " << move.to_y << ")." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Piece can move to the destination square." << std::endl;

    // Perform the move
    if (!piece->move(player, *dest)) {
        std::cerr << "ERROR: Move failed during execution." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Move executed successfully." << std::endl;

    // Check if the move puts the player's king in check
    if (player.inCheck(*this)) {
        std::cerr << "ERROR: Move puts the king in check. Reverting move." << std::endl;
        // Revert the move (if necessary, implement revert logic in Piece::move)
        return false;
    }

    std::cout << "DEBUG: Move completed successfully without putting the king in check." << std::endl;

    return true;
}
