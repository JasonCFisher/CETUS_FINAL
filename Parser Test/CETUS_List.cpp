#include "CETUS_List.hpp"
#include <iostream>

/* 
NORTH 	0
SOUTH 	1
EAST 	2
WEST 	3
UP		4
DOWN	5
*/

using std::endl;
using std::cout;
using std::string;

List::List(){
	
	this->north = NULL;
	this->south = NULL;
	this->east = NULL;
	this->west = NULL;
	this->up = NULL;
	this->down = NULL;

}

List::~List(){

		if (this->north != NULL){ delete this->north;}
		
		if (this->south != NULL){ delete this->south;}
		
		if (this->east != NULL){ delete this->east;}
		
		if (this->west != NULL){ delete this->west;}
		
		if (this->up != NULL){ delete this->up;}
		
		if (this->down != NULL){ delete this->down;}
	
}

void List::addAdjacent(int direction, Room* current){
	
	switch(direction){
		
		case 0:
			this->north = current;
			break;
		
		case 1:
			this->south = current;
			break;
			
		case 2:
			this->east = current;
			break;
			
		case 3:
			this->west = current;
			break;
			
		default:
			break;		
		
	}
	
	return;
	
}

//to be used when dimension changes, quick way to alter the adjacency list for each room
void List::switchAdjacent(int first, int second){
	
	Room* temp;
	
	switch(first){
		
	case 0:
	
		temp = this->north;
		switch(second){
			
			case 1:
				this->north = this->south;
				this->south = temp;
				break;
					
			case 2:
				this->north = this->east;
				this->east = temp;
				break;
					
			case 3:
				this->north = this->west;
				this->west = temp;
				break;
					
			default:
				break;					
			}
		break;
		
	case 1:
		temp = this->south;
			
		switch(second){
			
			case 0:
				this->south = this->north;
				this->north = temp;
				break;
					
			case 2:
				this->south = this->east;
				this->east = temp;
				break;
					
			case 3:
				this->south	= this->west;
				this->west = temp;
				break;
					
			default:
				break;					
		}
		break;
			
	case 2:
		temp = this->east;
		
		switch(second){
			
			case 0:
				this->east = this->north;
				this->north = temp;
				break;
					
			case 1:
				this->east = this->south;
				this->south	= temp;
				break;
					
			case 3:
				this->east	= this->west;
				this->west = temp;
				break;
					
			default:
				break;					
		}
		
		break;
			
	case 3:
		temp = this->west;
		
		switch(second){
			
			case 0:
				this->west = this->north;
				this->north = temp;
				break;
					
			case 1:
				this->west = this->south;
				this->south	= temp;
				break;
					
			case 2:
				this->west	= this->east;
				this->east = temp;
				break;
					
			default:
				break;					
		}		
		break;
	
	case 4:
		temp = this->up;
		
		switch(second){
			
			case 5:
				this->up = this->down;
				this->down = temp;
				break;
				
			default:
				break;
		}
		break;
		
	case 5:
		temp = this->down;
		
		switch(second){
			case 4:
				this->down = this->up;
				this->up = temp;
				break;
				
			default:
				break;
		}
		break;
	
	default:
		break;		
	
	}
	
	return;	
	
}

