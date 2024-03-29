CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = Bishop.o ChessBoard.o Game.o Horse.o King.o Pawn.o Piece.o Player.o Queen.o Rook.o Square.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
