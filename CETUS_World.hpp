#include <string>
#include "CETUS_Room.hpp"

#ifndef CETUS_WORLD_HPP
#define CETUS_WORLD_HPP

class Room;
class Item;
class Player;
class List;

class World {
	
	private:
	
		string	Name;
		string	Description;
		Player*	currentPlayer;
		bool	realWorld;
<<<<<<< HEAD
		std::vector<Room*> worldRooms; 
        int act;
    
=======
		std::vector<Room*> worldRooms;
		std::vector<Item*> worldItems;
	
>>>>>>> 3a7a416c981684faea3925dc99bd9e169acdaf14
	public:
	
		World();
		World(Room* current, int currentHealth, int currentMoves, int currentSpecialCount);
		int	createRooms(std::vector <Room*> rmVect);
		int	createPlayer();
		void dropItems();
		void dropItem(Item* current);
		string getName();
		string getDescription();
		Player* getPlayer();
		bool getRealWorld();
		Room* getCurrentRoom();
		void setName(string newName);
		void setDescription(string newDesc);
		void setPlayer(Player* currentP);
		void setRealWorld(bool real);
		void setCurrentRoom(Room* currentR);
		void addItem(Item* current);
		void dropItem(string current);	
		Item* findItem(string);
		Item* findItem(string current, bool drop);	
		Item* findRoomItem(string current, bool drop);
		void printAllAdjacent();	
		void printInventory();
		void printRoomInventory();
		void printAdjacent(int direction);
		int move(int direction);
		void printLogo();
		void ClearScreen();
		void cetusPrint(string* inText, int color);
		std::vector<Room*> getRooms();
<<<<<<< HEAD
        int getAct();
        void incrementAct();
        int actController(string);
=======
		int	createItems(std::vector <Item*> itemVect);
		std::vector<Item*> getItems();
	
>>>>>>> 3a7a416c981684faea3925dc99bd9e169acdaf14
};
#endif
