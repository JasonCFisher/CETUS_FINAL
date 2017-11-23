
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
//#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"
#define numItems 10

#ifndef CETUS_PLAYER_HPP
#define CETUS_PLAYER_HPP

using std::string;

class Item;
class Room;

class Player{
	
	private:
	
		string Name = "John";
		int	health;
		int movesCompleted;
		Room* currentRoom;
		std::vector<Item*> inventory;
		int specialItemCount;
		
	
	public:
	
		Player();
		Player(Room* current);
		string getName();
		int getHealth();
		int getMovesCompleted();
		Room*	getCurrentRoom();
		int getSpecialItemCount();
		void setCurrentRoom(Room* current);
		int addItem(Item* current);
		int dropItem(Item* current);
		int incrementMoves();
		int decrementMoves();
		int resurrectPlayer(Room* current);
		int damagePlayer(int damage);
		int healPlayer(int health);
		void printAllAdjacent();
		void printInventory();
		void printRoomInventory();
		void printAdjacent(int direction);
    void displayRoom();
		void move(int direction);
    std::vector<Item*> getInventory();
};

#endif
