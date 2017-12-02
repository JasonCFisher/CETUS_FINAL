all: main.cpp Data.o List.o Items.o Player.o Room.o World.o Parser.o Print.o battle.o creature.o cetus.o ghost.o cultist.o  merman.o 
	
	g++ -std=c++11 -o cetus main.cpp CETUS_World.o CETUS_data.o CETUS_List.o CETUS_Items.o CETUS_Player.o CETUS_Room.o CETUS_Parser.o CETUS_Print.hpp battle.o creature.o cetus.o ghost.o cultist.o  merman.o 

creature.o: creature.cpp
	g++ -c creature.cpp -std=c++11

cetus.o: cetus.cpp
	g++ -c cetus.cpp -std=c++11

ghost.o: ghost.cpp
	g++ -c ghost.cpp -std=c++11	

cultist.o: cultist.cpp
	g++ -c cultist.cpp -std=c++11

merman.o: merman.cpp
	g++ -c merman.cpp -std=c++11

battle.o: battle.cpp
	g++ -c battle.cpp -std=c++11

World.o: CETUS_World.cpp
	g++ -c CETUS_World.cpp -std=c++11
	
Data.o: CETUS_data.cpp
	g++ -c CETUS_data.cpp -std=c++11

Items.o: CETUS_Items.cpp
	g++ -c CETUS_Items.cpp -std=c++11

List.o: CETUS_List.cpp
	g++ -c CETUS_List.cpp -std=c++11

Player.o: CETUS_Player.cpp
	g++ -c CETUS_Player.cpp -std=c++11

Room.o: CETUS_Room.cpp 
	g++ -c CETUS_Room.cpp -std=c++11

Print.o: CETUS_Print.hpp
	g++ -c CETUS_Print.hpp -std=c++11
	
Parser.o: CETUS_Parser.cpp
	g++ -c CETUS_Parser.cpp -std=c++11
	
test: CETUS_TEST.cpp World.o Room.o Player.o Items.o List.o Print.o
	g++ -o test CETUS_TEST.cpp CETUS_World.o CETUS_List.o CETUS_Items.o CETUS_Player.o CETUS_Room.o CETUS_Print.hpp  -std=c++11

clean:
	$(RM) *.o
