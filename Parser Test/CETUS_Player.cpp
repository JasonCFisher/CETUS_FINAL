#include <iostream>
#include <string>
#include <iterator>
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5

using std::endl;
using std::cout;
using std::string;

	Player::Player(){
		
		this->health = 100;
		this->movesCompleted = 0;
		this->currentRoom = NULL;
		//this->currentNeighbors = NULL;
		this->specialItemCount = 0;
		return;
	}
	
	Player::Player(Room* current){
		
		this->health = 100;
		this->movesCompleted = 0;
		this->currentRoom = current;
		//this->currentNeighbors = current->getNeighbors();
		this->specialItemCount = 0;
		return;
	}
	
	string Player::getName(){
		
		return this->Name;
		
	}
	int Player::getHealth(){
		
		return this->health;
		
	}
	int Player::getMovesCompleted(){
		
		return this->movesCompleted;
		
	}
	
	void Player::setCurrentRoom(Room* current){
		
		this->currentRoom = current;
		return;
	}
	
	Room* Player::getCurrentRoom(){
		
		return this->currentRoom;
		
	}

	int Player::getSpecialItemCount(){
		
		return this->specialItemCount;
		
	}
	
	int Player::addItem(Item* current){
		
		this->inventory.push_back(current);
        return 0;
	}
	int Player::dropItem(Item* current){
		
		return 0;
		
	}
	int Player::incrementMoves(){
		
		this->movesCompleted++;
		return 0;
		
	}
	int Player::decrementMoves(){
		
		this->movesCompleted--;
		return 0;
		
	}
	int Player::resurrectPlayer(Room* current){
		
		this->health = 100;
		this->movesCompleted = 0;
		this->currentRoom = current;
		//this->currentNeighbors = current->getNeighbors();
		this->specialItemCount = 0;
		return 1;
		
	}
	int Player::damagePlayer(int damage){
		
		this->health -= damage;

		if(this->health < 0){
			
			this->health = 0;
			
		}
		
		return 0;
		
	}
	int Player::healPlayer(int health){
		
		this->health += health;

		if(this->health > 100){
			
			this->health = 100;
			
		}
		
		return 0;		
		
	}

	void Player::printAllAdjacent(){
        Room* current = this->getCurrentRoom();
		if (current->getNeighbor("north") != NULL){
			
			cout << current->getNeighbor("north")->getName() << endl;
			
		}
		
		if (current->getNeighbor("south") != NULL){
			
			cout << current->getNeighbor("south")->getName() << endl;
			
		}
		
		if (current->getNeighbor("east") != NULL){
			
			cout << current->getNeighbor("east")->getName() << endl;
			
		}
		
		if (current->getNeighbor("west") != NULL){
			
			cout << current->getNeighbor("west")->getName()<< endl;
			
		}
		
		
		if (current->getNeighbor("up") != NULL){
			
			cout << current->getNeighbor("up")->getName() << endl;
			
		}
		
		if (current->getNeighbor("down") != NULL){
			
			cout << current->getNeighbor("down")->getName() << endl;
			
		}
		
		return;
	}

	void Player::printInventory(){
		
		for(std::vector<Item*>::iterator it = this->inventory.begin(); it != this->inventory.end(); ++it) {
			
			cout << (*it)->getName();
			
		}
		
		return;
		
	}
	void Player::printRoomInventory(){
		
		for(std::vector<Item*>::iterator it = this->currentRoom->getRoomItems().begin(); it != this->currentRoom->getRoomItems().end(); ++it) {
			
			cout << (*it)->getName();
			
		}
		
		return;		
		
	}
	void Player::printAdjacent(int direction){
		
		switch(direction){
			
			case NORTH:
				cout << this->getCurrentRoom()->getNeighbor("north")->getName() << endl;
				break;
			
			case SOUTH:
				cout << this->getCurrentRoom()->getNeighbor("south")->getName() << endl;
				break;
			
			case EAST:
				cout << this->getCurrentRoom()->getNeighbor("east")->getName()<< endl;
				break;
			
			case WEST:
				cout << this->getCurrentRoom()->getNeighbor("west")->getName() << endl;
				break;
			
			case UP:
				cout << this->getCurrentRoom()->getNeighbor("up")->getName() << endl;
				break;
			
			case DOWN:
				cout << this->getCurrentRoom()->getNeighbor("down")->getName()<< endl;
				break;
			
			default:
				break;
			
		}		
		return;		
		
	}

void Player::displayRoom(){
    //Display the correct room description.
    cout << this->getCurrentRoom()->getName() << "\n\n";
    if(this->getCurrentRoom()->isVisited()){
        this->getCurrentRoom()->getShort();
    } else {
        this->getCurrentRoom()->getLong();
    }
    
    this->getCurrentRoom()->printRoomItems();
    
    if(!this->getCurrentRoom()->isVisited()){
        this->getCurrentRoom()->setVisited();
    }
    return;
}

	void Player::move(int direction){
		
		switch(direction){
			
			case NORTH:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("north");
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case SOUTH:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("south");;
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case EAST:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("east");
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case WEST:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("west");
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case UP:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("up");
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case DOWN:
				this->currentRoom = this->getCurrentRoom()->getNeighbor("down");
				//this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			default:
				break;
			
            
		}
        
        this->displayRoom();
        
        return;
	}

std::vector<Item*> Player::getInventory(){
    return this->inventory;
}
