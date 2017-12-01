#include <iostream>
#include <string>
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"



#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5
#define LINESIZE 101

/*const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");*/


using std::endl;
using std::cout;
using std::string;

Player::Player(){
    
    this->health = 100;
    this->movesCompleted = 0;
    this->currentRoom = NULL;
    this->currentNeighbors = NULL;
    this->specialItemCount = 0;
    return;
}

Player::Player(Room* current, int currentHealth, int currentMoves, int currentSpecialCount){
    
    this->health = currentHealth;
    this->movesCompleted = currentMoves;
    this->currentRoom = current;
    this->currentNeighbors = current->getNeighbors();
    this->specialItemCount = currentSpecialCount;
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


Room* Player::getCurrentRoom(){
    
    return this->currentRoom;
    
}

int Player::getSpecialItemCount(){
    
    return this->specialItemCount;
    
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
    this->currentNeighbors = current->getNeighbors();
    this->specialItemCount = 0;
    return 0;
    
}
int Player::damagePlayer(int damage){
    
    this->health -= damage;
    cout << "You took " << damage << " damage.\n"  << "You have " << this->health << " life.\n";
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

void Player::setHealth(int currentHealth){
    
    this->health = currentHealth;
    
}
void Player::setCurrentRoom(Room* currentR){
    
    this->currentRoom = currentR;
    
}
void Player::setMovesCompleted(int moves){
    
    this->movesCompleted = moves;
    
}
void Player::setSpecialItemCount(int count){
    
    this->specialItemCount = count;
    
}
void Player::setNeighbors(List* newNeighbors){
    
    this->currentNeighbors = newNeighbors;
    
}
std::vector<Item*> Player::getItems(){
    return this->inventory;
}

void Player::addItem(Item* current){
    
    this->inventory.push_back(current);
    return;
    
}

int Player::invIsEmpty(){
    if( this->inventory.size()==0){
        return 1;
    }else{
        return 0;
    }
}
