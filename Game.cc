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
}

Game::Game(const Game& other) : board(other.board) {
    this->player1 = other.player1->Clone();
    this->player2 = other.player2->Clone();

    for (Piece* piece : player1->myPieces()) {
        Square* newSquare = board.squareAt(piece->location()->getX(), piece->location()->getY());
        newSquare->setPiece(piece);
        piece->setLocation(newSquare);
    }

    for (Piece* piece : player2->myPieces()) {
        Square* newSquare = board.squareAt(piece->location()->getX(), piece->location()->getY());
        newSquare->setPiece(piece);
        piece->setLocation(newSquare);
    }
}

void Game::initialize(ChessPlayer* player1, ChessPlayer* player2) {
    Piece *aPiece;
    King * aKing;
    Square *aSquare;

    std::set<Piece*> whiteP;
    std::set<Piece*> blackP;

    // queens
    aPiece = new Queen(true);
    aSquare = board.squareAt(3,0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Queen(false);
    aSquare = board.squareAt(3,7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // bishops
    aPiece = new Bishop(true);
    aSquare = board.squareAt(2, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Bishop(true);
    aSquare = board.squareAt(5, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Bishop(false);
    aSquare = board.squareAt(2, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Bishop(false);
    aSquare = board.squareAt(5, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // horses
    aPiece = new Horse(true);
    aSquare = board.squareAt(1, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Horse(true);
    aSquare = board.squareAt(6, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Horse(false);
    aSquare = board.squareAt(1, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Horse(false);
    aSquare = board.squareAt(6, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    // rooks
    aPiece = new Rook (true);
    aSquare = board.squareAt(0, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);
    aPiece = new Rook(true);
    aSquare = board.squareAt(7, 0);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    whiteP.insert(aPiece);

    aPiece = new Rook(false);
    aSquare = board.squareAt(0, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);
    aPiece = new Rook(false);
    aSquare = board.squareAt(7, 7);
    aSquare->setPiece(aPiece);
    aPiece->setLocation(aSquare);
    blackP.insert(aPiece);

    for (int i = 0; i < 8; i++) {
        aPiece = new Pawn(true);
        aSquare = board.squareAt(i, 1);
        aSquare->setPiece(aPiece);
        aPiece->setLocation(aSquare);
        whiteP.insert(aPiece);

        aPiece = new Pawn(false);
        aSquare = board.squareAt(i , 6);
        aSquare->setPiece(aPiece);
        aPiece->setLocation(aSquare);
        blackP.insert(aPiece);
    }

    aKing = new King(true);
    aSquare = board.squareAt(4, 0);
    aSquare->setPiece(aKing);
    aKing->setLocation(aSquare);
    whiteP.insert(aKing);

    player1->SetPieces(whiteP);
    player1->SetKing(aKing);
    
    aKing = new King(false);
    aSquare = board.squareAt(4,7);
    aSquare->setPiece(aKing);
    aKing->setLocation(aSquare);
    blackP.insert(aKing);
    player2->SetPieces(blackP);
    player2->SetKing(aKing);

    this->player1 = player1;
    this->player2 = player2;

}

ChessPlayer* Game::getPlayer(int player_id) {
    if (player_id == 1) {
        return player1;
    } else if (player_id == 2) {
        return player2;
    } else {
        return nullptr;
    }
}

ChessPlayer* Game::opponent(ChessPlayer& player) {
    ChessPlayer* opponent;
    if (player.getName() == player1->getName()) {
        std::cout << "DEBUG: Player is player1, setting opponent to player2." << std::endl;
        opponent = player2;
    } else {
        std::cout << "DEBUG: Player is player2, setting opponent to player1." << std::endl;
        opponent = player1;
    }
    return opponent;
}

bool Game::MakeMove(ChessPlayer& player, Move move) {
    std::cout << "DEBUG: Starting MakeMove for player: " << player.getName() << std::endl;
    std::cout << "DEBUG: Move from (" << move.from_x << ", " << move.from_y << ") to ("
              << move.to_x << ", " << move.to_y << ")" << std::endl;

    // Get the origin and destination squares
    Square* origin = board.squareAt(move.from_x, move.from_y);
    Square* dest = board.squareAt(move.to_x, move.to_y);

    if (origin == dest) {
        std::cerr << "ERROR: Origin and destination squares are the same." << std::endl;
        return false;
    }

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
    if (!piece->canMoveTo(board, *dest)) {
        std::cerr << "ERROR: Piece cannot move to the destination square (" << move.to_x << ", " << move.to_y << ")." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Piece can move to the destination square." << std::endl;

    // Perform the move
    std::optional<Piece*> capturedPiece = piece->move(player, *dest);
    if (capturedPiece.has_value()) {
        std::cout << "DEBUG: Captured piece at destination square." << std::endl;
        opponent(player)->capture(capturedPiece.value());
    } else {
        std::cout << "DEBUG: No piece captured during the move." << std::endl;
    }

    std::cout << "DEBUG: Move executed successfully." << std::endl;

    // Check if the move puts the player's king in check
    if (player.inCheck(*this)) {
        std::cerr << "ERROR: Move puts the king in check. Reverting move." << std::endl;
        piece->move(player, *origin);
        return false;
    }

    std::cout << "DEBUG: Move completed successfully without putting the king in check." << std::endl;

    return true;
}

bool Game::inCheck(ChessPlayer& player) {
    std::cout << "DEBUG: Checking if player " << player.getName() << " is in check." << std::endl;

    Square* kingSquare = player.myKing()->location();
    if (!kingSquare) {
        std::cerr << "ERROR: King's location is not set for player " << player.getName() << "." << std::endl;
        return false;
    }

    std::cout << "DEBUG: King's location is at (" << kingSquare->getX() << ", " << kingSquare->getY() << ")." << std::endl;

    auto opponentPieces = opponent(player)->myPieces();
    if (opponentPieces.empty()) {
        std::cout << "DEBUG: Opponent has no pieces. Player " << player.getName() << " cannot be in check." << std::endl;
        return false;
    }

    std::cout << "DEBUG: Opponent has " << opponentPieces.size() << " pieces." << std::endl;

    for (Piece* opponentPiece : opponentPieces) {
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
        if (opponentPiece->canMoveTo(getBoard(), *kingSquare)) {
            std::cout << "DEBUG: Opponent piece at (" << opponentLocation->getX() << ", " << opponentLocation->getY()
                      << ") can move to the king's square (" << kingSquare->getX() << ", " << kingSquare->getY() << ")." << std::endl;
            std::cout << "Player " << player.getName() << " is in check by "
                      << (opponentPiece->isPieceWhite() ? "white" : "black") << " piece." << std::endl;
            return true;
        }
    }

    std::cout << "DEBUG: No opponent pieces can move to the king's square. Player " << player.getName() << " is not in check." << std::endl;
    return false;
}


std::vector<Move> Game::generateMoves(ChessPlayer& player) {
    std::vector<Move> moves;
    for (Piece* piece : player.myPieces()) {
        if (!piece || !piece->location()) continue; // Skip null pieces or pieces not on a square
        Square* origin = piece->location();
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                Square* dest = board.squareAt(x, y);
                if (piece->canMoveTo(board, *dest)) {
                    if (origin->getX() == dest->getX() && origin->getY() == dest->getY()) {
                        std::cerr << "ERROR: Piece at (" << origin->getX() << ", " << origin->getY()
                                  << ") claims it can move to its own square (" << dest->getX() << ", " << dest->getY()
                                  << "). This is incorrect!" << std::endl;
                    } else {
                        std::cout << "DEBUG: Piece at (" << origin->getX() << ", " << origin->getY()
                                  << ") can move to (" << dest->getX() << ", " << dest->getY() << ")." << std::endl;
                        moves.push_back({origin->getX(), origin->getY(), dest->getX(), dest->getY()});
                    }
                }
            }
        }
    }
    return moves;
}
