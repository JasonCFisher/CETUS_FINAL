#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <term.h>
#include <fstream>
#define numItems 10
//#include "CETUS_Room.hpp"

#ifndef CETUS_PLAYER_HPP
#define CETUS_PLAYER_HPP

using std::string;
using std::cout;
using std::endl;
using std::ifstream;


class Item;
class Room;
class List;
void printLogo();
void ClearScreen();
void cetusPrint(string* temp, int color);

class Player{

	private:
	
		friend class World;
		string Name;
		int	health;
		int movesCompleted;
		Room* currentRoom;
		std::vector<Item*> inventory;
		int specialItemCount;
		List* currentNeighbors;
	
	public:
	
		Player();
		Player(Room* current, int currentHealth, int currentMoves, int currentSpecialCount);
		string getName();
		int getHealth();
		int getMovesCompleted();
		Room*	getCurrentRoom();
		int getSpecialItemCount();
		void setHealth(int currentHealth);
		void setCurrentRoom(Room* currentR);
		void setMovesCompleted(int moves);
		void setSpecialItemCount(int count);
		void setNeighbors(List* newNeighbors);
		void addItem(Item* current);
		int incrementMoves();
		int decrementMoves();
		int resurrectPlayer(Room* currentR);
		int damagePlayer(int damage);
		int healPlayer(int health);
		std::vector<Item*> getItems();
        int invIsEmpty(); //added to check if inventory empty
};

#endif
