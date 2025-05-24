#include "AIPlayer.h"

#include <iostream>

#include "Game.h"

AIPlayer::AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king)
    : name(name), isWhite(isWhite), pieces(pieces), king(&king) {}
AIPlayer::AIPlayer() 
    : name("Black"), isWhite(false), king(nullptr) {
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

double AIPlayer::mini_max(int depth, Game &game, double alpha, double beta, bool isMaximisingPlayer) {
    if (depth == 0) {
        return -evaluate_board(game);
    }

    if (isMaximisingPlayer) {
        double maxEval = -1e9; 
        auto moves = game.generateMoves(*game.getPlayer(2));
        
        for (const auto& move : moves) {
            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(1), move)) {
                double eval = mini_max(depth - 1, newGame, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break; // Beta cut-off
                }
            }
        }
        return maxEval;
    } else {
        double minEval = 1e9;
        auto moves = game.generateMoves(*game.getPlayer(2));
        for (const auto& move : moves) {
            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(2), move)) {
                double eval = mini_max(depth - 1, newGame, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
}
}

double AIPlayer::evaluate_board(Game& game) {
    double score = 0.0;

    for (Piece* piece : *game.getPlayer(2)->myPieces()) {
        if (!piece || !piece->location()) continue;
        score += piece->getValue();
    }

    for (Piece* piece : *game.getPlayer(1)->myPieces()) {
        if (!piece || !piece->location()) continue;
        score -= piece->getValue(); 
    }

    std::cout << "DEBUG: Evaluating board. Score: " << score << std::endl;

    return score;
}

Move AIPlayer::getMove(Game& game) {
    std::cout << "DEBUG: Starting getMove for AI player: " << getName() << std::endl;

    double bestEval = -1e9;
    Move bestMove{-1, -1, -1, -1};

    // Iterate through all pieces owned by the AI player
    for (Piece* piece : pieces) {
        std::cout << "DEBUG: Evaluating piece: " <<  std::endl;
        if (!piece) {
            std::cerr << "DEBUG: Found a null piece in AI player's pieces. Skipping." << std::endl;
            continue;
        }

        Square* origin = piece->location();
        if (!origin) {
            std::cerr << "DEBUG: Piece has no location. Skipping." << std::endl;
            continue;
        }

        std::cout << "DEBUG: Evaluating moves for piece at (" << origin->getX() << ", " << origin->getY() << ")." << std::endl;

        // Iterate through all possible destination squares
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                Square* dest = ChessBoard::getBoard()->squareAt(x, y);
                if (!dest) {
                    std::cerr << "DEBUG: Destination square (" << x << ", " << y << ") is invalid. Skipping." << std::endl;
                    continue;
                }

                if (piece->canMoveTo(*dest)) {
                    std::cout << "DEBUG: Piece can move to (" << x << ", " << y << ")." << std::endl;

                    Game newGame = game;  // Create a copy of the game
                    Move move{origin->getX(), origin->getY(), x, y};

                    if (newGame.MakeMove(*this, move)) {
                        std::cout << "DEBUG: Simulating move from (" << move.from_x << ", " << move.from_y
                                  << ") to (" << move.to_x << ", " << move.to_y << ")." << std::endl;

                        double eval = mini_max(3, newGame, -1e9, 1e9, false);  // Depth = 3
                        std::cout << "DEBUG: Evaluation for move: " << eval << std::endl;

                        if (eval > bestEval) {
                            std::cout << "DEBUG: Found a better move with evaluation: " << eval << std::endl;
                            bestEval = eval;
                            bestMove = move;
                        }
                    } else {
                        std::cerr << "DEBUG: Move from (" << move.from_x << ", " << move.from_y
                                  << ") to (" << move.to_x << ", " << move.to_y << ") is invalid in the simulated game." << std::endl;
                    }
                } else {
                    std::cout << "DEBUG: Piece cannot move to (" << x << ", " << y << "). Skipping." << std::endl;
                }
            }
        }
    }

    if (bestMove.from_x == -1) {
        std::cerr << "DEBUG: No valid moves found for AI player." << std::endl;
    } else {
        std::cout << "DEBUG: Best move found: (" << bestMove.from_x << ", " << bestMove.from_y
                  << ") to (" << bestMove.to_x << ", " << bestMove.to_y << ") with evaluation: " << bestEval << std::endl;
    }

    return bestMove;
}
