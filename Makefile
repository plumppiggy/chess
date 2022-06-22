CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = bishop.o main.o queen.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chessgame

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
