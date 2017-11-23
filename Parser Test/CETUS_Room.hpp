#include <string>
#include <algorithm>
#include <vector>
#include "CETUS_Items.hpp"
#include "creature.hpp"
#include "ghost.hpp"

#ifndef CETUS_ROOM_HPP
#define CETUS_ROOM_HPP

using std::string;



class Room {
	
	private:
        Room* north;
        Room* south;
        Room* east;
        Room* west;
        Room* up;
        Room* down;
    
		string 	name;
		string	longDesc;
		string	shortDesc;
		bool	visited;
		std::vector<Item*> roomItems;
        std::vector<Creature*> enemyList;
			
	public:
	
		Room();
    Room(Room*, Room*, Room*, Room*, Room*, Room*, string, string, string, bool);
		~Room();
		string getName();
		void addDescriptions(string longDesc, string shortDesc);
		void addItem(Item* current);
		void removeItem(Item* current);
		void addNeighbor(int direction, Room* neigbor);
		void getLong();
		void getShort();
        void addAdjacent(int, Room*);
		void switchAdjacent(int first, int second);
        Room* getNeighbor(string);
        std::vector<Item*> getRoomItems();
        void printRoomItems();
        bool isVisited();
        void setVisited();
    void addEnemy(Creature*);
    std::vector<Creature*> getEnemies();
};
#endif
