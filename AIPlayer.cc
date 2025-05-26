#include "AIPlayer.h"

#include <iostream>

#include "Game.h"

AIPlayer::AIPlayer(std::string name, bool isWhite, std::set<Piece*>& pieces, King& king)
    : name(name), isWhite(isWhite), pieces(pieces), king(&king) {}
AIPlayer::AIPlayer() 
    : name("AI Player"), isWhite(false), king(nullptr) {
}

bool AIPlayer::inCheck(Game &game) {
    return game.inCheck(*this);
}

void AIPlayer::capture(Piece* piece) {
    pieces.erase(piece);
}

std::string AIPlayer::getName() {
    return name;
}

bool AIPlayer::isPlayerWhite() {
    return isWhite;
}

std::set<Piece*> AIPlayer::myPieces() {
    return pieces;
}

King* AIPlayer::myKing() {
    return king;
}

double AIPlayer::mini_max(int depth, Game& game, double alpha, double beta, bool isMaximisingPlayer) {
    if (depth == 0) {
        double eval = -evaluate_board(game);
        return eval;
    }

    if (isMaximisingPlayer) {
        double maxEval = -1e9;
        auto moves = game.generateMoves(*game.getPlayer(2));

        for (const auto& move : moves) {
            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(2), move)) {
                double eval = mini_max(depth - 1, newGame, alpha, beta, false);

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);

                if (beta <= alpha) {
                    break;
                }
            } else {
                std::cerr << "DEBUG: Move failed. Skipping move." << std::endl;
            }
        }
        return maxEval;
    } else {
        double minEval = 1e9;
        auto moves = game.generateMoves(*game.getPlayer(1));

        for (const auto& move : moves) {
            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(1), move)) {
                double eval = mini_max(depth - 1, newGame, alpha, beta, true);

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);

                if (beta <= alpha) {
                    break;
                }
            } else {
                std::cerr << "DEBUG: Move failed. Skipping move." << std::endl;
            }
        }
        return minEval;
    }
}

double AIPlayer::evaluate_board(Game& game) {
    double score = 0.0;

    for (Piece* piece : game.getPlayer(2)->myPieces()) {
        if (!piece || !piece->location()) continue;
        score += piece->getValue();
    }

    for (Piece* piece : game.getPlayer(1)->myPieces()) {
        if (!piece || !piece->location()) continue;
        score -= piece->getValue(); 
    }

    return score;
}

Move AIPlayer::getMove(Game& game) {
    double bestEval = -1e9;
    Move bestMove{-1, -1, -1, -1};

    // Iterate through all pieces owned by the AI player
    for (Piece* piece : pieces) {
        if (!piece) {
            continue;
        }

        Square* origin = piece->location();
        if (!origin) {
            std::cerr << "DEBUG: Piece has no location. Skipping." << std::endl;
            continue;
        }

        // Iterate through all possible destination squares
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                Square* dest = game.getBoard().squareAt(x, y);


                if (!dest) {
                    continue;
                }

                if (!piece) {
                    continue;
                }

                if (piece->canMoveTo(game.getBoard(), *dest)) {
                    Game newGame = game;  // Create a copy of the game
                    Move move{origin->getX(), origin->getY(), x, y};

                    if (newGame.MakeMove(*this, move)) {
                        double eval = mini_max(1, newGame, -1e9, 1e9, false);  // Depth = 1

                        if (eval > bestEval) {
                            bestEval = eval;
                            bestMove = move;
                        }
                        else {
                        }
                    } else {
                    }
                } else {
                }
            }
        }
    }

    if (bestMove.from_x == -1) {
    } else {
    }

    return bestMove;
}
