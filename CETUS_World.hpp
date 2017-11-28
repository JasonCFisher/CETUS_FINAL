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
		std::vector<Room*> worldRooms;
        int act;
		std::vector<Item*> worldItems;

	public:

		World();
		World(Room* current, int currentHealth, int currentMoves, int currentSpecialCount, int currentAct);
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
        int getAct();
        void incrementAct();
        int actController(string, string);
		int	createItems(std::vector <Item*> itemVect);
		std::vector<Item*> getItems();
		void setAct(int currentAct);
		void addWorldItem(Item* current);
    Item* findWorldItem(string, bool);
    void destroyItem(string); //takes item from inventory and places into world inventory
};
#endif
