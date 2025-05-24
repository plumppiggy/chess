CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = AIPlayer.o Bishop.o ChessBoard.o Game.o Horse.o King.o Pawn.o Piece.o Player.o Queen.o Rook.o Square.o InputReader.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
