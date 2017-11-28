#include <string>
#include <algorithm>
#include <vector>
#include "CETUS_Items.hpp"
#include "creature.hpp"
#include "CETUS_List.hpp"
#ifndef CETUS_ROOM_HPP
#define CETUS_ROOM_HPP

using std::string;


class List;


class Room {
	
	private:
	
		friend class Player;
		friend class World;
		string ID;
		string 	Name;
		string	longDesc;
		string	shortDesc;
		bool	visited;
		std::vector<Item*> roomItems;
		List* 	neighbors;
        Creature* enemy;
	public:
	
		Room();
		~Room();
		string getName();
		void addDescriptions(string longDesc, string shortDesc);
		void addItem(Item* current);
		Item* removeItem(Item* current);
		void addNeighbor(int direction, Room* neigbor);
		void createNeighbors(List* neighborList);
		void getLong();
		void getShort();
		void setName(string currentName);
		void setVisited(bool visit);
		List* getNeighbors();
		Item* findItem(string current, bool drop);
        int getVisited();
		std::vector<Item*> getItems();
		string saveLongDesc();
		string saveShortDesc();
        int invIsEmpty(); //checking room inventory
        int hasEnemy();
        void setEnemy(Creature*);
        Creature* getEnemy();
		void setID(string currentID);
		string getID();
 
};
#endif
