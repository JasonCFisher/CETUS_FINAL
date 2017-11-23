#include "CETUS_Room.hpp"
#include <iostream>

using std::endl;
using std::cout;
using std::string;


Room::Room(){
	
	this->visited = false;
	this->north = NULL;
    this->south= NULL;
    this->east = NULL;
    this->west = NULL;
    this->up = NULL;
    this->down = NULL;
	return;
	
}

Room::Room(Room* n, Room* s, Room* e, Room* w, Room* u, Room* d, string newName, string newLong, string newShort, bool vis){
    this->north = n;
    this->south = s;
    this->east = e;
    this->west = w;
    this->up = u;
    this->down = d;
    this->name = newName;
    this->longDesc = newLong;
    this->shortDesc = newShort;
    this->visited = vis;
}

Room::~Room(){
    if (this->north != NULL){ delete this->north;}
    
    if (this->south != NULL){ delete this->south;}
    
    if (this->east != NULL){ delete this->east;}
    
    if (this->west != NULL){ delete this->west;}
    
    if (this->up != NULL){ delete this->up;}
    
    if (this->down != NULL){ delete this->down;}
}
string Room::getName(){
    return this->name;
}

void Room::addDescriptions(string longDesc, string shortDesc){
	
	this->longDesc = longDesc;
	this->shortDesc = shortDesc;
	return;	
	
}

void Room::addItem(Item* current){
	
	this->roomItems.push_back(current);
	
	return;
	
}

void Room::removeItem(Item* current){
	
	return;
	
}


void Room::getLong(){

		cout<<this->longDesc;
		return;
	
}

void Room::getShort(){

	cout<<this->shortDesc;
	return;
	
}



//to be used when dimension changes, quick way to alter the adjacency list for each room
void Room::switchAdjacent(int first, int second){
    
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
                    this->south    = this->west;
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
                    this->south    = temp;
                    break;
                    
                case 3:
                    this->east    = this->west;
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
                    this->south    = temp;
                    break;
                    
                case 2:
                    this->west    = this->east;
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

void Room::addAdjacent(int direction, Room* current){
    
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

Room* Room::getNeighbor(string dir){
    if(dir == "north"){
        return this->north;
    } else if(dir == "south"){
        return this->south;
    } else if(dir == "east"){
        return this->east;
    }else if(dir == "west"){
        return this->west;
    }else if(dir == "up"){
        return this->up;
    }else if(dir == "down"){
        return this->down;
    }else {
        return NULL;
    }
}

std::vector<Item*> Room::getRoomItems(){
    
    return roomItems;
}

void Room::printRoomItems(){
    cout << "\n\n";
    for(std::vector<Item*>::iterator it = this->roomItems.begin(); it != this->roomItems.end(); ++it) {
        
        cout << (*it)->getName() << std::endl;
        
    }}

bool Room::isVisited(){
    return this->visited;
}

void Room::setVisited(){
    this->visited = true;
}

void Room::addEnemy(Creature* enemy){
    this->enemyList.push_back(enemy);
}
std::vector<Creature*> Room::getEnemies(){
    return this->enemyList;
}

