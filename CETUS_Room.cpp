#include "CETUS_Room.hpp"
#include <iostream>

using std::endl;
using std::cout;
using std::string;


Room::Room(){

	this->visited = false;
	this->neighbors = NULL;
	this->enemy = NULL;
	return;
	
}

string Room::getName(){
	return this->Name;
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

Item* Room::removeItem(Item* current){
	
	return this->findItem(current->getName(), true);
	
}

/*void Room::addNeighbor(int direction, Room* neighbor){
	
	this->neighbors->addAdjacent(direction, neighbor);
	return;
	
}*/ //Returning error for using an incomplete type here, may need to move this functionality to the overall world. 

void Room::getLong(){

		cout << this->longDesc;
		return;
	
}

void Room::getShort(){

	cout << this->shortDesc;
	return;
	
}

void Room::createNeighbors(List* neighborList){
	
	this->neighbors = neighborList;
	return;
}

List* Room::getNeighbors(){
	
	return this->neighbors;
	
}

void Room::setName(string newName){
	
	this->Name = newName;
	return;
}

void Room::setVisited(bool visit){
	
	
	this->visited = visit;
	
}

Item* Room::findItem(string current, bool drop){
    std::string tempString;
    std::transform(current.begin(), current.end(), current.begin(), ::tolower);
	
    for (int i = 0; i < this->roomItems.size(); i++){
		
		if(roomItems[i] != NULL){
            tempString = this->roomItems[i]->getName();
			
            std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
			
            if (!tempString.compare(current)){
                
                Item* temp = this->roomItems[i];
                
                if(drop == true){
                    this->roomItems.erase(this->roomItems.begin()+i);
                }
                return temp;
            }
        }
    }
    
    return NULL;
    
}

int Room::getVisited(){
    return this->visited;
}


std::vector<Item*> Room::getItems() {
	return this->roomItems;
}

string Room::saveLongDesc() {
	return this->longDesc;
}

string Room::saveShortDesc() {
	return this->shortDesc;
}

int Room::invIsEmpty(){
    if( this->roomItems[0]==NULL){
        return 1;
    }else{
        return 0;
    }
}

int Room::hasEnemy(){
    if(this->enemy != NULL){
        return 1;
    }else {
        return 0;
    }
}

void Room::setEnemy(Creature* newEnemy){
    this->enemy = newEnemy;
}

Creature* Room::getEnemy(){
    if(this->hasEnemy()){
        return this->enemy;
    } else {
        return NULL;
    }
}

void Room::setID(string currentName) {
	this->ID = currentName;
}

string Room::getID(){
	return this->ID;
}
