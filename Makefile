CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = gameimpl.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = tictactoe

${EXEC} : ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY : clean

clean :
		rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
