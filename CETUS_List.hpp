#include <string>

#include <iostream>

#ifndef CETUS_LIST_HPP
#define CETUS_LIST_HPP

using std::string;
class Room;

class List{
	
	private:
	
		friend class Player;
		friend class World;
		Room* north;
		Room* south;
		Room* east;
		Room* west; 
		Room* up;
		Room* down;
		
	public:
	
		List();
		~List();
		void addAdjacent(int direction, Room* current);
		void switchAdjacent(int first, int second);
		Room* getAdjName(int dir); 
		
};

#endif
