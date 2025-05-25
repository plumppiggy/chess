#ifndef SQUARES_H
#define SQUARES_H

class Piece;

class Square {
    public:
        bool occupied();
        Square(int x, int y);
        Square();
    
        ~Square();
    
        void setPiece(Piece *piece);
    
        int getX();
        int getY();
    
        Piece* occupiedBy();

        bool operator==(const Square &other) const {
            return (x == other.x && y == other.y);
        }

    private:
        int x, y;
        Piece * piece;

};

#endif

