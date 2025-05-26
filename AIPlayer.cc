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
    std::cout << "DEBUG: AIPlayer name is: " << name << std::endl;
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
    std::cout << "DEBUG: Entering mini_max. Depth: " << depth
              << ", Alpha: " << alpha << ", Beta: " << beta
              << ", Maximising: " << (isMaximisingPlayer ? "true" : "false") << std::endl;

    if (depth == 0) {
        double eval = -evaluate_board(game);
        std::cout << "DEBUG: Reached leaf node. Evaluation: " << eval << std::endl;
        return eval;
    }

    if (isMaximisingPlayer) {
        double maxEval = -1e9;
        auto moves = game.generateMoves(*game.getPlayer(2));
        std::cout << "DEBUG: Maximising player. Number of moves: " << moves.size() << std::endl;

        for (const auto& move : moves) {
            std::cout << "DEBUG: Evaluating move from (" << move.from_x << ", " << move.from_y
                      << ") to (" << move.to_x << ", " << move.to_y << ")." << std::endl;

            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(2), move)) {
                std::cout << "DEBUG: Move successful. Simulating next depth." << std::endl;
                double eval = mini_max(depth - 1, newGame, alpha, beta, false);
                std::cout << "DEBUG: Evaluation returned: " << eval << std::endl;

                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                std::cout << "DEBUG: Updated maxEval: " << maxEval << ", Alpha: " << alpha << std::endl;

                if (beta <= alpha) {
                    std::cout << "DEBUG: Beta cut-off. Beta: " << beta << ", Alpha: " << alpha << std::endl;
                    break;
                }
            } else {
                std::cerr << "DEBUG: Move failed. Skipping move." << std::endl;
            }
            std::cout << "DEBUG: Current maxEval: " << maxEval << std::endl;
        }
        std::cout << "DEBUG: Returning maxEval: " << maxEval << std::endl;
        return maxEval;
    } else {
        double minEval = 1e9;
        auto moves = game.generateMoves(*game.getPlayer(1));
        std::cout << "DEBUG: Minimising player. Number of moves: " << moves.size() << std::endl;

        for (const auto& move : moves) {
            std::cout << "DEBUG: Evaluating move from (" << move.from_x << ", " << move.from_y
                      << ") to (" << move.to_x << ", " << move.to_y << ")." << std::endl;

            Game newGame = game;
            if (newGame.MakeMove(*game.getPlayer(1), move)) {
                std::cout << "DEBUG: Move successful. Simulating next depth." << std::endl;
                double eval = mini_max(depth - 1, newGame, alpha, beta, true);
                std::cout << "DEBUG: Evaluation returned: " << eval << std::endl;

                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                std::cout << "DEBUG: Updated minEval: " << minEval << ", Beta: " << beta << std::endl;

                if (beta <= alpha) {
                    std::cout << "DEBUG: Alpha cut-off. Beta: " << beta << ", Alpha: " << alpha << std::endl;
                    break;
                }
            } else {
                std::cerr << "DEBUG: Move failed. Skipping move." << std::endl;
            }
        }
        std::cout << "DEBUG: Returning minEval: " << minEval << std::endl;
        return minEval;
    }
}

double AIPlayer::evaluate_board(Game& game) {
    std::cout << "DEBUG: Evaluating board for AI player: " << getName() << std::endl;
    double score = 0.0;

    for (Piece* piece : game.getPlayer(2)->myPieces()) {
        if (!piece || !piece->location()) continue;
        score += piece->getValue();
    }

    for (Piece* piece : game.getPlayer(1)->myPieces()) {
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
        if (!piece) {
            std::cerr << "DEBUG: Found a null piece in AI player's pieces. Skipping." << std::endl;
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
        std::cerr << "DEBUG: No valid moves found for AI player." << std::endl;
    } else {
        std::cout << "DEBUG: Best move found: (" << bestMove.from_x << ", " << bestMove.from_y
                  << ") to (" << bestMove.to_x << ", " << bestMove.to_y << ") with evaluation: " << bestEval << std::endl;
    }

    return bestMove;
}
