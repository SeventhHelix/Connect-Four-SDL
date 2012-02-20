CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = connectFour
OBJECTS = connectFour.o board.o piece.o interpreter.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
