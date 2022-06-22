#include "ChessBoard.h"
#include "Piece.h"

using namespace std;

ChessBoard::ChessBoard() {
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            squares[i][j] = new Square(i, j);
        }
    }
}

ChessBoard::~ChessBoard() {
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            delete[] squares[i][j];
        }
        delete [] squares[i];
    }
    delete [] squares;
}

ChessBoard * ChessBoard::getBoard() {
    if (!board) {
        board = new ChessBoard();
    } 
    return board;
}

Square * ChessBoard::squareAt(int x, int y) {
    return squares[x][y];
}

bool ChessBoard::clearVertPath(Square &origin, Square & dest) {
    if (origin.getX() != dest.getX()) {
        return false;
    }
    int start, end;

    if (origin.getY() < dest.getY()) {
        start = origin.getY();
        end = dest.getY();
    } else {
        end = origin.getY();
        start = dest.getY();
    }

    int x = origin.getX();
    for (int i = start + 1; i < end; i++) {
        if (squareAt(x, i)->occupied()) return false;
    }
    return true;
}

bool ChessBoard::clearHorPath(Square & origin, Square & dest) {
    if (origin.getY() != dest.getY()) return false;

    int start, end;
    if (origin.getX() < dest.getX()) {
        start = origin.getX();
        end = dest.getX();
    } else {
        end = origin.getX();
        start = dest.getX();
    }
    int y = origin.getY();

    for (int i = start; i < end; i++) {
        if (squareAt(i, y)->occupied()) return false; 
    }

    return true;

}

bool ChessBoard::clearDiagPath(Square & origin, Square &dest) {
    return true;
}

void ChessBoard::display(ostream& out) {
    out << endl << " a b c d e f g h" << endl;
    out << "==================" << endl;
    for (int i = DIMENSION - 1; i >= 0; i--) {
        out << i + 1;
        for (int x = 0; x < DIMENSION; x++) {
            out << "|";
            if (squares[x][i]->occupied()) {
                squares[x][i]->occupiedBy()->display();
            } else {
                out << " ";
            }
        }
        out << endl;
    }
    out << " a b c d e f g h" << endl;
}
