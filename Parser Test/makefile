# Makefile for Final Project

CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -O2
OBJS = parser.o CETUS_Items.o CETUS_Room.o battle.o CETUS_Player.o creature.o ghost.o
SRCS = parser.cpp CETUS_Items.cpp CETUS_Room.cpp creature.cpp ghost.cpp CETUS_Player.cpp
HEADERS = battle.hpp creature.hpp ghost.hpp CETUS_Items.hpp CETUS_Room.hpp CETUS_Player.hpp


#Targets
all: test

test: ${OBJS} #${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o test

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f ${OBJS}


